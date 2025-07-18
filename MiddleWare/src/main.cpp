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

class SHMPublishers {
private:
    std::shared_ptr<zenoh::Session> session_;
    std::optional<zenoh::PosixShmProvider> provider_;
    std::optional<zenoh::Publisher> speed_publisher_;
    std::optional<zenoh::Publisher> beamLow_publisher_;
    std::optional<zenoh::Publisher> beamHigh_publisher_;
    std::optional<zenoh::Publisher> running_publisher_;
    std::optional<zenoh::Publisher> parking_publisher_;
    std::optional<zenoh::Publisher> fogRear_publisher_;
    std::optional<zenoh::Publisher> fogFront_publisher_;
    std::optional<zenoh::Publisher> brake_publisher_;
    std::optional<zenoh::Publisher> hazard_publisher_;
    std::optional<zenoh::Publisher> directionIndicatorLeft_publisher_;
    std::optional<zenoh::Publisher> directionIndicatorRight_publisher_;
    std::optional<zenoh::Publisher> laneDeparture_publisher_;
    std::optional<zenoh::Publisher> currentGear_publisher_;
    std::optional<zenoh::Publisher> current_voltage_publisher_;
    std::optional<zenoh::Publisher> current_current_publisher_;
    std::optional<zenoh::Publisher> current_power_publisher_;
    std::optional<zenoh::Publisher> state_of_charge_publisher_;
    std::optional<zenoh::Publisher> right_lanes_publisher_;
    std::optional<zenoh::Publisher> left_lanes_publisher_;
    std::optional<zenoh::Publisher> obstacleWarning_publisher_;
    std::optional<zenoh::Publisher> sae0_publisher_;
    std::optional<zenoh::Publisher> sae1_publisher_;
    std::optional<zenoh::Publisher> sae2_publisher_;
    std::optional<zenoh::Publisher> sae5_publisher_;
    std::optional<zenoh::Publisher> cruise_control_publisher_;
    std::optional<zenoh::Publisher> speedLimit_publisher_;
    std::optional<zenoh::Publisher> stopSign_publisher_;
    std::optional<zenoh::Publisher> yieldSign_publisher_;
    std::optional<zenoh::Publisher> pedestrianZone_publisher_;
    std::optional<zenoh::Publisher> trafficLight_publisher_;
    std::optional<zenoh::Publisher> dangerSign_publisher_;

public:
    SHMPublishers(std::shared_ptr<zenoh::Session> session) {
        session_ = session;
        provider_.emplace(zenoh::MemoryLayout(65536, zenoh::AllocAlignment({2})));

        speed_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Speed")));
        beamLow_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Beam/Low")));
        beamHigh_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Beam/High")));
        running_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Running")));
        parking_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Parking")));
        fogRear_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Fog/Rear")));
        fogFront_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Fog/Front")));
        brake_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Brake")));
        hazard_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/Hazard")));
        directionIndicatorLeft_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/DirectionIndicator/Left")));
        directionIndicatorRight_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Body/Lights/DirectionIndicator/Right")));
        laneDeparture_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/ADAS/LaneDeparture/Detected")));
        currentGear_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Powertrain/Transmission/CurrentGear")));
        current_voltage_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurentVoltage")));
        current_current_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurrentCurrent")));
        current_power_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurrentPower")));
        state_of_charge_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/StateOfCharge")));
        right_lanes_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Scene/Lanes/Right")));
        left_lanes_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Scene/Lanes/Left")));
        obstacleWarning_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/ADAS/ObstacleDetection/Warning")));
        sae0_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_0")));
        sae1_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1")));
        sae2_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_2")));
        sae5_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5")));
        cruise_control_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/ADAS/ActiveAutonomyLevel/CruiseControl")));
        speedLimit_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/SpeedLimit")));
        stopSign_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/Stop")));
        yieldSign_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/Yield")));
        pedestrianZone_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/PedestrianZone")));
        trafficLight_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/TrafficLight")));
        dangerSign_publisher_.emplace(session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Environment/RoadSigns/DangerSign")));
    }

    void speed_publisher(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result =
            provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        speed_publisher_->put(std::move(buf));
    }
    void beamLow_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        beamLow_publisher_->put(std::move(buf));
    }
    void beamHigh_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        beamHigh_publisher_->put(std::move(buf));
    }
    void running_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        running_publisher_->put(std::move(buf));
    }
    void parking_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        parking_publisher_->put(std::move(buf));
    }
    void fogRear_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        fogRear_publisher_->put(std::move(buf));
    }
    void fogFront_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        fogFront_publisher_->put(std::move(buf));
    }
    void brake_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        brake_publisher_->put(std::move(buf));
    }
    void hazard_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        hazard_publisher_->put(std::move(buf));
    }
    void directionIndicatorLeft_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        directionIndicatorLeft_publisher_->put(std::move(buf));
    }
    void directionIndicatorRight_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        directionIndicatorRight_publisher_->put(std::move(buf));
    }
    void laneDeparture_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        laneDeparture_publisher_->put(std::move(buf));
    }
    void currentGear_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        currentGear_publisher_->put(std::move(buf));
    }
    void current_voltage_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        current_voltage_publisher_->put(std::move(buf));
    }
    void current_current_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        current_current_publisher_->put(std::move(buf));
    }
    void current_power_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        current_power_publisher_->put(std::move(buf));
    }
    void state_of_charge_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result =
            provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        state_of_charge_publisher_->put(std::move(buf));
    }
    void right_lanes_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        right_lanes_publisher_->put(std::move(buf));
    }
    void left_lanes_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        left_lanes_publisher_->put(std::move(buf));
    }
    void obstacleWarning_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        obstacleWarning_publisher_->put(std::move(buf));
    }
    void sae0_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        sae0_publisher_->put(std::move(buf));
    }
    void sae1_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        sae1_publisher_->put(std::move(buf));
    }
    void sae2_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        sae2_publisher_->put(std::move(buf));
    }
    void sae5_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        sae5_publisher_->put(std::move(buf));
    }
    void cruise_control_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        cruise_control_publisher_->put(std::move(buf));
    }
    void speedLimit_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        speedLimit_publisher_->put(std::move(buf));
    }
    void stopSign_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        stopSign_publisher_->put(std::move(buf));
    }
    void yieldSign_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        yieldSign_publisher_->put(std::move(buf));
    }
    void pedestrianZone_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        pedestrianZone_publisher_->put(std::move(buf));
    }
    void trafficLight_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        trafficLight_publisher_->put(std::move(buf));
    }
    void dangerSign_publish(const std::string& value_str) {
        const auto len = value_str.size() + 1;
        auto alloc_result = provider_->alloc_gc_defrag_blocking(len, zenoh::AllocAlignment({0}));
        zenoh::ZShmMut&& buf = std::get<zenoh::ZShmMut>(std::move(alloc_result));
        memcpy(buf.data(), value_str.c_str(), len);
        dangerSign_publisher_->put(std::move(buf));
    }
};

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

    std::shared_ptr<zenoh::Session> session;

    try
    {
        if (argc == 2)
        {
            std::cout << "Using configuration file: " << argv[1] << std::endl;
            auto config = Config::from_file(argv[1]);
            session     = std::make_shared<zenoh::Session>(
                zenoh::Session::open(std::move(config)));
            }
            else
        {
            std::cout << "Using default configuration." << std::endl;
            auto config = Config::create_default();
            session     = std::make_shared<zenoh::Session>(
                zenoh::Session::open(std::move(config)));
        }
    }
    catch (const zenoh::ZException& e)
    {
        std::cerr << "Failed to open Zenoh session: " << e.what() << std::endl;
        close(canSocket);
        exit(1);
    }
    
    SHMPublishers publishers(session);

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
                publishers.speed_publisher(speed_str);
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
            publishers.state_of_charge_publish(battery_str);
        }
        else if (frame.can_id >= 0x700 && frame.can_id <= 0x707)
        {
            bool lightState = frame.data[0] != 0; // first byte indicates ON/OFF state
            switch (frame.can_id)
            {
            case 0x700:
                publishers.directionIndicatorLeft_publish(std::to_string(lightState));
                std::cout << "Publishing Direction Indicator Left: " << lightState << std::endl;
                break;
            case 0x701:
                publishers.directionIndicatorRight_publish(std::to_string(lightState));
                std::cout << "Publishing Direction Indicator Right: " << lightState << std::endl;
                break;
            case 0x702:
                publishers.beamLow_publish(std::to_string(lightState));
                std::cout << "Publishing Beam Low: " << lightState << std::endl;
                break;
            case 0x703:
                publishers.beamHigh_publish(std::to_string(lightState));
                std::cout << "Publishing Beam High: " << lightState << std::endl;
                break;
            case 0x704:
                publishers.fogFront_publish(std::to_string(lightState));
                std::cout << "Publishing Fog Front: " << lightState << std::endl;
                break;
            case 0x705:
                publishers.fogRear_publish(std::to_string(lightState));
                std::cout << "Publishing Fog Rear: " << lightState << std::endl;
                break;
            case 0x706:
                publishers.hazard_publish(std::to_string(lightState));
                std::cout << "Publishing Hazard: " << lightState << std::endl;
                break;
            case 0x707:
                publishers.parking_publish(std::to_string(lightState));
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
            publishers.currentGear_publish(std::to_string(gear));
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
                    publishers.left_lanes_publish(stream.str());
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
                    publishers.right_lanes_publish(stream.str());
                    std::fill(std::begin(rightReceived), std::end(rightReceived), false);
                }
            }
        }
        else if (frame.can_id == 0x200)
            publishers.obstacleWarning_publish("1");
        else if (frame.can_id == 0x301) //left lane departure
        {
            std::cout << "Publishing lane departure to left." << std::endl;
            publishers.laneDeparture_publish("10");
        }
        else if (frame.can_id == 0x302) //left lane departure off
        {
            std::cout << "Publishing lane departure to left or right off." << std::endl;
            publishers.laneDeparture_publish("11");
        }
        else if(frame.can_id == 0x303) //right lane departure
        {
            std::cout << "Publishing lane departure to right." << std::endl;
            publishers.laneDeparture_publish("20");
        }
        else if (frame.can_id == 0x400)
            publishers.sae0_publish("0");
        else if (frame.can_id == 0x401)
            publishers.sae1_publish("1");
        else if (frame.can_id == 0x402)
            publishers.sae2_publish("2");
        else if (frame.can_id == 0x405)
            publishers.sae5_publish("5");
        else if (frame.can_id == 0x406)
        {
            std::cout << "Publishing cruise control activated." << std::endl;
            publishers.cruise_control_publish("1");
        }
        else if (frame.can_id == 0x407)
        {
            std::cout << "Publishing cruise control deactivated." << std::endl;
            publishers.cruise_control_publish("0");
        }
        else if (frame.can_id == 0x500)
        {
            std::cout << "Publishing speed limit: 50km/h" << std::endl;
            publishers.speedLimit_publish("50");
        }
        else if (frame.can_id == 0x505)
        {
            std::cout << "Publishing speed limit: 80km/h" << std::endl;
            publishers.speedLimit_publish("80");
        }
        else if (frame.can_id == 0x501)
        {
            std::cout << "Publishing stop sign detected. (11)" << std::endl;
            publishers.stopSign_publish("1");
        }
        else if (frame.can_id == 0x502)
        {
            std::cout << "Publishing yield sign detected (12)." << std::endl;
            publishers.yieldSign_publish("1");
        }
        else if (frame.can_id == 0x503)
        {
            std::cout << "Publishing pedestrian zone sign detected. (13)" << std::endl;
            publishers.pedestrianZone_publish("1");
        }
        else if (frame.can_id == 0x504)
        {
            std::cout << "Publishing danger sign detected. (17)" << std::endl;
            publishers.dangerSign_publish("1");
        }
        else if (frame.can_id == 0x600)
        {
            std::cout << "Publishing traffic sign detected: yellow (14)" << std::endl;
            publishers.trafficLight_publish("yellow");
        }
        else if (frame.can_id == 0x601)
        {
            std::cout << "Publishing traffic sign detected: green (15)" << std::endl;
            publishers.trafficLight_publish("green");
        }
        else if (frame.can_id == 0x602)
        {
            std::cout << "Publishing traffic sign detected: red (16)" << std::endl;
            publishers.trafficLight_publish("red");
        }
        
        usleep(10);
    }
    return 0;
}