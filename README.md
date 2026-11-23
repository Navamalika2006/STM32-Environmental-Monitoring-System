# STM32-Environmental-Monitoring-System
Environmental monitoring system using STM32F103C8T6, DHT22, LDR, OLED and UART communication.

<p align="center">
  <strong>An Embedded Systems Project using STM32F103C8T6</strong>
</p>📌 Project Overview

The STM32-Based Environmental Monitoring System is an embedded systems project designed to monitor environmental conditions in real time.

The system uses an STM32F103C8T6 microcontroller to collect temperature, humidity, and light intensity data from sensors. The measured values are displayed on an OLED display, while abnormal environmental conditions trigger visual and audible alerts.

🎯 Project Objectives

- Monitor temperature and humidity in real time.
- Measure light intensity using an LDR sensor.
- Display sensor readings on an OLED screen.
- Implement UART and I2C communication.
- Generate alerts when predefined limits are exceeded.

🔧 Hardware Components

Component| Purpose
STM32F103C8T6 Blue Pill| Main microcontroller
DHT22 Sensor| Temperature and humidity measurement
LDR Sensor| Light intensity measurement
SSD1306 OLED| Displaying sensor readings
Green LED| Normal condition indication
Red LED| Alert indication
Buzzer| Audible alert

💻 Software and Tools

- Wokwi Simulator
- Arduino IDE
- STM32 Arduino Core
- Embedded C/C++
- GitHub

🔗 Communication Interfaces

Interface| Application
ADC| Reading LDR sensor values
I2C| OLED display communication
UART| Sending sensor data to Serial Monitor
GPIO| Controlling LEDs and buzzer

⚙️ Working Principle

1. The DHT22 sensor measures temperature and humidity.
2. The LDR sensor detects changes in light intensity.
3. The STM32 microcontroller reads and processes the sensor data.
4. The measured values are displayed on the OLED screen.
5. UART communication is used to transmit sensor readings to the Serial Monitor.
6. If the temperature exceeds 30°C or humidity exceeds 70%, the alert system is activated using the red LED and buzzer.

✨ Key Features

- Real-time environmental monitoring
- Temperature and humidity measurement
- ADC-based light intensity monitoring
- OLED-based data visualization
- UART serial communication
- Automatic threshold-based alert system
- LED and buzzer indication

🖥️ Simulation

Simulation Platform: Wokwi

Wokwi Project Link: [https://wokwi.com/projects/481463461921378305]

Simulation Screenshots:

- Circuit Diagram
- OLED Display Output
- Serial Monitor Output

📊 Expected Results

The system displays temperature, humidity, and light sensor readings. When the predefined temperature or humidity limits are exceeded, the red LED and buzzer provide an alert. Under normal conditions, the green LED indicates normal operation.

🚀 Future Enhancements

- STM32 HAL-based firmware implementation
- FreeRTOS integration for multitasking
- SD card-based data logging
- Sensor calibration for improved accuracy
- IoT-based remote monitoring

📁 Project Structure

STM32-Environmental-Monitoring/
│
├── Firmware/
│   ├──libraries.txt
│   └── sketch.ino

│
├── Simulation/
│   ├── alert output.png
│   ├── circuit circuit.png
│   └── oled initialize.png
│   
│
└── README.md

📚 Learning Outcomes

Through this project, practical knowledge is gained in:

- STM32 microcontroller programming
- Sensor interfacing
- ADC, I2C, and UART communication
- OLED display interfacing
- Embedded C/C++ programming
- Basic embedded system debugging

👩‍💻 Author

Navamalika B

Electronics and Communication Engineering
Embedded Systems and Advanced Robotics
University College of Engineering, BIT Campus
Anna University, Tiruchirappalli

---

This project demonstrates the practical application of microcontrollers, sensor interfacing, and communication protocols in embedded systems.
