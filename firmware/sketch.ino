#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =================================
// PIN CONFIGURATION
// =================================

#define DHT_PIN       PA4
#define DHT_TYPE      DHT22

#define LDR_PIN       PA0

#define GREEN_LED     PA1
#define RED_LED       PA2
#define BUZZER_PIN    PA3

// =================================
// SENSOR THRESHOLDS
// =================================

#define TEMP_LIMIT    30.0
#define HUM_LIMIT     70.0

// =================================
// OLED CONFIGURATION
// =================================

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS  0x3C

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// =================================
// GLOBAL VARIABLES
// =================================

unsigned long previousTime = 0;

const unsigned long interval = 2000;

// =================================
// SETUP
// =================================

void setup()
{
  // UART initialization
  Serial.begin(115200);

  // ADC configuration
  analogReadResolution(12);

  // GPIO configuration
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial output state
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // DHT initialization
  dht.begin();

  // I2C initialization
  Wire.begin();

  // OLED initialization
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS))
  {
    Serial.println("OLED initialization failed!");
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(10, 20);
    display.println("STM32 MONITOR");

    display.setCursor(10, 35);
    display.println("Initializing...");

    display.display();
  }

  Serial.println("==============================");
  Serial.println("STM32 ENVIRONMENT MONITOR");
  Serial.println("==============================");
}

// =================================
// OLED DISPLAY FUNCTION
// =================================

void updateDisplay(
  float temperature,
  float humidity,
  int lightValue,
  bool alert
)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("ENVIRONMENT MONITOR");

  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  display.setCursor(0, 18);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 30);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 42);
  display.print("Light ADC: ");
  display.println(lightValue);

  display.setCursor(0, 54);

  if (alert)
  {
    display.println("STATUS: ALERT!");
  }
  else
  {
    display.println("STATUS: NORMAL");
  }

  display.display();
}

// =================================
// SENSOR MONITORING FUNCTION
// =================================

void readSensors()
{
  // Read DHT22 values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read LDR analog value
  int lightValue = analogRead(LDR_PIN);

  // Sensor error checking
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("ERROR: DHT22 reading failed!");

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER_PIN, LOW);

    return;
  }

  // Threshold checking
  bool tempAlert = temperature > TEMP_LIMIT;
  bool humAlert = humidity > HUM_LIMIT;

  bool alert = tempAlert || humAlert;

  // Output control
  if (alert)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    tone(BUZZER_PIN, 1000);
  }
  else
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    noTone(BUZZER_PIN);
  }

  // UART output
  Serial.println("------------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light ADC: ");
  Serial.print(lightValue);
  Serial.println(" / 4095");

  Serial.print("System Status: ");

  if (alert)
  {
    Serial.println("WARNING!");
  }
  else
  {
    Serial.println("NORMAL");
  }

  // OLED update
  updateDisplay(
    temperature,
    humidity,
    lightValue,
    alert
  );
}

// =================================
// MAIN LOOP
// =================================

void loop()
{
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval)
  {
    previousTime = currentTime;

    readSensors();
  }
}
