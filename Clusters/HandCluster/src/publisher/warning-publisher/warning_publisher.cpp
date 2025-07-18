// #include <zenoh.hxx>
// #include <thread>
// #include <chrono>
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <memory>
// #include <cstdlib>
// #include <ctime>

// using namespace zenoh;

// // Generate a space-separated coefficient string like: "0.02 -12.5 1600.0"
// std::string generateLaneCoefficients(double a, double b, double c) {
//     std::ostringstream oss;
//     oss << a << " " << b << " " << c;
//     return oss.str();
// }

// int main() {
//     std::srand(static_cast<unsigned>(std::time(nullptr)));

//     std::cout << "Starting Warning Publisher..." << std::endl;

//     // Create Zenoh session
//     auto config = Config::create_default();
//     auto session = std::make_shared<zenoh::Session>(
//         zenoh::Session::open(std::move(config)));

//     auto warning_pub = session->declare_publisher("Vehicle/1/ADAS/ObstacleDetection/Warning");
//     auto sae1_pub = session->declare_publisher("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1");
//     auto sae5_pub = session->declare_publisher("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5");
//     auto laneDeparture_pub = session->declare_publisher("Vehicle/1/ADAS/LaneDeparture/Detected");



//     // while (true) {

//         std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        
//         auto start_time = std::chrono::steady_clock::now();
//         auto end_time = start_time + std::chrono::seconds(10);

//         while (std::chrono::steady_clock::now() < end_time) {
//             std::cout << "Publishing warning code... EMERGENCY BRAKE" << std::endl;
//             int warningCode = 1; // Example warning code
//             warning_pub.put(std::to_string(warningCode));
//             std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Publish every 500ms
//         }
//         // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//         // std::cout << "Publishing warning code... LANE DEPARTURE" << std::endl;
//         // int warningCode2 = 10; // Example warning code
//         // laneDeparture_pub.put(std::to_string(warningCode2));
//         // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//         // std::cout << "Publishing warning code... LANE DEPARTURE OFF" << std::endl;
//         // int warningCode3 = 11; // Example warning code
//         // laneDeparture_pub.put(std::to_string(warningCode3));
        
//         // Publish
//         // std::cout << "Publishing warning code..." << std::endl;
//         // int warningCode = 1;
//         // std::cout << "Warning code: " << warningCode << std::endl;

//         // // Convert the warning code to a string and publish it
//         // std::string warningCodeStr = std::to_string(warningCode);
//         // warning_pub.put(warningCodeStr);

//         // // std::cout << "Publishing SAE Level 1..." << std::endl;
//         // // sae1_pub.put("1");

//         // std::cout << "Lane Departure to right" << std::endl;
//         // laneDeparture_pub.put("20");

//         // // std::cout << "Lane Departure to left" << std::endl;
//         // // laneDeparture_pub.put("10");

//         // // Simulate a delay before the next publication
//         // std::this_thread::sleep_for(std::chrono::milliseconds(3000));

//         // // std::cout << "Lane Departure left off" << std::endl;
//         // // laneDeparture_pub.put("11");


//         // std::cout << "Lane Departure right off" << std::endl;
//         // laneDeparture_pub.put("21");

//     // }

//     return 0;
// }

#include <zenoh.hxx>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

using namespace zenoh;

void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {
    std::cout << "Starting Instrument Cluster Demo Publisher..." << std::endl;

    auto config = Config::create_default();
    auto session = std::make_shared<zenoh::Session>(Session::open(std::move(config)));

    auto warning_pub         = session->declare_publisher("Vehicle/1/ADAS/ObstacleDetection/Warning");
    auto laneDeparture_pub   = session->declare_publisher("Vehicle/1/ADAS/LaneDeparture/Detected");
    auto sae1_pub            = session->declare_publisher("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1");
    auto sae2_pub            = session->declare_publisher("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_2");
    auto sae5_pub            = session->declare_publisher("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5");
    auto speed_pub           = session->declare_publisher("Vehicle/1/Speed");
    auto gear_pub            = session->declare_publisher("Vehicle/1/Powertrain/Transmission/CurrentGear");
    auto battery_pub         = session->declare_publisher("Vehicle/1/Powertrain/TractionBattery/StateOfCharge");
    auto sign_pub            = session->declare_publisher("Vehicle/1/Environment/RoadSigns/SpeedLimit");
    auto stopSign_pub        = session->declare_publisher("Vehicle/1/Environment/RoadSigns/Stop");
    auto yieldSign_pub       = session->declare_publisher("Vehicle/1/Environment/RoadSigns/Yield");
    auto pedestrianSign_pub  = session->declare_publisher("Vehicle/1/Environment/RoadSigns/PedestrianZone");
    auto dangerSign_pub      = session->declare_publisher("Vehicle/1/Environment/RoadSigns/DangerSign");
    auto trafficLight_pub    = session->declare_publisher("Vehicle/1/Environment/RoadSigns/TrafficLight");
    auto leftBlinker_pub     = session->declare_publisher("Vehicle/1/Body/Lights/DirectionIndicator/Left");
    auto rightBlinker_pub    = session->declare_publisher("Vehicle/1/Body/Lights/DirectionIndicator/Right");

    std::thread background([&]() {
        while (true) {
            speed_pub.put("2");         // Constant 2 km/h
            gear_pub.put("1");          // Gear D
            battery_pub.put("88");      // Fake battery level
            sleepMs(1000);
        }
    });

    sae1_pub.put("1"); sleepMs(1500);
    sae5_pub.put("1"); sleepMs(1500);
    sae2_pub.put("1"); sleepMs(1500);

    warning_pub.put("1"); sleepMs(2000);
    sleepMs(2000);
    laneDeparture_pub.put("20"); sleepMs(2500);
    laneDeparture_pub.put("11");
    sleepMs(2000);
    laneDeparture_pub.put("10"); sleepMs(2500);
    laneDeparture_pub.put("11"); 

    leftBlinker_pub.put("1"); sleepMs(2500);
    leftBlinker_pub.put("0"); sleepMs(1000);
    rightBlinker_pub.put("1"); sleepMs(2500);
    rightBlinker_pub.put("0"); sleepMs(1000);

    // Traffic signs
    sign_pub.put("80"); sleepMs(1500);
    stopSign_pub.put("1"); sleepMs(1000);
    yieldSign_pub.put("1"); sleepMs(1000);
    pedestrianSign_pub.put("1"); sleepMs(1000);
    dangerSign_pub.put("1"); sleepMs(1000);
    sign_pub.put("50"); sleepMs(1500);

    // Traffic lights
    trafficLight_pub.put("green"); sleepMs(2000);
    trafficLight_pub.put("yellow"); sleepMs(2000);
    trafficLight_pub.put("red"); sleepMs(2000);

    std::cout << "Demo sequence completed." << std::endl;
    background.detach();
    return 0;
}
