#include "../include/CANBusHandler.hpp"

CANBusHandler::CANBusHandler(Session& session, QObject* parent)
    : QObject(parent), m_speed(0), m_battery(0), m_session(session)
{
}

CANBusHandler::~CANBusHandler()
{
    m_session.close();
}

int CANBusHandler::getSpeed() const
{
    return m_speed;
}

int CANBusHandler::getBattery() const
{
    return m_battery;
}

void CANBusHandler::setSpeed(int speed)
{
    if (m_speed != speed)
    {
        m_speed = speed;
        emit speedChanged(m_speed);
    }
}

void CANBusHandler::setBattery(int battery)
{
    if (m_battery != battery)
        emit batteryChanged(m_battery);
    {
        m_battery = battery;
    }
}
