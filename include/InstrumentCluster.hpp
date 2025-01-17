#ifndef INSTRUMENTCLUSTER_HPP
#define INSTRUMENTCLUSTER_HPP

#include <QObject>
#include <iostream>
#include "zenoh.hxx"

using namespace zenoh;

struct LightStatus
{
    bool rightBlinker{false};
    bool leftBlinker{false};
    bool lowBeam{false};
    bool highBeam{false};
    bool frontFogLight{false};
    bool rearFogLight{false};
    bool hazardLight{false};
    bool parkingLight{false};

    bool operator!=(const LightStatus& lights) const
    {
        return rightBlinker != lights.rightBlinker ||
               leftBlinker != lights.leftBlinker || lowBeam != lights.lowBeam ||
               highBeam != lights.highBeam ||
               frontFogLight != lights.frontFogLight ||
               rearFogLight != lights.rearFogLight ||
               hazardLight != lights.hazardLight ||
               parkingLight != lights.parkingLight;
    }
};

enum GearPosition
{
    PARK,
    REVERSE,
    NEUTRAL,
    DRIVE
};

class InstrumentCluster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(int battery READ getBattery NOTIFY batteryChanged)
    Q_PROPERTY(
        bool rightBlinker READ getRightBlinker NOTIFY rightBlinkerChanged)
    Q_PROPERTY(bool leftBlinker READ getLeftBlinker NOTIFY leftBlinkerChanged)
    Q_PROPERTY(bool lowBeam READ getLowBeam NOTIFY lowBeamChanged)
    Q_PROPERTY(bool highBeam READ getHighBeam NOTIFY highBeamChanged)
    Q_PROPERTY(
        bool frontFogLight READ getFrontFogLight NOTIFY frontFogLightChanged)
    Q_PROPERTY(
        bool readFogLight READ getRearFogLight NOTIFY rearFogLightChanged)
    Q_PROPERTY(bool hazardLight READ getHazardLight NOTIFY hazardLightChanged)
    Q_PROPERTY(
        bool parkingLight READ getParkingLight NOTIFY parkingLightChanged)
    Q_PROPERTY(GearPosition gear READ getGear NOTIFY gearChanged)

  public:
    enum class GearPosition
    {
        PARK,
        REVERSE,
        NEUTRAL,
        DRIVE
    };

    Q_ENUM(GearPosition)

  private:
    int m_speed;
    int m_battery;
    bool m_rightBlinker;
    bool m_leftBlinker;
    bool m_lowBeam;
    bool m_highBeam;
    bool m_frontFogLight;
    bool m_rearFogLight;
    bool m_hazardLight;
    bool m_parkingLight;
    GearPosition m_gear;

    Session& m_session;

  public:
    explicit InstrumentCluster(Session& session, QObject* parent = nullptr);
    ~InstrumentCluster();

    int getSpeed() const;
    int getBattery() const;
    bool getRightBlinker() const;
    bool getLeftBlinker() const;
    bool getLowBeam() const;
    bool getHighBeam() const;
    bool getFrontFogLight() const;
    bool getRearFogLight() const;
    bool getHazardLight() const;
    bool getParkingLight() const;
    GearPosition getGear() const;

    void setSpeed(int speed);
    void setBattery(int battery);
    void setRightBlinker(bool rightBlinker);
    void setLeftBlinker(bool leftBlinker);
    void setLowBeam(bool lowBeam);
    void setHighBeam(bool highBeam);
    void setFrontFogLight(bool frontFogLight);
    void setRearFogLight(bool readFogLight);
    void setHazardLight(bool hazardLight);
    void setParkingLight(bool parkingLight);
    void setGear(GearPosition gear);

  signals:
    void speedChanged(int speed);
    void batteryChanged(int battery);
    void rightBlinkerChanged(bool rightBlinker);
    void leftBlinkerChanged(bool leftBlinker);
    void lowBeamChanged(bool lowBeam);
    void highBeamChanged(bool highBeam);
    void frontFogLightChanged(bool frontFogLight);
    void rearFogLightChanged(bool readFogLight);
    void hazardLightChanged(bool hazardLight);
    void parkingLightChanged(bool parkingLight);
    void gearChanged(GearPosition gear);
};

#endif // INSTRUMENTCLUSTER_HPP
