# TMIT_MOTORTEST23
The **Motor Test** Project undertaken by team **ThrustMIT 2023-24** aims to test and analyze the working and response of a Commercial M-Class Solid Rocket Motor.

This Project Repository contains a collection of testing projects and files, primarily presented as `Arduino Sketches`, along with the final code programs that were developed and utilised during the testing phase and execution of the MOTOR TEST, conducted on 6th November 2023. These files are the culmination of our exploration, experimentation and research leading upto the final project.

## REPOSITORY CONTENTS  

This repository is organised into various directories representing an aspect of our testing process, as well as two folders for the final implemented codes for both systems. Here's a brief overview of what you'll find:
- **`Motor System`**: Contains an Arduino Sketch (.ino file) titled as **MotorCode2.0**. This is the final program that was uploaded onto the Motor System.
- **`Ground System`**: Contains an Arduino Sketch (.ino file) titled as **GroundCode**. This is the final program that was uploaded onto the Ground System.
- **`Documentation`**: In this directory, you can find project-related documentation, including research notes, technical specifications, and any relevant documentation created during the testing phase.
- **`Testing Projects`**: Here you will find all relevant testing sketches created for testing the working and efficiency of the involved peripherals in the project.
- **`Datasheets`**: Contains datasheets and technical specifications for components and devices used in our testing.

## BACKGROUND
The Motor will be situated on a testbed, where it will be placed upon a Load Cell. Additionally, there will be a Strain Gauge module that will be attached to the nozzle. The Motor is fired via an ignitor device. For the purpose of operations and reference, we shall divide the Avionics Systems into two: Motor and Ground. The microcontroller used for both systems is a Teensy 4.1, and the RF Module required for wireless communication between the two systems in an XBee S2C.  

The Ground System employs a switch-controlled Ignition System with three states, SAFE, ARMED, and LAUNCHED. These are coordinated between the two systems via a Finite State Machine on both sides to ensure safe transition between phases. The Motor Side also employs logging of peripheral data in the built-in SD Card via the peripheral modules. The Strain Gauge Module (BF350) is powered via a Power Distribution Board (PDB), providing approx. 5V voltage to the module, converting the 7.4V it receives from a LiPo Battery. The Load Cell is powered by an Arduino Uno R3 to provide stable 5V input; Both the Arduino and Teensy on Motor Side are powered via a Power Bank through respective USB Cables. 
| Module               | Motor Side | Ground Side  | Description                     |
|----------------------|------------|------------- | --------------------------------|
| Teensy 4.1           | ✓          | ✓           | Microcontroller                 |
| XBee S2C             | ✓          | ✓           | Ignition Seq. Telemetry         |
| RS232/TTL Converter  | ✓          | ✗           | Load Cell Data                  |
| BF350 Strain Gauge   | ✓          | ✗           | Strain Gauge Data               |
| Built-in SD Card     | ✓          | ✗           | Datalogging                     |
| Load Cell Indicator  | ✓          | ✗           | Digital Indicator for Load Cell |
| Ignition Control     | ✗          | ✓           | Switch-Control for Ignition     |

## HOW TO USE
The `Motor` and `Ground` System directories will contain the final sketches. The `Testing Projects` directory contains all used test sketches, which may be used for individual testing or reference of the involved peripherals for future use.

## Contribution Guidelines
This repository has been created for documentation purposes for future reference for **ThrustMIT**.
