## 🗂️ CAN ID Reference Table

This table defines the meaning of each CAN ID the middlewareApp handles, along with expected data and the Zenoh topic it publishes to.

| CAN ID (Hex) | Description                         | Payload Format        | Zenoh Topic(s) Published To                                                   |
|--------------|-------------------------------------|------------------------|--------------------------------------------------------------------------------|
| 0x01       | Wheel RPM                           | int32_t rpm (4 bytes) | Vehicle/1/Speed – calculated speed in km/h                                  |
| 0x02       | Battery Voltage                     | double voltage (8 bytes) | Vehicle/1/Powertrain/TractionBattery/StateOfCharge                          |
| 0x03       | Lights Status Bitmask               | uint8_t bitfield (1 byte) | Various topics (see below)                                                    |
| 0x04       | Current Gear                        | int gear (4 bytes)   | Vehicle/1/Powertrain/Transmission/CurrentGear                               |
| 0x100      | Left Lane Line (index + value)      | int index + float value | Vehicle/1/Scene/Lanes/Left                                                  |
| 0x101      | Right Lane Line (index + value)     | int index + float value | Vehicle/1/Scene/Lanes/Right                                                 |
| 0x200      | Obstacle Warning                    | –                      | Vehicle/1/ADAS/ObstacleDetection/Warning                                    |
| 0x301      | Lane Departure Detected             | –                      | Vehicle/1/ADAS/LaneDeparture/Detected = "1"                               |
| 0x302      | Lane Departure Cleared              | –                      | Vehicle/1/ADAS/LaneDeparture/Detected = "0"                               |
| 0x400      | SAE Autonomy Level: 0               | –                      | Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_0 = "0"                            |
| 0x401      | SAE Autonomy Level: 1               | –                      | Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1 = "1"                            |
| 0x405      | SAE Autonomy Level: 5               | –                      | Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5 = "5"                            |
| 0x500      | Speed Limit Sign                    | int kmh (4 bytes)    | Vehicle/1/Environment/RoadSigns/SpeedLimit                                  |
| 0x501      | Stop Sign Detected                  | –                      | Vehicle/1/Environment/RoadSigns/Stop = "1"                                |
| 0x502      | Yield Sign Detected                 | –                      | Vehicle/1/Environment/RoadSigns/Yield = "1"                               |
| 0x503      | Pedestrian Zone Sign Detected       | –                      | Vehicle/1/Environment/RoadSigns/PedestrianZone = "1"                      |
| 0x600      | Traffic Light – Yellow              | –                      | Vehicle/1/Environment/RoadSigns/TrafficLight = "yellow"                   |
| 0x601      | Traffic Light – Green               | –                      | Vehicle/1/Environment/RoadSigns/TrafficLight = "green"                    |
| 0x602      | Traffic Light – Red                 | –                      | Vehicle/1/Environment/RoadSigns/TrafficLight = "red"                      |

---

### 💡 Light Bitmask (CAN ID 0x03)

Each bit in the uint8_t bitfield corresponds to a vehicle light:

| Bit Position | Light Function                  | Zenoh Topic                                                 |
|--------------|----------------------------------|--------------------------------------------------------------|
| 0            | Right Direction Indicator       | Vehicle/1/Body/Lights/DirectionIndicator/Right            |
| 1            | Left Direction Indicator        | Vehicle/1/Body/Lights/DirectionIndicator/Left             |
| 2            | Low Beam                        | Vehicle/1/Body/Lights/Beam/Low                            |
| 3            | High Beam                       | Vehicle/1/Body/Lights/Beam/High                           |
| 4            | Front Fog Light                 | Vehicle/1/Body/Lights/Fog/Front                           |
| 5            | Rear Fog Light                  | Vehicle/1/Body/Lights/Fog/Rear                            |
| 6            | Hazard Light                    | Vehicle/1/Body/Lights/Hazard                              |
| 7            | Parking Light                   | Vehicle/1/Body/Lights/Parking                             |l