<h1 align="center">Instrument Cluster</h1>

<p>A real-time vehicle speed and data display. <p>

## Demo

![Cluster GIF](https://github.com/SEAME-pt/Team02-RaspberryPi/blob/readme/assets/instrumentCluster.gif)

# Team02 RaspberryPi - Car Dashboard System

This repository contains a car dashboard system that runs on a Raspberry Pi, displaying real-time vehicle information on a dashboard screen.

## Overview

The system consists of two main applications:
- **Instrument Cluster** - A QML-based dashboard display
- **MiddleWare** - CAN bus communication handler

## System Architecture

```
Jetson Nano → CAN Bus → Raspberry Pi → Dashboard Display
```

The Jetson Nano sends vehicle data over CAN bus to the Raspberry Pi, which processes and displays the information on a car dashboard interface.

## Components

### 🚗 Instrument Cluster (`Cluster/`)
- Qt/QML-based dashboard application
- Displays speed, battery level, gear, warning lights, and ADAS information
- Real-time lane departure warnings and traffic sign detection
- Custom UI with vehicle lights indicators

### 🔌 MiddleWare (`MiddleWare/`)
- CAN bus communication handler
- Receives data from Jetson Nano via CAN interface (`can0`)
- Publishes vehicle data using Zenoh messaging
- Handles various vehicle systems (lights, battery, speed, ADAS)

🗂️ [Check here](https://github.com/SEAME-pt/Team02-RaspberryPi/blob/80-task-object-detection-in-cluster/MiddleWare/src/can-id-reference-table.md) the CAN ID Reference Table in middleware

## Vehicle Data Supported

- Vehicle speed and gear
- Battery state of charge
- Light indicators (headlights, fog lights, turn signals)
- Lane detection and departure warnings
- Traffic sign detection
- ADAS autonomy levels
- Emergency braking alerts

## Requirements

- Raspberry Pi with CAN interface
- Qt6 with QML support
- Zenoh messaging library
- CAN utilities


### Usage


Once the application is up and running, the instrument cluster will display `real-time speed data` and the `vehicle's battery status` on an LCD screen. The data is continuously updated as it is received **via the CAN bus**.

This project can be deployed and tested in two main environments (in a raspberry pi 4 and locally in you computer). Check the deploy manual [here]

## Testing





We use **LCOV** for test coverage analysis to ensure the reliability and quality of the codebase. Follow the steps below to run the tests:





1. Navigate to the `RaspberryPi/tests` directory:


  ```bash


  cd RaspberryPi/tests


  ```





2. After the tests are executed, a coverage report will be generated. Run the test script:


  ```bash


  ./test.sh


  ```


Make sure all tests pass and the coverage meets the project's standards before submitting any changes. 

## Acknowledgments

- **Qt Framework:** [Qt](https://www.qt.io/) – A cross-platform framework for GUI applications.


- **Raspberry Pi Foundation:** [Raspberry Pi](https://www.raspberrypi.org/) – The small, powerful computer that powers the display side of the project.


- **Arduino:** [Arduino](https://www.arduino.cc/) – A versatile open-source electronics platform used for sensor data collection.


- **CAN Bus Protocol:** [CAN Protocol](https://www.kvaser.com/can/) – The communication protocol used to connect different ECUs in the vehicle.


## The Team 🤝


> Together, we've collaborated to bring this project to life, combining our knowledge, skills, and experience every step of the way. It has been a great journey of learning and growing as a team.


  - <a href="https://github.com/Rui-Pedro-Pires">Rui Pires</a>


  - <a href="https://github.com/ziliolu">Luiza Zilio</a>


  - <a href="https://github.com/luis-ffe">Luis Filipe Carvalho</a>


  - <a href="https://github.com/mjorgecruz">Jorge Cruz</a>




