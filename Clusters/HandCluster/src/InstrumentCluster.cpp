#include "../include/InstrumentCluster.hpp"
#include <QPoint>
#include <chrono>
#include <thread>


InstrumentCluster::InstrumentCluster(QObject* parent)
    : QObject(parent), m_speed(0), percentage(0), autonomyLevel(0), gear(0)
{
    std::cout << "Using default configuration." << std::endl;
    auto config = zenoh::Config::create_default();
    session     = std::make_unique<zenoh::Session>(
        zenoh::Session::open(std::move(config)));
    this->setupSubscriptions();
}

InstrumentCluster::InstrumentCluster(const std::string& configFile,
                                     QObject* parent)
    : QObject(parent), m_speed(0), percentage(0), autonomyLevel(0), gear(0)
{
    std::cout << "Using configuration file: " << configFile << std::endl;
    auto config = zenoh::Config::from_file(configFile);
    session = std::make_unique<zenoh::Session>(zenoh::Session::open(std::move(config)));
    this->setupSubscriptions();
}

InstrumentCluster::~InstrumentCluster()
{
    session->close();
}

void InstrumentCluster::setupSubscriptions()
{
    std::cout << "Setting up subscriptions..." << std::endl;
    speed_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Speed",
        [this](const zenoh::Sample& sample)
        {
            int speed = std::stoi(sample.get_payload().as_string());
            setSpeed(speed);
        },
        zenoh::closures::none));

    beamLow_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/Beam/Low",
        [this](const zenoh::Sample& sample)
        {
            bool isOn = std::stoi(sample.get_payload().as_string());
            setLowBeam(isOn);
        },
        zenoh::closures::none));

    beamHigh_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/Beam/High",
        [this](const zenoh::Sample& sample)
        {
            bool isOn = std::stoi(sample.get_payload().as_string());
            setHighBeam(isOn);
        },
        zenoh::closures::none));

    directionIndicatorLeft_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/DirectionIndicator/Left",
        [this](const zenoh::Sample& sample)
        {
            std::cout << "Recebido left blinker: " << sample.get_payload().as_string() << std::endl;
            bool isSignaling = std::stoi(sample.get_payload().as_string());
            setLeftBlinker(isSignaling);
        },
        zenoh::closures::none));

    directionIndicatorRight_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/DirectionIndicator/Right",
        [this](const zenoh::Sample& sample)
        {
            std::cout << "Recebido right blinker: " << sample.get_payload().as_string() << std::endl;
            bool isSignaling = std::stoi(sample.get_payload().as_string());
            setRightBlinker(isSignaling);
        },
        zenoh::closures::none));

    hazard_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/Hazard",
        [this](const zenoh::Sample& sample)
        {
            bool isSignaling = std::stoi(sample.get_payload().as_string());
            setHazardLight(isSignaling);
        },
        zenoh::closures::none));

    fogFront_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/Fog/Front",
        [this](const zenoh::Sample& sample)
        {
            bool isOn = std::stoi(sample.get_payload().as_string());
            setFrontFogLight(isOn);
        },
        zenoh::closures::none));

    fogRear_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/Fog/Rear",
        [this](const zenoh::Sample& sample)
        {
            bool isOn = std::stoi(sample.get_payload().as_string());
            setRearFogLight(isOn);
        },
        zenoh::closures::none));

    parking_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/Parking",
        [this](const zenoh::Sample& sample)
        {
            bool isOn = std::stoi(sample.get_payload().as_string());
            setParkingLight(isOn);
        },
        zenoh::closures::none));

    stateOfCharge_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Powertrain/TractionBattery/StateOfCharge",
        [this](const zenoh::Sample& sample)
        {
            int soc = std::stoi(sample.get_payload().as_string());
            setPercentage(soc);
        },
        zenoh::closures::none));

    currentGear_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Powertrain/Transmission/CurrentGear",
        [this](const zenoh::Sample& sample)
        {
            int currentGear = std::stoi(sample.get_payload().as_string());
            std::cout << "Current Gear: " << currentGear << std::endl;
            setGear(currentGear);
        },
        zenoh::closures::none));
    obstacleWarning_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/ADAS/ObstacleDetection/Warning",
        [this](const zenoh::Sample& sample) {
            std::cout << "Recebido obstacleWarning: " << sample.get_payload().as_string() << std::endl;
            setWarningCode(1);
        },
        zenoh::closures::none));
    laneDeparture_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/ADAS/LaneDeparture/Detected",
        [this](const zenoh::Sample& sample) {
            int isDeparting = std::stoi(sample.get_payload().as_string());
            if (isDeparting == 10) //lane departure to left
            {
                std::cout << "Received lane departure to left" << std::endl;
                setLaneDeparture(10);
                std::cout << "Setting warning code to 2" << std::endl;
                setWarningCode(2);
            } 
            else if (isDeparting == 11) { //lane departure to left off
                std::cout << "Received lane departure to left or right off" << std::endl;
                setLaneDeparture(11);
                std::cout << "Setting warning code to 0" << std::endl;
                setWarningCode(0);
            }
            else if(isDeparting == 20) { //lane departure to right
                std::cout << "Received lane departure to right" << std::endl;
                setLaneDeparture(20);
                std::cout << "Setting warning code to 2" << std::endl;
                setWarningCode(2);
            } 
        },
        zenoh::closures::none));
    sae0_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_0",
        [this](const zenoh::Sample& sample) {
                std::cout << "Recebido SAE 0" << std::endl;
                setAutonomyLevel(0);
        },
        zenoh::closures::none));   
    sae1_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1",
        [this](const zenoh::Sample& sample) {
                std::cout << "Recebido SAE 1" << std::endl;
                setAutonomyLevel(1);
        },
        zenoh::closures::none));
    sae2_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_2",
        [this](const zenoh::Sample& sample) {
                std::cout << "Recebido SAE 2" << std::endl;
                setAutonomyLevel(2);
        },
        zenoh::closures::none));
    sae5_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5",
        [this](const zenoh::Sample& sample) {
                std::cout << "Recebido SAE 5" << std::endl;
                setAutonomyLevel(5);
        },
        zenoh::closures::none));
    cruiseControl_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/ADAS/ActiveAutonomyLevel/CruiseControl",
        [this](const zenoh::Sample& sample) {
            std::string cruiseControlState = sample.get_payload().as_string();
            if (cruiseControlState == "1") {
                std::cout << "Cruise Control Activated" << std::endl;
                setCruiseControl(true);
            } else if (cruiseControlState == "0") {
                std::cout << "Cruise Control Deactivated" << std::endl;
                setCruiseControl(false);
            }
        },
        zenoh::closures::none));
    speedLimit_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Environment/RoadSigns/SpeedLimit",
        [this](const zenoh::Sample& sample) {
            int speedLimit = std::stoi(sample.get_payload().as_string());
            std::cout << "Speed Limit Received: " << speedLimit << " km/h" << std::endl;
            if(speedLimit == 20)
                setSignDetected(0);
            else if(speedLimit == 30)
                setSignDetected(1);
            else if(speedLimit == 40)
                setSignDetected(2);
            if(speedLimit == 50)
                setSignDetected(3);
            else if(speedLimit == 60)
                setSignDetected(4);
            else if(speedLimit == 70)
                setSignDetected(5);
            else if(speedLimit == 80)
                setSignDetected(6);
            else if(speedLimit == 90)
                setSignDetected(7);
            else if(speedLimit == 100)
                setSignDetected(8);
            else if(speedLimit == 120)
                setSignDetected(9);
            else
                setSignDetected(0);
        },
        zenoh::closures::none));
    stopSign_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Environment/RoadSigns/Stop",
        [this](const zenoh::Sample& sample) {
            std::cout << "Recebido Stop Sign" << std::endl;
            setSignDetected(0);
            setSignDetected(11); 
        },
        zenoh::closures::none));
    yieldSign_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Environment/RoadSigns/Yield",
        [this](const zenoh::Sample& sample) {
            std::cout << "Recebido Yield Sign" << std::endl;
            setSignDetected(0);
            setSignDetected(12);
        },
        zenoh::closures::none));
    pedestrianZone_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Environment/RoadSigns/PedestrianZone",
        [this](const zenoh::Sample& sample) {
            std::cout << "Recebido Pedestrian Zone Sign" << std::endl;
            setSignDetected(0);
            setSignDetected(13);
        },
        zenoh::closures::none));
    dangerSign_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Environment/RoadSigns/DangerSign",
        [this](const zenoh::Sample& sample) {
            std::cout << "Recebido Danger Sign" << std::endl;
            setSignDetected(0);
            setSignDetected(17);
        },
        zenoh::closures::none));
    trafficLight_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Environment/RoadSigns/TrafficLight",
        [this](const zenoh::Sample& sample) {
            std::string trafficLight = sample.get_payload().as_string();
            if (trafficLight == "yellow") {
                std::cout << "Recebido Traffic Sign: yellow" << std::endl;
                setSignDetected(0);
                setSignDetected(14);
            } else if (trafficLight == "green") {
                std::cout << "Recebido Traffic Sign: green" << std::endl;
                setSignDetected(0);
                setSignDetected(15);
            } else if (trafficLight == "red") {
                std::cout << "Recebido Traffic Sign: red" << std::endl;
                setSignDetected(0);
                setSignDetected(16);
            }
        },
        zenoh::closures::none));
}

