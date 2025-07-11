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

    std::cout << "Starting Warning Publisher..." << std::endl;

    // Create Zenoh session
    auto config = Config::create_default();
    auto session = std::make_shared<zenoh::Session>(
        zenoh::Session::open(std::move(config)));

    auto warning_pub = session->declare_publisher("Vehicle/1/ADAS/ObstacleDetection/Warning");
    auto sae1_pub = session->declare_publisher("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1");
    auto sae5_pub = session->declare_publisher("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5");
    auto laneDeparture_pub = session->declare_publisher("Vehicle/1/ADAS/LaneDeparture/Detected");



    // while (true) {

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        // Publish
        std::cout << "Publishing warning code..." << std::endl;
        int warningCode = 1;
        std::cout << "Warning code: " << warningCode << std::endl;

        // Convert the warning code to a string and publish it
        std::string warningCodeStr = std::to_string(warningCode);
        warning_pub.put(warningCodeStr);
        
        // // std::cout << "Publishing SAE Level 1..." << std::endl;
        // // sae1_pub.put("1");

        // std::cout << "Lane Departure to right" << std::endl;
        // laneDeparture_pub.put("20");

        // // std::cout << "Lane Departure to left" << std::endl;
        // // laneDeparture_pub.put("10");

        // // Simulate a delay before the next publication
        // std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        // // std::cout << "Lane Departure left off" << std::endl;
        // // laneDeparture_pub.put("11");


        // std::cout << "Lane Departure right off" << std::endl;
        // laneDeparture_pub.put("21");

    // }

    return 0;
}
