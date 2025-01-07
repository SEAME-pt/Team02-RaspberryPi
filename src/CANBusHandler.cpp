#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/CANBusHandler.hpp"

CANBusHandler::CANBusHandler(QObject* parent)
    : QObject(parent), canSocket(-1), m_speed(0), m_battery(0)
{
    struct ifreq ifr;
    struct sockaddr_can addr;

    canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (canSocket < 0)
    {
        qWarning() << "Cannot create CAN socket!";
        return;
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(canSocket, SIOCGIFINDEX, &ifr);

    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(canSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        qWarning() << "Cannot bind CAN socket!";
        close(canSocket);
        return;
    }

    qDebug() << "CAN socket bound to can0 interface successfully.";

    // Set up a timer to periodically read frames
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() { readFrames(); });
    timer->start(10); // Adjust the interval as needed
}

CANBusHandler::~CANBusHandler()
{
    if (canSocket >= 0)
    {
        close(canSocket); // Close the CAN socket
    }
}

int CANBusHandler::getSpeed() const
{
    return m_speed;
}

void CANBusHandler::setSpeed(int speed)
{
    if (m_speed != speed)
    {
        m_speed = speed;
        emit speedChanged(m_speed);
    }
}

int CANBusHandler::getBattery() const
{
    return m_battery;
}

void CANBusHandler::setBattery(int battery)
{
    if (m_battery != battery)
    {
        m_battery = battery;
        emit batteryChanged(m_battery);
    }
}

void CANBusHandler::readFrames()
{
    struct can_frame frame;
    int nbytes = read(canSocket, &frame, sizeof(struct can_frame));

    if (nbytes < 0)
    {
        qWarning() << "Error reading CAN frame!";
        return;
    }

    if (frame.can_id == 0x01)
    {
        int speed;
        memcpy(&speed, frame.data, sizeof(int));

        speed = ntohl(speed);

        // qDebug() << "Speed:" << speed; // Print the speed value
        setSpeed(speed);
    }
    else if (frame.can_id == 0x02)
    {
        int battery;
        memcpy(&battery, frame.data, sizeof(int));

        battery = ntohl(battery);

        // qDebug() << "Battery:" << battery; // Print the speed value
        setBattery(battery);
    }
}
