# RFID Pass V1

**Arduino-Based RFID Access Control System**

RFID Pass V1 is an embedded electronics project developed using an Arduino Uno R3. It demonstrates a basic RFID access-control system with badge identification, a 16x2 LCD display, and relay activation.

The project was designed to explore embedded C++ programming, RFID technology, electronic circuits, and access-control principles.

## Project Overview

The system reads RFID cards using an MFRC522 reader and compares their unique identifiers (UIDs) with predefined values stored in the Arduino program.

Depending on the detected badge, the system displays an appropriate message and controls the relay.

**Main features:**
- RFID badge detection using MFRC522.
- Authorized and unauthorized badge identification.
- 16x2 I2C LCD status display.
- 5V relay activation for authorized badges.
- Serial Monitor output for debugging and monitoring.
- Access denied by default for unknown badges.

## Hardware Components

| Component | Quantity |
|---|---|
| Arduino Uno R3 | 1 |
| RFID RC522 Reader (13.56 MHz) | 1 |
| LCD 16x2 I2C Display | 1 |
| 5V Single-Channel Relay Module | 1 |
| Breadboard | 1 |
| Male-to-Male Jumper Wires | As needed |
| Male-to-Female Jumper Wires | As needed |
| USB-A to USB-B Cable | 1 |

## Circuit Diagram

The following diagram illustrates the complete hardware setup, including the Arduino Uno, RC522 RFID reader, LCD display, and relay module.

![RFID Pass V1 - Complete Wiring Diagram](<img width="2880" height="2160" alt="IMG_2436" src="https://github.com/user-attachments/assets/68438e15-8544-49c8-9411-3262081ea2f9" />

)

*Figure 1 — Complete RFID Pass V1 circuit diagram.*

## System Operation

### Access Granted

When an authorized RFID badge is detected, the Arduino validates its UID and activates the relay for 500 milliseconds.

The LCD displays:

```text
ACCES AUTORISE
Ouverture...
```

![RFID Pass V1 - Access Granted](<img width="2880" height="2160" alt="IMG_2434" src="https://github.com/user-attachments/assets/a41976a7-e358-4072-af4b-6a376e764671" />

)

*Figure 2 — Authorized RFID badge detected and relay activated.*

### Access Denied

When an unauthorized or unknown RFID badge is detected, the system denies access and keeps the relay inactive.

For a known but unauthorized badge, the LCD displays:

```text
ACCES REFUSE
Badge bleu
```

For an unknown badge:

```text
BADGE INCONNU
ACCES REFUSE
```

![RFID Pass V1 - Access Denied](<img width="2880" height="2160" alt="IMG_2435" src="https://github.com/user-attachments/assets/56c9bd8f-617b-4d8b-b765-c0e86f2c7361" />

)

*Figure 3 — Unauthorized RFID badge detected.*

After two seconds, the system returns to the standby screen:

```text
RFID PASS V1
Presentez badge
```

## Pin Configuration

| Component | Arduino Uno Pin |
|---|---|
| RC522 SDA / SS | D10 |
| RC522 RST | D9 |
| RC522 MOSI | D11 |
| RC522 MISO | D12 |
| RC522 SCK | D13 |
| Relay IN | D7 |
| LCD SDA | A4 |
| LCD SCL | A5 |

The RC522 must be powered at 3.3V. Its signal pins also use 3.3V logic, so appropriate level shifting or verified electrical compatibility is required when connecting it to the 5V Arduino Uno.

The LCD and relay power connections must match the specifications of the actual modules.

## Software Requirements

- Arduino IDE
- Arduino Uno board support
- MFRC522 library
- LiquidCrystal_I2C library
- SPI library
- Wire library

## Installation

1. Download or clone the repository.
2. Open `src/RFID-Pass-V1.ino` using Arduino IDE.
3. Install the required libraries.
4. Connect the components according to the circuit diagram.
5. Select **Arduino Uno** as the board.
6. Select the correct serial port.
7. Compile and upload the program.
8. Open the Serial Monitor at **9600 baud**.
9. Present an RFID badge to test the system.

## Project Structure

```text
RFID-Pass-V1/
├── README.md
├── src/
│   └── RFID-Pass-V1.ino
└── images/
    ├── wiring-diagram.png
    ├── access-granted.jpg
    └── access-denied.jpg
```

## Technical Details

| Parameter | Value |
|---|---|
| Microcontroller | Arduino Uno R3 |
| Programming Language | C++ / Arduino |
| RFID Module | MFRC522 |
| RFID Frequency | 13.56 MHz |
| Communication | SPI |
| LCD Interface | I2C |
| LCD Address | 0x27 |
| Relay Control Pin | D7 |
| Relay Logic | Active LOW |
| Relay Activation Duration | 500 ms |
| Serial Communication | 9600 baud |

## Security Limitations

RFID Pass V1 is an educational prototype and is not intended for production access-control installations.

The current implementation uses RFID card UIDs for identification. UID-based authorization alone is not secure authentication because identifiers can potentially be cloned or emulated.

The project also uses hardcoded badge identifiers rather than a secure credential-management system.

External locks or other higher-power loads require a suitable power supply, electrical isolation, and appropriate protection. They must never be powered directly from Arduino I/O pins.

## Future Improvements

-
