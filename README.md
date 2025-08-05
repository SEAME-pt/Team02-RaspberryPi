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
