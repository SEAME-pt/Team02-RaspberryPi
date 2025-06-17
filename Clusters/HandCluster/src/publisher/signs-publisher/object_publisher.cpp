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

    #include <zenoh.hxx>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>

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

    // Speed limit options
    std::vector<int> speedLimits = {50, 80};

    // Loop publishing signs
    while (true) {
        int choice = std::rand() % 10;

        if (choice < 7) {
            int speed = speedLimits[std::rand() % speedLimits.size()];
            std::cout << "Publishing Speed Limit: " << speed << " km/h" << std::endl;
            speedLimit_pub.put(std::to_string(speed));
        } else if (choice == 7) {
            std::cout << "Publishing Stop Sign" << std::endl;
            stopSign_pub.put("true");
        } else if (choice == 8) {
            std::cout << "Publishing Yield Sign" << std::endl;
            yieldSign_pub.put("true");
        } else {
            std::cout << "Publishing Pedestrian Zone" << std::endl;
            pedestrianZone_pub.put("true");
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