void InstrumentCluster::parseLaneData(const std::string& laneData, const std::string& laneType)
{
    std::istringstream stream(laneData);
    float a, b, c;
    stream >> a >> b >> c;
    
    QVariantMap coefficients;
    coefficients["a"] = a;
    coefficients["b"] = b;
    coefficients["c"] = c;

    if (laneType == "leftLane") {
        setLeftLaneCoefs(coefficients);  
    }
    else if (laneType == "rightLane") {
        setRightLaneCoefs(coefficients); 
    }
}

bool InstrumentCluster::getCruiseControl() const
{
    return cruiseControl;
}

void InstrumentCluster::setCruiseControl(bool state)
{
    if (cruiseControl != state)
    {
        cruiseControl = state;
        emit cruiseControlChanged(state);
    }
}

int InstrumentCluster::getSpeed() const
{
    return m_speed;
}

void InstrumentCluster::setSpeed(int speed)
{
    if (m_speed != speed)
    {
        m_speed = speed;
        emit speedChanged(speed);
    }
}


int InstrumentCluster::getWarningCode() const {
    return this->warningCode;
}

void InstrumentCluster::setWarningCode(int code) {
    if (this->warningCode != code) {
        this->warningCode = code; 
    }
    emit warningCodeChanged(code);
}

