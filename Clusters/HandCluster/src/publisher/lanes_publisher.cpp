#include <string>
#include <zenoh.hxx>
#include <iostream>
#include <sstream>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>

using namespace zenoh;

int main(int argc, char** argv)
{
    std::string laneData = "leftLane: 300,500 320,400 360,300\nrightLane: 600,500 580,400 600,300";
    std::vector<std::string> laneDataSamples = {
        "leftLane: 300,500 320,400 360,300\nrightLane: 600,500 580,400 600,300",
        "leftLane: 310,510 330,410 370,310\nrightLane: 610,510 590,410 610,310",
        "leftLane: 320,520 340,420 380,320\nrightLane: 620,520 600,420 620,320",
        "leftLane: 330,530 350,430 390,330\nrightLane: 630,530 610,430 630,330",
        "leftLane: 340,540 360,440 400,340\nrightLane: 640,540 620,440 640,340"
    };

    int sampleIndex = 0;
    std::cout << "Starting Lane Publisher" << std::endl;
    std::shared_ptr<zenoh::Session> session;
    auto config = Config::create_default();
    session = std::make_unique<zenoh::Session>(
    zenoh::Session::open(std::move(config)));
    auto publisher = session->declare_publisher("Vehicle/1/LaneData");
    
    // while (1)
    // {
    //     std::cout << "Publishing Lane Data" << std::endl;
    //     std::cout << "Published Lane Data: " << laneData << std::endl;
    //     publisher.put(laneData);    
    //     std::this_thread::sleep_for(std::chrono::seconds(5)); // Add delay of 10 seconds
    // }

    while (1)
    {
        std::cout << "Publishing Lane Data" << std::endl;
        std::cout << "Published Lane Data: " << laneDataSamples[sampleIndex] << std::endl;
        publisher.put(laneDataSamples[sampleIndex]);
        sampleIndex = (sampleIndex + 1) % laneDataSamples.size();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Add delay of 5 seconds
    }

}


