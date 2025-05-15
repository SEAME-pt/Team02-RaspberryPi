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

    auto warning_pub = session->declare_publisher("Vehicle/1/Scene/Warning");

    while (true) {

        // Publish
        std::cout << "Publishing warning code..." << std::endl;
        // Generate a random warning code between 1 and 5 (never 0)
        int warningCode = (std::rand() % 4) + 1; // Random number between 1 and 5
        std::cout << "Warning code: " << warningCode << std::endl;

        // Convert the warning code to a string and publish it
        std::string warningCodeStr = std::to_string(warningCode);
        warning_pub.put(warningCodeStr);
        std::this_thread::sleep_for(std::chrono::milliseconds(4500));
    }

    return 0;
}
