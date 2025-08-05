#ifndef INSTRUMENTCLUSTERTEST_HPP
#define INSTRUMENTCLUSTERTEST_HPP

#include <QObject>
#include "zenoh.hxx"
class TestInstrumentCluster : public QObject
{
    Q_OBJECT

private slots: // Test functions should be in private slots
    void testFontLoading();
    void testInstrumentClusterInitialization();
    void testSetSpeed();
    void testSetWarningCode();
    void testSetHighBeam();
    void testSetLowBeam();
    void testBlinkers();
    void testParseLaneData(); // Move this to private slots
    void testLights();
    void testPercentage();
    void testAutonomy();
    void testGear();
    void testSubscriptionsIntegration();
    void testSetSignDetected();
    void testLaneDeparture();
    void testAutonomyLevel();
    void testInstrumentClusterConstructor();
    // void testSpeedCallback();
};


#endif // INSTRUMENTCLUSTERTEST_HPP