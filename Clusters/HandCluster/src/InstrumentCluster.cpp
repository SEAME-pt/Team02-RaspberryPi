#include "../include/InstrumentCluster.hpp"
#include <QPoint>
#include <chrono>
#include <thread>


InstrumentCluster::InstrumentCluster(QObject* parent)
    : QObject(parent), m_speed(0), percentage(0), autonomy(0), gear(0)
{
    auto config = zenoh::Config::create_default();
    session     = std::make_unique<zenoh::Session>(
        zenoh::Session::open(std::move(config)));
    this->setupSubscriptions();
}

InstrumentCluster::InstrumentCluster(const std::string& configFile,
                                     QObject* parent)
    : QObject(parent), m_speed(0), percentage(0), autonomy(0), gear(0)
{
    auto config = zenoh::Config::from_file(configFile);
    session     = std::make_unique<zenoh::Session>(
        zenoh::Session::open(std::move(config)));
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
            bool isSignaling = std::stoi(sample.get_payload().as_string());
            setLeftBlinker(isSignaling);
        },
        zenoh::closures::none));

    directionIndicatorRight_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Body/Lights/DirectionIndicator/Right",
        [this](const zenoh::Sample& sample)
        {
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
            setGear(currentGear);
        },
        zenoh::closures::none));
        
    leftLane_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Scene/Lanes/Left",
        [this](const zenoh::Sample& sample) {

            std::string laneData = sample.get_payload().as_string();
            std::cout << "Recebido leftLaneData: " << laneData << std::endl;
            // std::cout << "Recebido leftLaneData: " << laneData << std::endl;
            parseLaneData(laneData, "rightLane"); //deixei trocado porque no middleware esta trocado e nao consigo alterar pela net 
        },
        zenoh::closures::none));

    rightLane_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/Scene/Lanes/Right",
        [this](const zenoh::Sample& sample) {

            std::string laneData = sample.get_payload().as_string();
            std::cout << "Recebido rightLaneData: " << laneData << std::endl;
            // std::cout << "Recebido rightLaneData: " << laneData << std::endl;
            parseLaneData(laneData, "leftLane"); //deixei trocado porque no middleware esta trocado e nao consigo alterar pela net 
        },
        zenoh::closures::none));
}

// QVariantList InstrumentCluster::generateLaneFromCoefficients(float a, float b, float c, int height)
// {
//     QVariantList lanePoints;

//     for (int y = height; y >= height / 3; y -= 5)
//     {
//         float x = a * y * y + b * y + c;

//         QVariantMap point;
//         point["x"] = x;
//         point["y"] = y;
//         lanePoints.append(point);
//     }
//     return lanePoints;
// }

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

int InstrumentCluster::getAutonomy() const
{
    return autonomy;
}
void InstrumentCluster::setAutonomy(int value)
{
    if (autonomy != value)
    {
        autonomy = value;
        emit autonomyChanged(value);
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

