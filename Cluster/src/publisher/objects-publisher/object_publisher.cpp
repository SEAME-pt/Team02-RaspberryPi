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

// Function to generate random object data
std::string generateRandomObjectData() {
    std::vector<std::string> types = {"car", "pedestrian", "traffic_light"};
    std::ostringstream oss;

    oss << "[";
    for (int i = 0; i < 3; ++i) {
        if (i > 0) oss << ",";
        oss << "{"
            << "\"x\":" << (rand() % 500) << ","
            << "\"y\":" << (rand() % 500) << ","
            << "\"width\":" << (rand() % 100 + 20) << ","
            << "\"height\":" << (rand() % 100 + 20) << ","
            << "\"type\":\"" << types[rand() % types.size()] << "\""
            << "}";
    }
    oss << "]";
    return oss.str();
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random

    std::cout << "Starting Object Publisher..." << std::endl;

    // Create Zenoh session
    auto config = Config::create_default();
    auto session = std::make_shared<zenoh::Session>(
        zenoh::Session::open(std::move(config)));

    // Declare publisher
    auto publisher = session->declare_publisher("Vehicle/1/Scene/Objects");

    // Publish dynamic object data in a loop
    while (true) {
        std::string dynamicPayload = generateRandomObjectData();
        publisher.put(dynamicPayload);
        std::cout << "Published: " << dynamicPayload << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
