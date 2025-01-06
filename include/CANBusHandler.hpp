#ifndef CANBUSHANDLER_HPP
#define CANBUSHANDLER_HPP

#include <QtCore/QObject>

class CANBusHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit CANBusHandler(QObject *parent = nullptr);
    ~CANBusHandler();

    int getSpeed() const;
    void setSpeed(int speed);

signals:
    void speedChanged(int speed);

private slots:
    void readFrames();

private:
    int canSocket;  // File descriptor for the CAN socket
    int m_speed;    // Member variable for the speed
};

#endif // CANBUSHANDLER_HPP
