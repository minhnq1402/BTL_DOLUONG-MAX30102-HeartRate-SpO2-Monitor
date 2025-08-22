# ⚡ BTL_DOLUONG-MAX30102-HeartRate-SpO2-Monitor

<div align="center">

**A PlatformIO project for monitoring heart rate and SpO2 using the MAX30102 sensor.**

</div>

## 📖 Overview

This project uses the PlatformIO framework to implement a heart rate and SpO2 monitor utilizing the MAX30102 sensor.  The code is written in C++ and is designed for embedded systems development.  It reads sensor data, processes it to extract heart rate and SpO2 levels, and potentially outputs this data to a display or other interface (implementation details not provided in the repository).

## ✨ Features

- Reads heart rate and SpO2 data from the MAX30102 sensor.
- (Presumed) Processes raw sensor data to calculate heart rate and SpO2.
- (Presumed) Outputs calculated values to a display or communication interface.


## 🛠️ Tech Stack

- **Language:** C++
- **Framework:** PlatformIO
- **Microcontroller:**  (Requires further analysis of `platformio.ini` to determine the specific microcontroller)
- **Sensor:** MAX30102

## 🚀 Quick Start

### Prerequisites

- PlatformIO IDE installed.  (https://platformio.org/getstarted)
- A microcontroller supported by PlatformIO (see `platformio.ini` for details).
- A MAX30102 sensor properly wired to the microcontroller.

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/minhnq1402/BTL_DOLUONG-MAX30102-HeartRate-SpO2-Monitor.git
   cd BTL_DOLUONG-MAX30102-HeartRate-SpO2-Monitor
   ```

2. **Open in PlatformIO:** Open the project folder in the PlatformIO IDE.

3. **Build and Upload:** PlatformIO will automatically detect the project configuration. Use the PlatformIO IDE to build and upload the code to your microcontroller.  Specific build and upload commands depend on your PlatformIO setup.

## 📁 Project Structure

```
BTL_DOLUONG-MAX30102-HeartRate-SpO2-Monitor/
├── .gitignore
├── .vscode/             # VS Code project settings (if any)
├── include/             # Header files (likely sensor library includes)
├── lib/                 # Libraries (possibly custom or third-party)
├── platformio.ini      # PlatformIO project configuration
├── src/                 # Source code for the heart rate monitor
└── test/                # Test files (if any)
```

## ⚙️ Configuration

The primary configuration is within the `platformio.ini` file.  This file specifies the board, framework, libraries, and other build settings.  Refer to the `platformio.ini` file for detailed configuration options.  TODO: Analyze `platformio.ini` for more precise configuration details.

## 🧪 Testing

TODO:  Add testing information once test files in the `/test` directory are analyzed.


## 🤝 Contributing

Contributions are welcome!  Please open an issue to discuss potential changes before creating a pull request.

## 📄 License

TODO: Add License information.


---

<div align="center">

**Made with ❤️ by minhnq1402**

</div>

