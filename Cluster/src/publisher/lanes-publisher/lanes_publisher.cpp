#include <zenoh.hxx>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace zenoh;

// Generate a space-separated coefficient string like: "0.02 -12.5 1600.0"
std::string generateLaneCoefficients(double a, double b, double c) {
    std::ostringstream oss;
    oss << a << " " << b << " " << c;
    return oss.str();
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "Starting Lane Publisher..." << std::endl;

    // Create Zenoh session
    auto config = Config::create_default();
    auto session = std::make_shared<zenoh::Session>(
        zenoh::Session::open(std::move(config)));

    // Declare publishers
    auto left_lanes_pub = session->declare_publisher("Vehicle/1/Scene/Lanes/Left");
    auto right_lanes_pub = session->declare_publisher("Vehicle/1/Scene/Lanes/Right");

    while (true) {
        // Simulate lane coefficient values
        double aLeft = 0.02 + ((std::rand() % 100) - 50) / 10000.0;
        double bLeft = -12.0 + ((std::rand() % 200) - 100) / 10.0;
        double cLeft = 1600.0 + (std::rand() % 300);

        double aRight = 0.003 + ((std::rand() % 100) - 50) / 10000.0;
        double bRight = -0.5 + ((std::rand() % 100) - 50) / 100.0;
        double cRight = 350.0 + (std::rand() % 50);

        std::string leftPayload = generateLaneCoefficients(aLeft, bLeft, cLeft);
        std::string rightPayload = generateLaneCoefficients(aRight, bRight, cRight);

        // Publish
        left_lanes_pub.put(leftPayload);
        right_lanes_pub.put(rightPayload);

        std::cout << "[LEFT]  " << leftPayload << std::endl;
        std::cout << "[RIGHT] " << rightPayload << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
