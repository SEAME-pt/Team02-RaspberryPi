#include "../include/InstrumentCluster.hpp"
#include <QPoint>

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
    
    lanes_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/LaneData",
        [this](const zenoh::Sample& sample)
        {
            std::string laneData = sample.get_payload().as_string();
            parseLaneData(laneData);
        },
        zenoh::closures::none));
}

/* LANE DATA SYNTAX

std::string laneData = "leftLane: 300,500 320,400\nrightLane: 600,500 580,400";

session->declare_publisher("Vehicle/1/LaneData", laneData);
leftLane: 300 500 320 400
rightLane: 600 500 580 400

*/

void InstrumentCluster::parseLaneData(const std::string& laneData)
{
    std::istringstream stream(laneData);
    std::string line;

    std::vector<QPoint> leftLane;
    std::vector<QPoint> rightLane;

    while (std::getline(stream, line))
    {
        std::istringstream lineStream;
        std::string laneType;

        if (line.rfind("leftLane:", 0) == 0) 
        {
            laneType = "leftLane";
            line = line.substr(10); 
        }
        else if (line.rfind("rightLane:", 0) == 0){

            laneType = "rightLane";
            line = line.substr(11);
        }
        else
        {
            continue;
        }

        // 🔹 Substituir ',' por ' ' para permitir leitura correta dos números
        for (char &c : line) {
            if (c == ',') c = ' ';
        }

        lineStream = std::istringstream(line);

        int x, y;
        while (lineStream >> x >> y)
        {   
            if (laneType == "leftLane")
                leftLane.push_back(QPoint(x, y));
            else
                rightLane.push_back(QPoint(x, y));
        }
    }

    QVariantList leftLaneList;
    for (const auto& point : leftLane) {
        QVariantMap map;
        map["x"] = point.x();
        map["y"] = point.y();
        leftLaneList.append(map);
    }
    // std::cout << "Left Lane: " << leftLaneList.size() << std::endl;
    setLeftLanePoints(leftLaneList);

    QVariantList rightLaneList;
    for (const auto& point : rightLane) {
        QVariantMap map;
        map["x"] = point.x();
        map["y"] = point.y();
        std::cout << "Right Lane in parsing: " << point.x() << " " << point.y() << std::endl;
        rightLaneList.append(map);
    }
    setRightLanePoints(rightLaneList);
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

// Blinkers
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

QVariantList InstrumentCluster::getLeftLanePoints() const {
    QVariantList list;
    for (const auto& point : m_leftLanePoints) {
        QVariantMap map;
        map["x"] = point.x();
        map["y"] = point.y();
        list.append(map);
    }
    return list;
}

QVariantList InstrumentCluster::getRightLanePoints() const {
     QVariantList list;
    for (const auto& point : m_rightLanePoints) {
        QVariantMap map;
        map["x"] = point.x();
        map["y"] = point.y();
        list.append(map);
    }
    return list;
}
void InstrumentCluster::setLeftLanePoints(const QVariantList& points) {
    std::vector<QPoint> pointVec;

    for (const auto& var : points) {
        QVariantMap map = var.toMap();  // Converte QVariant para QVariantMap
        if (map.contains("x") && map.contains("y")) {
            int x = map["x"].toInt();
            int y = map["y"].toInt();
            pointVec.push_back(QPoint(x, y));
        }
    }
    m_leftLanePoints = pointVec;

    QVariantList leftLaneList;
    for (const auto& point : m_leftLanePoints) {
        QVariantMap map;
        map["x"] = point.x();
        map["y"] = point.y();
        std::cout << "Left Lane: " << point.x() << " " << point.y() << std::endl;
        leftLaneList.append(map);
    }
    
    emit leftLaneChanged(leftLaneList);  // Emit QVariantList, not std::vector<QPoint>
}


void InstrumentCluster::setRightLanePoints(const QVariantList& points) {
    std::vector<QPoint> pointVec;

    for (const auto& var : points) {
        QVariantMap map = var.toMap();  // Converte QVariant para QVariantMap
        if (map.contains("x") && map.contains("y")) {
            int x = map["x"].toInt();
            int y = map["y"].toInt();
            pointVec.push_back(QPoint(x, y));
        }
    }
    m_rightLanePoints = pointVec;

    QVariantList rightLaneList;
    for (const auto& point : m_rightLanePoints) {
        QVariantMap map;
        map["x"] = point.x();
        map["y"] = point.y();
        std::cout << "Right Lane: " << point.x() << " " << point.y() << std::endl;
        rightLaneList.append(map);
    }
    
    emit rightLaneChanged(rightLaneList);  // Emit QVariantList, not std::vector<QPoint>
}





