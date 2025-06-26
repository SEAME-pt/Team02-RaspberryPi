#include <zenoh.hxx>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <cstdlib>  // for rand
#include <ctime>    // for time

using namespace zenoh;

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "Starting Sign Publisher..." << std::endl;

    // Create Zenoh session
    auto config = Config::create_default();
    auto session = std::make_shared<zenoh::Session>(
        zenoh::Session::open(std::move(config)));

    // Declare publishers
    auto speedLimit_pub = session->declare_publisher("Vehicle/1/Environment/RoadSigns/SpeedLimit");
    auto stopSign_pub = session->declare_publisher("Vehicle/1/Environment/RoadSigns/Stop");
    auto yieldSign_pub = session->declare_publisher("Vehicle/1/Environment/RoadSigns/Yield");
    auto pedestrianZone_pub = session->declare_publisher("Vehicle/1/Environment/RoadSigns/PedestrianZone");
    auto trafficLight_pub = session->declare_publisher("Vehicle/1/Environment/RoadSigns/TrafficLight");

    auto left_blinker = session->declare_publisher("Vehicle/1/Body/Lights/DirectionIndicator/Left");
    auto right_blinker = session->declare_publisher("Vehicle/1/Body/Lights/DirectionIndicator/Right");
    // Speed limit options
    std::vector<int> speedLimits = {50, 80};

    // Traffic light state and timer
    std::string currentTrafficLight = "red";
    int trafficLightTimer = 0;

    // Loop publishing signs
    while (true) {
        int choice = std::rand() % 10;
        
        if (choice == 0) {
            std::cout << "Publishing Left Blinker ON" << std::endl;
            left_blinker.put("1");
        } else if (choice == 1) {
            std::cout << "Publishing Right Blinker ON" << std::endl;
            right_blinker.put("1");
        } else if (choice == 2) {
            std::cout << "Publishing Left Blinker OFF" << std::endl;
            left_blinker.put("0");
        } else if (choice == 3) {
            std::cout << "Publishing Right Blinker OFF" << std::endl;
            right_blinker.put("0");
        } 

        if (choice == 6) {
            int speed = speedLimits[std::rand() % speedLimits.size()];
            std::cout << "Publishing Speed Limit: " << speed << " km/h" << std::endl;
            speedLimit_pub.put(std::to_string(speed));
        } else if (choice == 7) {
            std::cout << "Publishing Stop Sign" << std::endl;
            stopSign_pub.put("true");
        } else if (choice == 8) {
            std::cout << "Publishing Yield Sign" << std::endl;
            yieldSign_pub.put("true");
        } else if (choice == 9) {
            std::cout << "Publishing Pedestrian Zone" << std::endl;
            pedestrianZone_pub.put("true");
        } else {
            // Traffic light logic
            trafficLightTimer++;
            if (trafficLightTimer >= 5) { // Change traffic light every 5 iterations
                if (currentTrafficLight == "red") {
                    currentTrafficLight = "green";
                } else if (currentTrafficLight == "green") {
                    currentTrafficLight = "yellow";
                } else {
                    currentTrafficLight = "red";
                }
                std::cout << "Publishing Traffic Light: " << currentTrafficLight << std::endl;
                trafficLight_pub.put(currentTrafficLight);
                trafficLightTimer = 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

