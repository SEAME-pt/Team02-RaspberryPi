#ifndef INSTRUMENTCLUSTER_HPP
#define INSTRUMENTCLUSTER_HPP

#include <QObject>
#include <iostream>
#include <memory>
#include "zenoh.hxx"
#include <QVariant>
#include <QPoint>
#include <QVariantList> 
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

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
    Q_PROPERTY(int gear READ getGear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(QVariantMap leftLaneCoefs READ getLeftLaneCoefs WRITE setLeftLaneCoefs NOTIFY leftLaneChanged)
    Q_PROPERTY(QVariantMap rightLaneCoefs READ getRightLaneCoefs WRITE setRightLaneCoefs NOTIFY rightLaneChanged)
    Q_PROPERTY(int warningCode READ getWarningCode WRITE setWarningCode NOTIFY warningCodeChanged)
    Q_PROPERTY(int laneDeparture READ getLaneDeparture WRITE setLaneDeparture NOTIFY laneDepartureChanged)
    Q_PROPERTY(int autonomyLevel READ getAutonomyLevel WRITE setAutonomyLevel NOTIFY autonomyLevelChanged)
    Q_PROPERTY(int signDetected READ getSignDetected WRITE setSignDetected NOTIFY signDetectedChanged)

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
    int laneDeparture{false};
    int percentage;
    int gear;  
    int warningCode;
    int autonomyLevel;
    int signDetected = 0;

    QVariantMap m_leftLaneCoefs;
    QVariantMap m_rightLaneCoefs;
    QVariantList m_detectedObjects;

    // std::shared_ptr<zenoh::Session> sharedsession;

    std::shared_ptr<zenoh::Session> session;
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
    std::optional<zenoh::Subscriber<void>> leftLane_subscriber;
    std::optional<zenoh::Subscriber<void>> rightLane_subscriber;
    std::optional<zenoh::Subscriber<void>> laneDeparture_subscriber;
    std::optional<zenoh::Subscriber<void>> obstacleWarning_subscriber;
    std::optional<zenoh::Subscriber<void>> sae0_subscriber;
    std::optional<zenoh::Subscriber<void>> sae1_subscriber;
    std::optional<zenoh::Subscriber<void>> sae2_subscriber;
    std::optional<zenoh::Subscriber<void>> sae5_subscriber;
    std::optional<zenoh::Subscriber<void>> speedLimit_subscriber;
    std::optional<zenoh::Subscriber<void>> stopSign_subscriber;
    std::optional<zenoh::Subscriber<void>> yieldSign_subscriber;
    std::optional<zenoh::Subscriber<void>> pedestrianZone_subscriber;
    std::optional<zenoh::Subscriber<void>> trafficLight_subscriber;
    std::optional<zenoh::Subscriber<void>> dangerSign_subscriber;
    
  public:
    explicit InstrumentCluster(QObject* parent = nullptr);
    explicit InstrumentCluster(const std::string& configFile,
                               QObject* parent = nullptr);
                               public:
    explicit InstrumentCluster(std::shared_ptr<zenoh::Session> session, QObject* parent = nullptr);
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

    int getGear() const;
    void setGear(int value);

    int getWarningCode() const;
    void setWarningCode(int value);

    int getSignDetected() const;
    void setSignDetected(int value);

    QVariantMap getLeftLaneCoefs() const;
    void setLeftLaneCoefs(const QVariantMap& coefs);

    QVariantMap getRightLaneCoefs() const;
    void setRightLaneCoefs(const QVariantMap& coefs);

    void setLaneDeparture(int state);
    int getLaneDeparture() const;

    void parseLaneData(const std::string& laneData, const std::string& laneType);
    void setupSubscriptions();

    int getAutonomyLevel() const;
    void setAutonomyLevel(int level);
   
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
    void gearChanged(int gear);
    void leftLaneChanged(const QVariantMap& leftLaneCoefs);
    void rightLaneChanged(const QVariantMap& rightLaneCoefs);
    void warningCodeChanged(int code);
    void onSpeedSample(const zenoh::Sample& sample);
    void laneDepartureChanged(bool state);
    void autonomyLevelChanged(int level);
    void signDetectedChanged(int sign);
    #ifdef UNIT_TEST
      std::function<void(const zenoh::Sample&)> getSpeedCallback();
    #endif
};

#endif // INSTRUMENTCLUSTER_HPP
