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

using namespace zenoh;

int main(int argc, char** argv)
{
    std::vector<uint8_t> laneDataBuffer; 
    struct ifreq ifr;
    struct sockaddr_can addr;
    std::vector<uint8_t> rightLaneBuffer;
    std::vector<uint8_t> leftLaneBuffer;

    std::vector<std::string> objectTypes = { "car", "pedestrian", "cyclist" };
    std::vector<QJsonObject> objectList;

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

    std::cout << "CAN socket bound to can0 interface successfully."
              << std::endl;

    std::unique_ptr<zenoh::Session> session;
    if (argc == 2)
    {
        auto config = Config::from_file(argv[1]);
        session     = std::make_unique<zenoh::Session>(
            zenoh::Session::open(std::move(config)));
    }
    else
    {
        auto config = Config::create_default();
        session     = std::make_unique<zenoh::Session>(
            zenoh::Session::open(std::move(config)));
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
    auto objects_pub = session->declare_publisher("Vehicle/1/Scene/Objects");

    while (1)
    {
        struct can_frame frame;

        int nbytes = read(canSocket, &frame, sizeof(struct can_frame));
        if (nbytes < 0)
        {
            std::cerr << "Error reading CAN frame!" << std::endl;
            continue;
        }
        if (frame.can_id == 0x01)
        {
            int speed;
            double wheelDiame = 0.067;

            memcpy(&speed, frame.data, sizeof(int));
            speed                 = ntohl(speed);
            speed                 = wheelDiame * 3.14 * speed * 10 / 60;
            std::string speed_str = std::to_string(speed);

            // printf("Publishing speed: '%d'\n", speed);
            speed_pub.put(speed_str.c_str());
        }
        else if (frame.can_id == 0x02)
        {
            double battery;

            memcpy(&battery, frame.data, sizeof(double));

            float percentage = ((battery - 9.5f) / (12.6f - 9.5f)) * 100.0f;
            battery          = std::min(100.0f, std::max(0.0f, percentage));
            std::string battery_str = std::to_string(battery);

            // printf("Publishing battery: '%lf\n", battery);
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
        if(frame.can_id == 0x200){ // estou publicando por tempo e nao a cada objeto que chega 
            float x, y;
            uint16_t width, height;
            uint8_t type;

            memcpy(&x, &frame.data[0], sizeof(float));
            memcpy(&y, &frame.data[4], sizeof(float));
            memcpy(&width, &frame.data[8], sizeof(uint16_t));
            memcpy(&height, &frame.data[10], sizeof(uint16_t));
            memcpy(&type, &frame.data[12], sizeof(uint8_t));

             std::cout << "[CAN] Object received - x: " << x
              << ", y: " << y
              << ", w: " << width
              << ", h: " << height
              << ", type: " << (int)type << std::endl;

            QJsonObject obj; 
            obj["x"] = x;
            obj["y"] = y;
            obj["width"] = width;
            obj["height"] = height;
            obj["type"] = QString::fromStdString(objectTypes[type]);
            objectList.push_back(obj);

            auto now = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPublishTime);

            if (duration.count() >= 100) {
                QJsonArray arr;
                for (const auto& o : objectBuffer)
                    arr.append(o);

                QJsonDocument doc(arr);
                std::string jsonString = doc.toJson(QJsonDocument::Compact).toStdString();
                objects_pub.put(jsonString);
                
                objectBuffer.clear();
                lastPublishTime = now;
            }

        usleep(10);
    }
    return 0;
}
