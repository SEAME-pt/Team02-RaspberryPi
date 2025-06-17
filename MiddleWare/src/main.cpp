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
#include <arpa/inet.h>  // For ntohl
#include <cmath>        // For M_PI

using namespace zenoh;

int main(int argc, char** argv)
{
    std::vector<uint8_t> laneDataBuffer; 
    struct ifreq ifr;
    struct sockaddr_can addr;
    std::vector<uint8_t> rightLaneBuffer;
    std::vector<uint8_t> leftLaneBuffer;

    // std::vector<std::string> objectTypes = { "car", "pedestrian", "cyclist" };
    // std::vector<QJsonObject> objectList;

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
    auto sae5_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5"));
    auto speedLimit_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/SpeedLimit"));
    auto stopSign_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/Stop"));
    auto yieldSign_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/Yield"));
    auto pedestrianZone_pub = session->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/PedestrianZone"));



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
                double speed_kmh = rpm * wheel_circumference * 60.0 / 1000.0;

                std::string speed_str = std::to_string(speed_kmh);
                std::cout << "Publishing speed: " << speed_str << " km/h" << std::endl;
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
        else if (frame.can_id == 0x03)
        {
            char lights;

            memcpy(&lights, frame.data, sizeof(char));

            printf("Can received lights: ");
            for (int i = 7; i >= 0; i--)
            {
                printf("%d", (lights >> i) & 0x01);
            }
            printf("\n");

            directionIndicatorRight_pub.put(
                std::to_string((lights & (1 << 0)) != 0));
            directionIndicatorLeft_pub.put(
                std::to_string((lights & (1 << 1)) != 0));
            beamLow_pub.put(std::to_string((lights & (1 << 2)) != 0));
            beamHigh_pub.put(std::to_string((lights & (1 << 3)) != 0));
            fogFront_pub.put(std::to_string((lights & (1 << 4)) != 0));
            fogRear_pub.put(std::to_string((lights & (1 << 5)) != 0));
            hazard_pub.put(std::to_string((lights & (1 << 6)) != 0));
            parking_pub.put(std::to_string((lights & (1 << 7)) != 0));
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
        else if (frame.can_id == 0x301)
            laneDeparture_pub.put("1");
        else if (frame.can_id == 0x302)
            laneDeparture_pub.put("0");
        else if (frame.can_id == 0x400)
            sae0_pub.put("0");
        else if (frame.can_id == 0x401)
            sae1_pub.put("1");
        else if (frame.can_id == 0x405)
            sae5_pub.put("5");
        else if (frame.can_id == 0x500)
        {
            int speedLimit;

            memcpy(&speedLimit, frame.data, sizeof(int));
            speedLimit = ntohl(speedLimit);

            std::cout << "Publishing speed limit: " << speedLimit << " km/h" << std::endl;
            speedLimit_pub.put(std::to_string(speedLimit).c_str());
        }
        else if (frame.can_id == 0x501)
        {
            std::cout << "Publishing stop sign detected." << std::endl;
            stopSign_pub.put("1");
        }
        else if (frame.can_id == 0x502)
        {
            std::cout << "Publishing yield sign detected." << std::endl;
            yieldSign_pub.put("1");
        }
        else if (frame.can_id == 0x503)
        {
            std::cout << "Publishing pedestrian zone sign detected." << std::endl;
            pedestrianZone_pub.put("1");
        }
        usleep(10);
    }
    return 0;
}