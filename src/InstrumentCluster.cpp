#include "../include/InstrumentCluster.hpp"

InstrumentCluster::InstrumentCluster(Session& session, QObject* parent)
    : QObject(parent), m_speed(0), m_battery(0), m_rightBlinker(false),
      m_leftBlinker(false), m_lowBeam(false), m_highBeam(false),
      m_frontFogLight(false), m_rearFogLight(false), m_hazardLight(false),
      m_parkingLight(false), m_gear(GearPosition::PARK), m_session(session)
{
}

InstrumentCluster::~InstrumentCluster()
{
    m_session.close();
}

int InstrumentCluster::getSpeed() const
{
    return m_speed;
}

int InstrumentCluster::getBattery() const
{
    return m_battery;
}

bool InstrumentCluster::getRightBlinker() const
{
    return m_rightBlinker;
}

bool InstrumentCluster::getLeftBlinker() const
{
    return m_leftBlinker;
}

bool InstrumentCluster::getLowBeam() const
{
    return m_lowBeam;
}

bool InstrumentCluster::getHighBeam() const
{
    return m_highBeam;
}

bool InstrumentCluster::getFrontFogLight() const
{
    return m_frontFogLight;
}

bool InstrumentCluster::getRearFogLight() const
{
    return m_rearFogLight;
}

bool InstrumentCluster::getHazardLight() const
{
    return m_hazardLight;
}

bool InstrumentCluster::getParkingLight() const
{
    return m_parkingLight;
}

GearPosition InstrumentCluster::getGear() const
{
    return m_gear;
}

void InstrumentCluster::setSpeed(int speed)
{
    if (m_speed != speed)
    {
        m_speed = speed;
        emit speedChanged(m_speed);
    }
}

void InstrumentCluster::setBattery(int battery)
{
    if (m_battery != battery)
    {
        m_battery = battery;
        emit batteryChanged(m_battery);
    }
}

void InstrumentCluster::setRightBlinker(bool rightBlinker)
{
    if (m_rightBlinker != rightBlinker)
    {
        m_rightBlinker = rightBlinker;
        emit rightBlinkerChanged(m_rightBlinker);
    }
}

void InstrumentCluster::setLeftBlinker(bool leftBlinker)
{
    if (m_leftBlinker != leftBlinker)
    {
        m_leftBlinker = leftBlinker;
        emit leftBlinkerChanged(m_leftBlinker);
    }
}

void InstrumentCluster::setLowBeam(bool lowBeam)
{
    if (m_lowBeam != lowBeam)
    {
        m_lowBeam = lowBeam;
        emit lowBeamChanged(m_lowBeam);
    }
}

void InstrumentCluster::setHighBeam(bool highBeam)
{
    if (m_highBeam != highBeam)
    {
        m_highBeam = highBeam;
        emit batteryChanged(m_highBeam);
    }
}

void InstrumentCluster::setFrontFogLight(bool frontFogLight)
{
    if (m_frontFogLight != frontFogLight)
    {
        m_frontFogLight = frontFogLight;
        emit speedChanged(m_frontFogLight);
    }
}

void InstrumentCluster::setRearFogLight(bool rearFogLight)
{
    if (m_rearFogLight != rearFogLight)
    {
        m_rearFogLight = rearFogLight;
        emit rightBlinkerChanged(m_rearFogLight);
    }
}

void InstrumentCluster::setHazardLight(bool hazardLight)
{
    if (m_hazardLight != hazardLight)
    {
        m_hazardLight = hazardLight;
        emit speedChanged(m_hazardLight);
    }
}

void InstrumentCluster::setParkingLight(bool parkingLight)
{
    if (m_parkingLight != parkingLight)
    {
        m_parkingLight = parkingLight;
        emit parkingLightChanged(m_parkingLight);
    }
}

void InstrumentCluster::setGear(GearPosition gear)
{
    if (m_gear != gear)
    {
        m_gear = gear;
        emit gearChanged(m_gear);
    }
}
