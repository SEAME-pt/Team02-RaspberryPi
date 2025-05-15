#ifndef INSTRUMENTCLUSTER_HPP
#define INSTRUMENTCLUSTER_HPP

#include <QObject>
#include <iostream>
#include <memory>
#include "zenoh.hxx"

using namespace zenoh;

class InstrumentCluster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(bool rightBlinker READ getRightBlinker WRITE setRightBlinker
                   NOTIFY rightBlinkerChanged)
    Q_PROPERTY(bool leftBlinker READ getLeftBlinker WRITE setLeftBlinker NOTIFY
                   leftBlinkerChanged)
    Q_PROPERTY(
        bool lowBeam READ getLowBeam WRITE setLowBeam NOTIFY lowBeamChanged)
    Q_PROPERTY(
        bool highBeam READ getHighBeam WRITE setHighBeam NOTIFY highBeamChanged)
    Q_PROPERTY(bool frontFogLight READ getFrontFogLight WRITE setFrontFogLight
                   NOTIFY frontFogLightChanged)
    Q_PROPERTY(bool rearFogLight READ getRearFogLight WRITE setRearFogLight
                   NOTIFY rearFogLightChanged)
    Q_PROPERTY(bool hazardLight READ getHazardLight WRITE setHazardLight NOTIFY
                   hazardLightChanged)
    Q_PROPERTY(bool parkingLight READ getParkingLight WRITE setParkingLight
                   NOTIFY parkingLightChanged)
    Q_PROPERTY(int percentage READ getPercentage WRITE setPercentage NOTIFY
                   percentageChanged)
    Q_PROPERTY(
        int autonomy READ getAutonomy WRITE setAutonomy NOTIFY autonomyChanged)
    Q_PROPERTY(int gear READ getGear WRITE setGear NOTIFY gearChanged)

  private:
    int m_speed;
    bool rightBlinker{false};
    bool leftBlinker{false};
    bool lowBeam{false};
    bool highBeam{false};
    bool frontFogLight{false};
    bool rearFogLight{false};
    bool hazardLight{false};
    bool parkingLight{false};
    int percentage;
    int autonomy;
    int gear;

    std::unique_ptr<zenoh::Session> session;
    std::optional<zenoh::Subscriber<void>> speed_subscriber;
    std::optional<zenoh::Subscriber<void>> beamLow_subscriber;
    std::optional<zenoh::Subscriber<void>> beamHigh_subscriber;
    std::optional<zenoh::Subscriber<void>> running_subscriber;
    std::optional<zenoh::Subscriber<void>> parking_subscriber;
    std::optional<zenoh::Subscriber<void>> fogRear_subscriber;
    std::optional<zenoh::Subscriber<void>> fogFront_subscriber;
    std::optional<zenoh::Subscriber<void>> brake_subscriber;
    std::optional<zenoh::Subscriber<void>> hazard_subscriber;
    std::optional<zenoh::Subscriber<void>> directionIndicatorLeft_subscriber;
    std::optional<zenoh::Subscriber<void>> directionIndicatorRight_subscriber;
    std::optional<zenoh::Subscriber<void>> stateOfCharge_subscriber;
    std::optional<zenoh::Subscriber<void>> maxVoltage_subscriber;
    std::optional<zenoh::Subscriber<void>> currentVoltage_subscriber;
    std::optional<zenoh::Subscriber<void>> currentCurrent_subscriber;
    std::optional<zenoh::Subscriber<void>> currentPower_subscriber;
    std::optional<zenoh::Subscriber<void>> currentGear_subscriber;

  public:
    explicit InstrumentCluster(QObject* parent = nullptr);
    explicit InstrumentCluster(const std::string& configFile,
                               QObject* parent = nullptr);
    ~InstrumentCluster();

    int getSpeed() const;
    void setSpeed(int speed);

    bool getRightBlinker() const;
    void setRightBlinker(bool state);

    bool getLeftBlinker() const;
    void setLeftBlinker(bool state);

    bool getLowBeam() const;
    void setLowBeam(bool state);

    bool getHighBeam() const;
    void setHighBeam(bool state);

    bool getFrontFogLight() const;
    void setFrontFogLight(bool state);

    bool getRearFogLight() const;
    void setRearFogLight(bool state);

    bool getHazardLight() const;
    void setHazardLight(bool state);

    bool getParkingLight() const;
    void setParkingLight(bool state);

    int getPercentage() const;
    void setPercentage(int value);

    int getAutonomy() const;
    void setAutonomy(int value);

    int getGear() const;
    void setGear(int value);

  private:
    void setupSubscriptions();

  signals:
    void speedChanged(int speed);
    void rightBlinkerChanged(bool state);
    void leftBlinkerChanged(bool state);
    void lowBeamChanged(bool state);
    void highBeamChanged(bool state);
    void frontFogLightChanged(bool state);
    void rearFogLightChanged(bool state);
    void hazardLightChanged(bool state);
    void parkingLightChanged(bool state);
    void percentageChanged(int value);
    void autonomyChanged(int value);
    void gearChanged(int gear);
};

#endif // INSTRUMENTCLUSTER_HPP
