#ifndef CANBUSHANDLER_HPP
#define CANBUSHANDLER_HPP

#include <QtCore/QObject>

class CANBusHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int battery READ getBattery WRITE setBattery NOTIFY batteryChanged)

public:
    explicit CANBusHandler(QObject *parent = nullptr);
    ~CANBusHandler();

    int getSpeed() const;
    void setSpeed(int speed);
    int getBattery() const;
    void setBattery(int battery);

signals:
    void speedChanged(int speed);
    void batteryChanged(int battery);

private slots:
    void readFrames();

private:
    int canSocket;
    int m_speed;
    int m_battery;
};

#endif // CANBUSHANDLER_HPP
