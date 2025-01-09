#ifndef CANBUSHANDLER_HPP
#define CANBUSHANDLER_HPP

#include <QObject>
#include <iostream>
#include "zenoh.hxx"

using namespace zenoh;

class CANBusHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(int battery READ getBattery NOTIFY batteryChanged)

  public:
    explicit CANBusHandler(Session& session, QObject* parent = nullptr);
    ~CANBusHandler();

    int getSpeed() const;
    int getBattery() const;
    void setSpeed(int speed);
    void setBattery(int battery);

  signals:
    void speedChanged(int speed);
    void batteryChanged(int battery);

  private:
    int m_speed;
    int m_battery;
    Session& m_session;
};

#endif // CANBUSHANDLER_HPP
