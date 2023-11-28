# Table-Top Autonomous Vehicle with Arduino Uno/ATmega328P

Welcome to my Table-Top Vehicle project, a bare-metal C implementation for creating a self-navigating vehicle using an Arduino Uno with ATmega328P microcontroller. This project incorporates an SSD1306 OLED driver, an HC-SR04 ultrasonic sensor, and basic DC motors for movement.

I started this project with several goals in mind.
1. Gain familiarity with C
2. Learn how to work directly with datasheets for microcontrollers and peripherals
3. Increase my understanding of low-level communications protocols (mainly I2C and one-wire in this project)
4. Make something fun! I didn't want to create something I'd never look at again once it was finished. I have some plans in the works to expand on this project once I have a functioning prototype

## Features

- **Bare-Metal C Implementation:** The entire codebase is written in bare-metal C, providing a low-level exploration of the Atmega328p. 

- **SSD1306 OLED Driver:** Custom OLED driver for the SSD1306 display, enabling clear and informative visual feedback on the vehicle's status and behavior.

- **TWI/I2C Driver:** Implementation of the Two-Wire Interface (TWI) or I2C driver to facilitate communication between devices, ensuring efficient interaction with peripherals.

- **HC-SR04 Ultrasonic Sensor Driver:** A custom driver for the HC-SR04 ultrasonic distance sensor, enabling accurate and reliable distance measurements for edge detection.

- **Basic DC Motors:** Integration of basic DC motors for movement, allowing the vehicle to navigate and explore its environment autonomously.

**Code Structure**

- `makefile`: Contains the code necessary to link and compile the drivers as well as flash the program onto the Atmega328p 
- `Core/`: Contains the project source code files.
  - `inc`: Contains the header files for the HC-SR04, SSD1306, and TWI drivers, as well as the text library for displaying messages on the OLED screen.
  - `lib`: Contains the TWI driver for the I2C interface between the Atmega328p and the SSD1306.
  - `src`: Contains the source files for the HC-SR04 driver, the SSD1306 driver, and the entry point for the program (main.c)

**Current Progress**

The I2C/TWI driver, SSD1306 driver, HC-SR04 driver, are all functioning, with the current circuit capable of measuring distance and displaying it via the OLED screen to an accuracy of ~3cm.

The movement driver (for the motors) is currently in progress, as is the design of a prototype that is able to support all components.


