# initBuzzer v1.0.0 🔊  

[![Arduino Library Manager](https://img.shields.io/badge/Arduino-Library_Manager-00979D.svg?logo=arduino&logoColor=white)](https://docs.arduino.cc/libraries/initBuzzer/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub release](https://img.shields.io/github/v/release/milad-nikpendar/initBuzzer)](https://github.com/milad-nikpendar/initBuzzer/releases)
[![Author](https://img.shields.io/badge/Author-milad--nikpendar-blueviolet)](https://github.com/milad-nikpendar)

A lightweight ESP32 library for controlling passive buzzers with both simple and RTOS-based classes.

## 📦 Features
- Simple buzzer control using blocking functions
- Advanced non-blocking buzzer control with FreeRTOS
- Support for tone, pulse, and beep generation
- Designed for embedded and industrial applications

## 🛠️ Installation
Download or clone this repository into your Arduino `libraries` folder, or install via PlatformIO.

## 🚀 Getting Started

### Basic Usage
```cpp
#include "initBuzzer.h"

Buzzer buzzer(12); // GPIO pin

void setup() {
  buzzer.begin();
  buzzer.beep(200); // Beep for 200ms
}
```

### RTOS-Based Usage
```cpp
#include "initBuzzer.h"

RtosBuzzer buzzer(12); // GPIO pin

void setup() {
  buzzer.begin();
  buzzer.tone(1000, 300); // Non-blocking tone at 1kHz for 300ms
}
```

## 📚 API Reference

### Buzzer Class
| Method         | Description                              |
|----------------|------------------------------------------|
| `begin()`      | Initializes the buzzer pin               |
| `write(bool)`  | Turns buzzer ON or OFF                   |
| `tone(freq, duration)` | Generates a tone at given frequency and duration |
| `pulse(freq, duration)` | Wrapper for tone with input validation |
| `beep(time)`   | Beep at 1kHz for specified time          |

### RtosBuzzer Class
| Method         | Description                              |
|----------------|------------------------------------------|
| `begin()`      | Initializes buzzer and creates RTOS queue |
| `tone(freq, duration)` | Sends tone data to queue for non-blocking execution |
| `tone(duration)` | Shortcut for 3kHz tone                 |
| `pulse(freq, duration)` | Same as tone() with validation  |

## 📁 Examples
See the `examples/` folder for ready-to-run sketches:
- `SimpleBeep`: Basic buzzer control
- `RtosBeep`: RTOS-based multitasking buzzer

## 🧠 Requirements
- ESP32 board
- Arduino core for ESP32
- FreeRTOS (included in ESP32 core)

## 🧾 License

This project is licensed under the **MIT License** – see [LICENSE](LICENSE) for details.

## ✍️ Author

**Milad Nikpendar**  
GitHub: [milad-nikpendar/initBuzzer](https://github.com/milad-nikpendar/initBuzzer)  
Email: milad82nikpendar@gmail.com  
