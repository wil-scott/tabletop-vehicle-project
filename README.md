# Table-Top Vehicle with Arduino Uno/ATmega328P
Welcome to my Table-Top Vehicle project, a bare-metal C implementation for creating a self-navigating vehicle using an Arduino Uno with the ATMEGA328P microcontroller. This project incorporates an SSD1306 OLED screen, an HC-SR04 ultrasonic sensor, and two DC motors driven by an L293D module for movement.

After finalizing the driver for the DC Motors/L293D module and constructing a DIY car chassis, the project has hit a tipping point: a functional prototype!

https://github.com/wil-scott/autonomous-vehicle-project/assets/90657631/0c05ac46-4df9-4550-b802-7ffb9257c222

## How It's Made:
Tech used: C, Make, AVR-GCC, Vim, Gedit.
Components used: Arduino Uno (ATMEGA328p), HC-SR04 Ultrasonic Distance sensor, SSD1306 32x128 OLED screen, 2x generic DC Motors.

The goal of this project was to make it as lightweight, small, and portable as possible. This meant using as few external libraries as possible, eschewing IDEs, and using bare-metal C to create the drivers and program logic for this device. All code was developed on a linux platform (either Ubuntu or Raspberry Pi OS Lite).

If your machine has GCC, Make, and AVR-GCC installed, and you have access to your command line/terminal program, then you have all the tools necessary to compile and flash this program.

### Why did I choose this stack?
The goal of this project was to get real experience with low-level programming concepts. This meant no I2C libraries, no LED/OLED libraries, and certainly no Arduino libraries. I wanted to make sure that I had the opportunity to understand and 'grok' the concepts that are commonly abstracted away by these external libraries.

I also wanted to decrease my dependence on IDEs and take a more bare-bones approach to development so that I could be comfortable developing in any environment. This meant, first, trying out Gedit and then going all-in by taking the plunge into Vim. If this sounds like a lot to handle all at once for a beginner/intro project, I would agree with you, but it has also been a great way to learn and I'm already looking for the next challenge.

## Lessons Learned
Where to start? I started this project with only a high-level understanding of I2C, Timers, Interrupts (and ISRs), and what a driver even was. As a result, trying to get started meant dealing with some very intimidating concepts for a beginner and trying to navigate several steep learning curves. I learned:
1. How to dig into a datasheet (and that not all datasheets were created equal).
2. How to use/write Makefiles.
3. How to incorporate Vim into my development workflow.
4. How to use ISRs.
5. How to use hardware pin interrupts in the AVR platform.
6. How to use timers.
7. How I2C works.

And much, much more, but for brevity's sake I'll stop here. 

## How to Run the Code
This guide assumes you are using a Linux platform.
1. Install the AVR-GCC toolchain using ```sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude```.
2. Install Make: ```sudo apt-get install build-essential``` (NOTE: This command will install additional tools on your system as well!).
3. Clone the repository on your local machine.
4. Navigate to the top-level of the repository and run ```make all``` via the command line.
5. Once the compilation is complete, connect the Arduino Uno/ATMEGA328p to your device and run ```make flash```.

## Pinout/Schematic
If you want to try running this program on your own Arduino UNO/ATMEGA328p tabletop car, then you can use the following schematic to mimic the design that I used:

![tabletop-vehicle_schem](https://github.com/wil-scott/autonomous-vehicle-project/assets/90657631/785eda1f-31e2-47c0-ae9a-3face1ba7fd9)

## Next Steps
While I plan to get started on some other projects right away, I will also be working at creating a UART/serial driver for this device so that I can interface the ATMEGA328p with an ESP8266 ESP-01 in order to add IoT functionality. Once complete, I plan to write a linux driver capable of sending simple commands to the car (e.g. start, stop, turn, etc.). 

