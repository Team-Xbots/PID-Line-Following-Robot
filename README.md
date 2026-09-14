# PID Line-Following Robot

An ESP32-based high-speed line-following robot using an 8-channel IR sensor array, TB6612FNG motor driver, N20 geared motors, and PID control.

## 🚀 Project Overview

This project is a PID-controlled autonomous line-following robot designed to follow a track accurately and quickly.

The robot continuously reads the position of the line using an 8-channel infrared sensor array. The ESP32 processes the sensor data and calculates the position error. A PID controller then generates a correction value that adjusts the speed of the left and right motors.

## 🧠 Main Features

- ESP32-based control system
- 8-channel IR sensor array
- PID-based line tracking
- TB6612FNG dual motor driver
- N20 geared motors
- Dynamic motor speed control
- Sharp-turn correction
- Line-lost detection and recovery
- Compact custom chassis
- CAD-designed mechanical structure

## 🔧 Hardware

| Component | Description |
|---|---|
| ESP32 | Main microcontroller |
| 8-channel IR sensor array | Line detection |
| TB6612FNG | Dual DC motor driver |
| N20 motors | Drive motors |
| DC-DC step-down module | Power regulation |
| Battery | Main power source |
| Tactile button | User control |
| Ball caster | Front/rear support |

## ⚙️ Control System

The robot uses a PID controller consisting of:

- Proportional (P)
- Integral (I)
- Derivative (D)

The controller calculates the difference between the desired line position and the measured sensor position.

The correction is then applied to the two motors:

```text
Left Motor  = Base Speed + PID Correction
Right Motor = Base Speed - PID Correction
This allows the robot to continuously correct its direction while following the line.

🔌 Electronics

The ESP32 is connected to:

8-channel IR sensor array
TB6612FNG motor driver
Left N20 motor
Right N20 motor
Power regulation circuit
Control button

Detailed wiring information is available in:

hardware/Component_&_Connection/

🏗️ Mechanical Design

The robot chassis and mechanical components were designed using CAD tools.

CAD files and mechanical drawings are available in:

hardware/CAD/

💻 Software

The control program is written for the ESP32 using the Arduino environment.

Source code:

src/pid_line_follower/

📁 Repository Structure
PID-Line-Following-Robot/
│
├── README.md
│
├── src/
│   └── pid_line_follower/
│       └── sensor1_pid_full.ino
│
├── hardware/
│   ├── CAD/
│   └── Component_&_Connection/
│
└── documentation/
    └── report/
        └── PID_LineFollowing_Robot_Report.docx
📚 Documentation

The complete project report is available here:

documentation/report/PID_LineFollowing_Robot_Report.docx

The report contains the project design, hardware information, control approach, implementation details, and source code.

🧪 Testing

The robot is intended to be tested on a line track under different conditions, including:

Straight sections
Curves
Sharp turns
Different speeds
Line-loss conditions
🔮 Future Improvements

Possible future improvements include:

Automatic PID parameter tuning
Higher-speed optimization
Improved sensor calibration
Better battery monitoring
Wireless configuration
Real-time telemetry
Improved chassis optimization
👥 Team

Team-Xbots

GitHub Organization:

https://github.com/Team-Xbots

📄 License

This project is maintained by Team-Xbots.
