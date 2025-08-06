#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <memory>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "zenoh.hxx"
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <cmath>

using namespace zenoh;

int main(int argc, char** argv)
{
    std::vector<uint8_t> laneDataBuffer; 
    struct ifreq ifr;
    struct sockaddr_can addr;
    std::vector<uint8_t> rightLaneBuffer;
    std::vector<uint8_t> leftLaneBuffer;

    float rightLane[3] = {0.0f};
    float leftLane[3] = {0.0f};
    bool rightReceived[3] = {false};
    bool leftReceived[3] = {false};

    int canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (canSocket < 0)
    {
        std::cerr << "Cannot create CAN socket!" << std::endl;
        exit(-1);
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(canSocket, SIOCGIFINDEX, &ifr);

    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(canSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "Cannot bind CAN socket!" << std::endl;
        close(canSocket);
        exit(1);
    }
    std::cerr << "Attempting to open Zenoh session..." << std::endl;
    std::cout << "CAN socket bound to can0 interface successfully."
              << std::endl;

    std::unique_ptr<zenoh::Session> session;
    try
    {
        if (argc == 2)
        {
            std::cout << "Using configuration file: " << argv[1] << std::endl;
            auto config = Config::from_file(argv[1]);
            session     = std::make_unique<zenoh::Session>(
                zenoh::Session::open(std::move(config)));
        }
        else
        {
            std::cout << "Using default configuration." << std::endl;
            auto config = Config::create_default();
            session     = std::make_unique<zenoh::Session>(
                zenoh::Session::open(std::move(config)));
        }
    }
    catch (const zenoh::ZException& e)
    {
        std::cerr << "Failed to open Zenoh session: " << e.what() << std::endl;
        close(canSocket);
        exit(1);
    }

    auto speed_pub =
        session->declare_publisher(zenoh::KeyExpr("Vehicle/1/Speed"));
    auto beamLow_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Beam/Low"));
    auto beamHigh_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Beam/High"));
    auto running_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Running"));
    auto parking_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Parking"));
    auto fogRear_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Fog/Rear"));
    auto fogFront_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Fog/Front"));
    auto brake_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Brake"));
    auto hazard_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/Hazard"));
    auto directionIndicatorLeft_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/DirectionIndicator/Left"));
    auto directionIndicatorRight_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Body/Lights/DirectionIndicator/Right"));
    auto currentGear_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/Transmission/CurrentGear"));
    auto current_voltage_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurentVoltage"));
    auto current_current_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurrentCurrent"));
    auto current_power_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurrentPower"));
    auto state_of_charge_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/StateOfCharge"));
    auto right_lanes_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Scene/Lanes/Right"));
    auto left_lanes_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Scene/Lanes/Left"));
    auto obstacleWarning_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/ObstacleDetection/Warning"));
    auto laneDeparture_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/LaneDeparture/Detected"));
    auto sae0_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_0"));
    auto sae1_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1"));
    auto sae2_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_2"));
    auto sae5_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5"));
    auto cruise_control_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/CruiseControl"));
    auto speedLimit_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/SpeedLimit"));
    auto stopSign_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/Stop"));
    auto yieldSign_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/Yield"));
    auto pedestrianZone_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/PedestrianZone"));
    auto trafficLight_pub = session->declare_publisher( 
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/TrafficLight"));
    auto dangerSign_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/DangerSign"));

    while (1)
    {
        struct can_frame frame;

        int nbytes = read(canSocket, &frame, sizeof(struct can_frame));
        if (nbytes < 0)
        {
            std::cerr << "Error reading CAN frame!" << std::endl;
            continue;
        }
        if (frame.can_id == 0x01 && frame.can_dlc >= 4)
        {
            int32_t rpm;
            double wheelDiameter = 0.067;

            memcpy(&rpm, frame.data, sizeof(int32_t));
            rpm = ntohl(rpm);

            if (rpm >= -1000 && rpm <= 1000)
            {
                double wheel_circumference = wheelDiameter * M_PI;
                double speed_m_per_min = rpm * wheel_circumference;

                std::string speed_str = std::to_string(speed_m_per_min);
                std::cout << "Publishing speed: " << speed_str << " m/min" << std::endl;
                speed_pub.put(speed_str.c_str());
            }
        }
        else if (frame.can_id == 0x02)
        {
            double battery;

            memcpy(&battery, frame.data, sizeof(double));

            float percentage = ((battery - 9.5f) / (12.6f - 9.5f)) * 100.0f;
            battery          = std::min(100.0f, std::max(0.0f, percentage));
            std::string battery_str = std::to_string(battery);

            std::cout << "Publishing battery state of charge: " << battery_str << "%" << std::endl;
            state_of_charge_pub.put(battery_str.c_str());
        }
        else if (frame.can_id >= 0x700 && frame.can_id <= 0x707)
        {
            bool lightState = frame.data[0] != 0; // first byte indicates ON/OFF state
            switch (frame.can_id)
            {
            case 0x700:
                directionIndicatorLeft_pub.put(std::to_string(lightState));
                std::cout << "Publishing Direction Indicator Left: " << lightState << std::endl;
                break;
            case 0x701:
                directionIndicatorRight_pub.put(std::to_string(lightState));
                std::cout << "Publishing Direction Indicator Right: " << lightState << std::endl;
                break;
            case 0x702:
                beamLow_pub.put(std::to_string(lightState));
                std::cout << "Publishing Beam Low: " << lightState << std::endl;
                break;
            case 0x703:
                beamHigh_pub.put(std::to_string(lightState));
                std::cout << "Publishing Beam High: " << lightState << std::endl;
                break;
            case 0x704:
                fogFront_pub.put(std::to_string(lightState));
                std::cout << "Publishing Fog Front: " << lightState << std::endl;
                break;
            case 0x705:
                fogRear_pub.put(std::to_string(lightState));
                std::cout << "Publishing Fog Rear: " << lightState << std::endl;
                break;
            case 0x706:
                hazard_pub.put(std::to_string(lightState));
                std::cout << "Publishing Hazard: " << lightState << std::endl;
                break;
            case 0x707:
                parking_pub.put(std::to_string(lightState));
                std::cout << "Publishing Parking: " << lightState << std::endl;
                break;
            default:
                std::cerr << "Unknown CAN ID for lights: " << frame.can_id << std::endl;
                break;
            }
        }
        else if (frame.can_id == 0x04)
        {
            int gear;

            memcpy(&gear, frame.data, sizeof(gear));

            std::cout << "Can received gear: " << gear << std::endl;
            currentGear_pub.put(std::to_string(gear));
        }
        if (frame.can_id == 0x100 || frame.can_id == 0x101)
        {
            int index;
            float value;

            memcpy(&index, &frame.data[0], sizeof(int));
            memcpy(&value, &frame.data[4], sizeof(float));

            std::cout << "[CAN] "
                << ((frame.can_id == 0x101) ? "Right" : "Left")
                << " Lane - Index: " << index
                << ", Value: " << value << std::endl;

            if (frame.can_id == 0x100)
            {
                leftLane[index] = value;
                leftReceived[index] = true;

                if (leftReceived[0] && leftReceived[1] && leftReceived[2])
                {
                    std::ostringstream stream;
                    for (int i = 0; i < 3; ++i)
                        stream << leftLane[i] << " ";

                    std::cout << "Publishing left lane: " << stream.str() << std::endl;
                    left_lanes_pub.put(stream.str());
                    std::fill(std::begin(leftReceived), std::end(leftReceived), false);
                }
            }
            else
            {
                rightLane[index] = value;
                rightReceived[index] = true;

                if (rightReceived[0] && rightReceived[1] && rightReceived[2])
                {
                    std::ostringstream stream;
                    for (int i = 0; i < 3; ++i)
                        stream << rightLane[i] << " ";
                    
                    std::cout << "Publishing right lane: " << stream.str() << std::endl;
                    right_lanes_pub.put(stream.str());
                    std::fill(std::begin(rightReceived), std::end(rightReceived), false);
                }
            }
        }
        else if (frame.can_id == 0x200)
            obstacleWarning_pub.put("1");
        else if (frame.can_id == 0x301) //left lane departure
        {
            std::cout << "Publishing lane departure to left." << std::endl;
            laneDeparture_pub.put("10");
        }
        else if (frame.can_id == 0x302) //left lane departure off
        {
            std::cout << "Publishing lane departure to left or right off." << std::endl;
            laneDeparture_pub.put("11"); 
        }
        else if(frame.can_id == 0x303) //right lane departure
        {
            std::cout << "Publishing lane departure to right." << std::endl;
            laneDeparture_pub.put("20"); 
        }
        else if (frame.can_id == 0x400)
            sae0_pub.put("0");
        else if (frame.can_id == 0x401)
            sae1_pub.put("1");
        else if (frame.can_id == 0x402)
            sae2_pub.put("2");
        else if (frame.can_id == 0x405)
            sae5_pub.put("5");
        else if (frame.can_id == 0x406)
        {
            std::cout << "Publishing cruise control activated." << std::endl;
            cruise_control_pub.put("1");
        }
        else if (frame.can_id == 0x407)
        {
            std::cout << "Publishing cruise control deactivated." << std::endl;
            cruise_control_pub.put("0");
        }
        else if (frame.can_id == 0x500)
        {
            std::cout << "Publishing speed limit: 50km/h" << std::endl;
            speedLimit_pub.put("50");
        }
        else if (frame.can_id == 0x505)
        {
            std::cout << "Publishing speed limit: 80km/h" << std::endl;
            speedLimit_pub.put("80");
        }
        else if (frame.can_id == 0x501)
        {
            std::cout << "Publishing stop sign detected. (11)" << std::endl;
            stopSign_pub.put("1");
        }
        else if (frame.can_id == 0x502)
        {
            std::cout << "Publishing yield sign detected (12)." << std::endl;
            yieldSign_pub.put("1");
        }
        else if (frame.can_id == 0x503)
        {
            std::cout << "Publishing pedestrian zone sign detected. (13)" << std::endl;
            pedestrianZone_pub.put("1");
        }
        else if (frame.can_id == 0x504)
        {
            std::cout << "Publishing danger sign detected. (17)" << std::endl;
            dangerSign_pub.put("1");
        }
        else if (frame.can_id == 0x600)
        {
            std::cout << "Publishing traffic sign detected: yellow (14)" << std::endl;
            trafficLight_pub.put("yellow");
        }
        else if (frame.can_id == 0x601)
        {
            std::cout << "Publishing traffic sign detected: green (15)" << std::endl;
            trafficLight_pub.put("green");
        }
        else if (frame.can_id == 0x602)
        {
            std::cout << "Publishing traffic sign detected: red (16)" << std::endl;
            trafficLight_pub.put("red");
        }
        
        usleep(10);
    }
    return 0;
}