int InstrumentCluster::getLaneDeparture() const {
    return this->laneDeparture;
}

void InstrumentCluster::setLaneDeparture(int state) {
    if (this->laneDeparture != state) {
        this->laneDeparture = state;
        emit laneDepartureChanged(state);
    }
}

bool InstrumentCluster::getRightBlinker() const
{
    return rightBlinker;
}
void InstrumentCluster::setRightBlinker(bool state)
{
    if (rightBlinker != state)
    {
        rightBlinker = state;
        emit rightBlinkerChanged(state);
    }
}

bool InstrumentCluster::getLeftBlinker() const
{
    return leftBlinker;
}
void InstrumentCluster::setLeftBlinker(bool state)
{
    if (leftBlinker != state)
    {
        leftBlinker = state;
        emit leftBlinkerChanged(state);
    }
}

bool InstrumentCluster::getLowBeam() const
{
    return lowBeam;
}
void InstrumentCluster::setLowBeam(bool state)
{
    if (lowBeam != state)
    {
        lowBeam = state;
        emit lowBeamChanged(state);
    }
}

bool InstrumentCluster::getHighBeam() const
{
    return highBeam;
}
void InstrumentCluster::setHighBeam(bool state)
{
    if (highBeam != state)
    {
        highBeam = state;
        emit highBeamChanged(state);
    }
}

