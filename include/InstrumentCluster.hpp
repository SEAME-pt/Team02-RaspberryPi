#ifndef INSTRUMENTCLUSTER_HPP
#define INSTRUMENTCLUSTER_HPP

#include <QObject>
#include <iostream>
#include "zenoh.hxx"

using namespace zenoh;

struct LightStatus
{
    Q_GADGET

    Q_PROPERTY(bool rightBlinker MEMBER rightBlinker)
    Q_PROPERTY(bool leftBlinker MEMBER leftBlinker)
    Q_PROPERTY(bool lowBeam MEMBER lowBeam)
    Q_PROPERTY(bool highBeam MEMBER highBeam)
    Q_PROPERTY(bool frontFogLight MEMBER frontFogLight)
    Q_PROPERTY(bool rearFogLight MEMBER rearFogLight)
    Q_PROPERTY(bool hazardLight MEMBER hazardLight)
    Q_PROPERTY(bool parkingLight MEMBER parkingLight)

  public:
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

struct BatteryStatus
{
    Q_GADGET

    Q_PROPERTY(int percentage MEMBER percentage)
    Q_PROPERTY(int autonomy MEMBER autonomy)

  public:
    int percentage;
    int autonomy;

    bool operator!=(const BatteryStatus& battery) const
    {
        return percentage != battery.percentage || autonomy != battery.autonomy;
    }
};

struct GearPosition
{
    Q_GADGET

    Q_PROPERTY(bool park MEMBER park)
    Q_PROPERTY(bool reverse MEMBER reverse)
    Q_PROPERTY(bool neutral MEMBER neutral)
    Q_PROPERTY(bool drive MEMBER drive)

  public:
    bool park{true};
    bool reverse{false};
    bool neutral{false};
    bool drive{false};

    bool operator!=(const GearPosition& gear) const
    {
        return park != gear.park || reverse != gear.reverse ||
               neutral != gear.neutral || drive != gear.drive;
    }
};

class InstrumentCluster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(BatteryStatus battery READ getBattery NOTIFY batteryChanged)
    Q_PROPERTY(LightStatus lights READ getLights NOTIFY lightsChanged)
    Q_PROPERTY(GearPosition gear READ getGear NOTIFY gearChanged)

  private:
    int m_speed;
    BatteryStatus m_battery;
    LightStatus m_lights;
    GearPosition m_gear;

    Session m_session;
    Subscriber<void> m_subSpeed;
    Subscriber<void> m_subBattery;
    Subscriber<void> m_subLights;
    Subscriber<void> m_subGear;

  public:
    explicit InstrumentCluster(QObject* parent = nullptr);
    ~InstrumentCluster();

    int getSpeed() const;
    BatteryStatus getBattery() const;
    LightStatus getLights() const;
    GearPosition getGear() const;

    void setSpeed(int speed);
    void setBattery(BatteryStatus battery);
    void setLights(LightStatus lights);
    void setGear(GearPosition gear);

  signals:
    void speedChanged(int speed);
    void batteryChanged(BatteryStatus battery);
    void lightsChanged(LightStatus lights);
    void gearChanged(GearPosition gear);
};

#endif // INSTRUMENTCLUSTER_HPP
