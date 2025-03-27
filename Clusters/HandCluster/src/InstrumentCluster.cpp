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
    
    leftLane_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/leftLaneData",
        [this](const zenoh::Sample& sample) {
            std::string laneData = sample.get_payload().as_string();
            std::cout << "Recebido leftLaneData: " << laneData << std::endl;
            parseLaneData(laneData, "leftLane");
        },
        zenoh::closures::none));

    rightLane_subscriber.emplace(session->declare_subscriber(
        "Vehicle/1/rightLaneData",
        [this](const zenoh::Sample& sample) {
            std::string laneData = sample.get_payload().as_string();
            std::cout << "Recebido rightLaneData: " << laneData << std::endl;
            parseLaneData(laneData, "rightLane");
        },
        zenoh::closures::none));
}

void InstrumentCluster::parseLaneData(const std::string& laneData, const std::string& laneType)
{
    std::istringstream stream(laneData);
    int x, y;

    std::vector<QPoint> lanePoints;

    while (stream >> x >> y) {  
        lanePoints.push_back(QPoint(x, y));
    }

    QVariantList laneList;
    for (const auto& point : lanePoints) {
        QVariantMap map;
        map["x"] = point.x();
        map["y"] = point.y();
        laneList.append(map);
    }

    if (laneType == "leftLane") {
        setLeftLanePoints(laneList);
    } else {
        setRightLanePoints(laneList);
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
        QVariantMap map = var.toMap();
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
    
    emit leftLaneChanged(leftLaneList);
}


void InstrumentCluster::setRightLanePoints(const QVariantList& points) {
    std::vector<QPoint> pointVec;

    for (const auto& var : points) {
        QVariantMap map = var.toMap();
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
    
    emit rightLaneChanged(rightLaneList);
}