bool InstrumentCluster::getFrontFogLight() const
{
    return frontFogLight;
}
void InstrumentCluster::setFrontFogLight(bool state)
{
    if (frontFogLight != state)
    {
        frontFogLight = state;
        emit frontFogLightChanged(state);
    }
}

bool InstrumentCluster::getRearFogLight() const
{
    return rearFogLight;
}
void InstrumentCluster::setRearFogLight(bool state)
{
    if (rearFogLight != state)
    {
        rearFogLight = state;
        emit rearFogLightChanged(state);
    }
}

bool InstrumentCluster::getHazardLight() const
{
    return hazardLight;
}
void InstrumentCluster::setHazardLight(bool state)
{
    if (hazardLight != state)
    {
        hazardLight = state;
        emit hazardLightChanged(state);
    }
}

bool InstrumentCluster::getParkingLight() const
{
    return parkingLight;
}
void InstrumentCluster::setParkingLight(bool state)
{
    if (parkingLight != state)
    {
        parkingLight = state;
        emit parkingLightChanged(state);
    }
}

int InstrumentCluster::getPercentage() const
{
    return percentage;
}
void InstrumentCluster::setPercentage(int value)
{
    if (percentage != value)
    {
        percentage = value;
        emit percentageChanged(value);
    }
}


int InstrumentCluster::getSignDetected() const
{
    return signDetected;
}

void InstrumentCluster::setSignDetected(int value)
{
    if (signDetected != value)
    {
        signDetected = value;
        std::cout << "Sign detected updated: " << signDetected << std::endl;
        emit signDetectedChanged(value);
    }
}

int InstrumentCluster::getGear() const
{
    return gear;
}
void InstrumentCluster::setGear(int value)
{
    if (gear != value)
    {
        gear = value;
        emit gearChanged(value);
    }
}

QVariantMap InstrumentCluster::getLeftLaneCoefs() const {
    return m_leftLaneCoefs;
}

QVariantMap InstrumentCluster::getRightLaneCoefs() const {
    return m_rightLaneCoefs;
}

int InstrumentCluster::getAutonomyLevel() const {
    return autonomyLevel;
}

void InstrumentCluster::setAutonomyLevel(int level) {
    // if (autonomyLevel != level) {
        autonomyLevel = level;
        std::cout << "Autonomy level updated: " << autonomyLevel << std::endl;
        emit autonomyLevelChanged(level);
        std::cout << "Autonomy level changed signal emitted to: " << getAutonomyLevel() << std::endl;
    // }
}

void InstrumentCluster::setLeftLaneCoefs(const QVariantMap& coefs) {
    std::cout << "Coefficients updated: " << std::endl;
    if (m_leftLaneCoefs != coefs) { 
        std::cout << "Left lane coefficients updated: " 
                  << coefs["a"].toFloat() << ", " 
                  << coefs["b"].toFloat() << ", " 
                  << coefs["c"].toFloat() << std::endl;
        m_leftLaneCoefs = coefs;
        emit leftLaneChanged(coefs);
    }
}

void InstrumentCluster::setRightLaneCoefs(const QVariantMap& coefs) {
    std::cout << "Coefficients updated: " << std::endl;
    if (m_rightLaneCoefs != coefs) {  
        std::cout << "Right lane coefficients updated: " 
                  << coefs["a"].toFloat() << ", " 
                  << coefs["b"].toFloat() << ", " 
                  << coefs["c"].toFloat() << std::endl;
        m_rightLaneCoefs = coefs;
        emit rightLaneChanged(coefs);
    }
}

InstrumentCluster::InstrumentCluster(std::shared_ptr<zenoh::Session> session, QObject* parent)
    : QObject(parent), session(std::move(session)), m_speed(0), percentage(0), autonomyLevel(0), gear(0) {
    this->setupSubscriptions();
}

