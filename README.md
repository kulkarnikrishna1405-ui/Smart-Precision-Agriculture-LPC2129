Smart Precision Agriculture Monitoring and Automated Irrigation System using LPC2129

Project Overview

The Smart Precision Agriculture Monitoring and Automated Irrigation System is an embedded system developed using the LPC2129 ARM7 microcontroller.

The main objective of this project is to continuously monitor agricultural field conditions using multiple sensors and help farmers make efficient irrigation decisions.

The system collects sensor information, processes the readings using the LPC2129 microcontroller, and displays the monitoring results through UART serial communication on a PC terminal.

Objectives

- Continuously monitor soil moisture.
- Monitor water availability in the storage tank.
- Measure surrounding temperature.
- Detect rainfall conditions.
- Monitor sunlight intensity.
- Detect fire using a flame sensor.
- Detect movement using a PIR sensor.
- Support efficient irrigation decisions.
- Reduce unnecessary water consumption and manual effort.

Hardware Components

Component| Purpose
LPC2129 ARM7| Main microcontroller
Soil Moisture Sensor| Measures soil moisture
Water Level Sensor| Monitors tank water level
LM35| Measures temperature
Rain Sensor| Detects rainfall
LDR| Measures light intensity
Flame Sensor| Detects possible fire
PIR Sensor| Detects motion
16×2 LCD| Displays system information
Relay Module| Controls the water pump
Water Pump| Supplies irrigation water
LEDs| Provides visual indications
Buzzer| Provides audible alerts
DS1307 RTC| Maintains date and time
AT24C08 EEPROM| Stores important data
UART| Communicates with the PC terminal
ADC| Converts analog sensor signals

Software Requirements

- Embedded C
- Keil µVision IDE
- ARM7 LPC2129 microcontroller
- Flash Magic (for programming the controller)
- Serial terminal software

Working Principle

1. The LPC2129 initializes the required peripherals.
2. Analog sensor readings are acquired using the ADC.
3. Digital sensor conditions are monitored through GPIO.
4. The controller processes the sensor readings.
5. Soil moisture, water availability, and rainfall conditions are used to determine irrigation requirements.
6. Environmental and safety sensor conditions are monitored.
7. Sensor readings and system status are displayed through UART on the PC terminal.
8. RTC and EEPROM interfaces are included for timekeeping and data storage.

Sensor Interface

Sensor| Interface
Soil Moisture Sensor| ADC
Water Level Sensor| ADC
LM35 Temperature Sensor| ADC
LDR Sensor| ADC
Rain Sensor| GPIO
Flame Sensor| GPIO
PIR Motion Sensor| GPIO

Features

- Multi-sensor agricultural monitoring.
- ADC-based analog sensor measurement.
- GPIO-based digital sensor monitoring.
- UART serial communication.
- Temperature measurement using LM35.
- Rain and fire detection.
- Motion detection for field monitoring.
- Irrigation decision logic.
- RTC and EEPROM interfacing.

Modules Excluded

The following modules are intentionally excluded from this implementation:

- ESP8266 Wi-Fi and ThingSpeak cloud connectivity.
- SD Card data logging.
- MCP2551 CAN communication.
- DHT22 temperature and humidity sensor.

Project Directory Structure

Smart-Precision-Agriculture-LPC2129/
│
├── README.md
├── header.h
├── main_agri.c
├── adc.c
├── uart.c
├── delay.c
├── lcd.c
├── i2c_driver.c
├── rtc.c
└── eeprom.c

Expected Serial Terminal Output

=============================================
SMART PRECISION AGRICULTURE MONITORING SYSTEM
=============================================

Controller     : LPC2129 ARM7
Project Status : RUNNING

---------------------------------------------
Soil Moisture  : 58%
Water Level    : 82%
Temperature    : 30 C
Rain Status    : NO
Light Intensity: HIGH
Flame Status   : SAFE
Motion Status  : CLEAR

Pump Status    : OFF
Relay Status   : OFF

RTC Date       : DD/MM/YY
RTC Time       : HH:MM:SS

System Status  : NORMAL
---------------------------------------------

Monitoring...

Note: The values above are illustrative. Actual readings depend on sensor calibration and hardware operation.

Future Enhancements

- IoT-based remote monitoring.
- Cloud-based agricultural data analysis.
- Long-term data logging.
- Multi-field agricultural monitoring.
- Improved irrigation automation.
- Advanced environmental monitoring.

Applications

- Agricultural fields.
- Greenhouses.
- Nursery management.
- Smart irrigation systems.
- Soil moisture monitoring.
- Water resource management.

Conclusion

This project demonstrates the use of an ARM7-based embedded system for agricultural monitoring and irrigation management. By integrating multiple sensors with the LPC2129 microcontroller, the system helps monitor important agricultural parameters and supports efficient water management.

---

Project: Smart Precision Agriculture Monitoring and Automated Irrigation System using LPC2129

Platform: LPC2129 ARM7

Programming Language: Embedded C
