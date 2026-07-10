# Arduino-Based Gas Leakage and Fire Detection System With Prevention and Safety Mechanisms

This project presents a low-cost, real-time gas leakage and fire detection system developed using an Arduino Uno. The system detects combustible gas leakage and flame hazards and automatically activates warning and prevention mechanisms.

## Features

- Real-time combustible gas detection using the MQ-2 gas sensor
- Flame detection using an infrared flame sensor
- Immediate audio warning using a buzzer
- Visual warning using an LED
- Real-time system status display using a 16×2 LCD
- Automatic exhaust fan activation during gas leakage
- Automatic gas supply shutoff using a servo motor
- Emergency response when gas leakage and flame are detected simultaneously

## Hardware Components

- Arduino Uno R3
- MQ-2 Gas Sensor
- Flame Sensor Module
- 16×2 LCD Display
- Active Buzzer
- Red LED
- Servo Motor
- Exhaust Fan
- MOSFET
- 220Ω Resistors
- Breadboard
- Jumper Wires
- USB Power Cable

## Working Principle

The MQ-2 sensor continuously monitors the concentration of combustible gases. When the sensor reading exceeds the predefined safety threshold, the Arduino activates the buzzer, warning LED, exhaust fan, and servo-controlled gas shutoff mechanism.

The flame sensor detects infrared radiation emitted by a flame. When a flame is detected, the Arduino activates the alarm system and displays a warning message on the LCD.

If gas leakage and flame are detected simultaneously, the system enters an emergency state and activates all available safety mechanisms.

## Repository Contents

| File or Folder | Description |
|---|---|
| `Project_Code_Main/Project_Code.ino` | Main Arduino source code |
| `Proteus File/` | Proteus circuit design, libraries, and simulation files |
| `Semulation Code/` | Compiled and simulation-related Arduino files |
| `Connection Setup.jpg` | Hardware connection setup |
| `fan & Wifi Connection .txt` | Fan and Wi-Fi connection information |
| `Project Report.docx` | Complete project report |
| `Project_Proposal.docx` | Project proposal |
| `Project-Presentationt.pptx` | Project presentation |
| `simulation-screenshot.png` | Screenshot of the Proteus simulation |
| `demo-video.mp4` | Project demonstration video stored using Git LFS |

## Simulation Screenshot

![Gas Leakage and Fire Detection System Simulation](./simulation-screenshot.png)

## Project Demo Video

Click the image below to open the project demonstration video:

[![Watch the Project Demo](./simulation-screenshot.png)](./demo-video.mp4)

### Direct Video Link

[▶ Open Project Demonstration Video](./demo-video.mp4)

> **Note:** The demonstration video is stored using Git Large File Storage (Git LFS). Depending on the browser and GitHub preview support, the video may open in a separate page or download before playing.

## Setup Instructions

1. Connect the sensors and output devices according to the circuit diagram.
2. Connect the Arduino Uno to the computer using a USB cable.
3. Open `Project_Code_Main/Project_Code.ino` using the Arduino IDE.
4. Select **Arduino Uno** from the board menu.
5. Select the correct COM port.
6. Verify and compile the Arduino code.
7. Upload the program to the Arduino Uno.
8. Allow the MQ-2 gas sensor sufficient time to warm up.
9. Test the gas and flame sensors in a controlled and safe environment.

## System Response

| Condition | System Response |
|---|---|
| Normal environment | System remains in safe mode |
| Mild gas presence | Warning displayed on the LCD |
| Gas leakage detected | Buzzer, LED, exhaust fan, and gas shutoff activated |
| Flame detected | Buzzer, LED, and flame warning activated |
| Gas and flame detected | Continuous emergency alarm and all safety mechanisms activated |

## Safety Notice

This project is an educational prototype and should not be treated as a certified commercial safety device.

For real-world deployment, certified gas sensors, industrial-grade ventilation systems, professionally installed gas shutoff valves, electrical isolation, and appropriate fire-safety equipment should be used.

## Future Improvements

- IoT-based remote monitoring
- Wi-Fi or GSM notifications
- Mobile application integration
- Solenoid-based gas shutoff valve
- Battery backup system
- Improved sensor calibration and filtering
- Smart-home automation integration

## Authors

Developed as a capstone project for the **Microprocessor and Embedded Systems** course at the **American International University-Bangladesh (AIUB)**.
