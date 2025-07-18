// #include "InstrumentClusterTest.hpp"
// #include "../include/InstrumentCluster.hpp"

// #include <QFontDatabase>
// #include <QSignalSpy>
// #include <QTest>
// #include <QJsonArray>
// #include <QJsonObject>
// #include <QJsonDocument>

// void TestInstrumentCluster::testFontLoading()
// {
//     int fontId = QFontDatabase::addApplicationFont("/usr/share/fonts/electrolize.ttf");
//     QVERIFY(fontId != -1);
// }

// void TestInstrumentCluster::testInstrumentClusterInitialization()
// {
//     InstrumentCluster cluster;
//     cluster.setObjectName("InstrumentCluster");
//     QVERIFY(!cluster.objectName().isEmpty());
// }

// void TestInstrumentCluster::testSetSpeed()
// {
//     InstrumentCluster cluster;
//     QSignalSpy spy(&cluster, &InstrumentCluster::speedChanged);

//     cluster.setSpeed(80);
//     QCOMPARE(cluster.getSpeed(), 80);
//     QCOMPARE(spy.count(), 1);

//     cluster.setSpeed(80);
//     QCOMPARE(spy.count(), 1);
// }

// void TestInstrumentCluster::testParseLaneData()
// {
//     InstrumentCluster cluster;

//     // Test left lane
//     QSignalSpy leftSpy(&cluster, &InstrumentCluster::leftLaneChanged);
//     cluster.parseLaneData("1.0 2.0 3.0", "leftLane");
//     QVariantMap leftCoefs = cluster.getLeftLaneCoefs();

//     QCOMPARE(leftCoefs["a"].toFloat(), 1.0f);
//     QCOMPARE(leftCoefs["b"].toFloat(), 2.0f);
//     QCOMPARE(leftCoefs["c"].toFloat(), 3.0f);
//     QCOMPARE(leftSpy.count(), 1);

//     // Test right lane
//     QSignalSpy rightSpy(&cluster, &InstrumentCluster::rightLaneChanged);
//     cluster.parseLaneData("4.0 5.0 6.0", "rightLane");
//     QVariantMap rightCoefs = cluster.getRightLaneCoefs();

//     QCOMPARE(rightCoefs["a"].toFloat(), 4.0f);
//     QCOMPARE(rightCoefs["b"].toFloat(), 5.0f);
//     QCOMPARE(rightCoefs["c"].toFloat(), 6.0f);
//     QCOMPARE(rightSpy.count(), 1);
// }


// void TestInstrumentCluster::testSetWarningCode()
// {
//     InstrumentCluster cluster;
//     QSignalSpy spy(&cluster, &InstrumentCluster::warningCodeChanged);

//     cluster.setWarningCode(3);
//     QCOMPARE(cluster.getWarningCode(), 3);
//     QCOMPARE(spy.count(), 1);
// }

// void TestInstrumentCluster::testSetHighBeam()
// {
//     InstrumentCluster cluster;
//     QSignalSpy spy(&cluster, &InstrumentCluster::highBeamChanged);

//     cluster.setHighBeam(true);
//     QCOMPARE(cluster.getHighBeam(), true);
//     QCOMPARE(spy.count(), 1);
// }

// void TestInstrumentCluster::testSetLowBeam()
// {
//     InstrumentCluster cluster;
//     QSignalSpy spy(&cluster, &InstrumentCluster::lowBeamChanged);

//     cluster.setLowBeam(true);
//     QCOMPARE(cluster.getLowBeam(), true);
//     QCOMPARE(spy.count(), 1);

//     cluster.setLowBeam(false);
//     QCOMPARE(cluster.getLowBeam(), false);
//     QCOMPARE(spy.count(), 2);
// }

// void TestInstrumentCluster::testBlinkers()
// {
//     InstrumentCluster cluster;

//     // Test right blinker
//     QSignalSpy rightBlinkerSpy(&cluster, &InstrumentCluster::rightBlinkerChanged);
//     cluster.setRightBlinker(true);
//     QCOMPARE(cluster.getRightBlinker(), true);
//     QCOMPARE(rightBlinkerSpy.count(), 1);

//     cluster.setRightBlinker(false);
//     QCOMPARE(cluster.getRightBlinker(), false);
//     QCOMPARE(rightBlinkerSpy.count(), 2);

//     // Test left blinker
//     QSignalSpy leftBlinkerSpy(&cluster, &InstrumentCluster::leftBlinkerChanged);
//     cluster.setLeftBlinker(true);
//     QCOMPARE(cluster.getLeftBlinker(), true);
//     QCOMPARE(leftBlinkerSpy.count(), 1);

//     cluster.setLeftBlinker(false);
//     QCOMPARE(cluster.getLeftBlinker(), false);
//     QCOMPARE(leftBlinkerSpy.count(), 2);
// }

// void TestInstrumentCluster::testLights()
// {
//     InstrumentCluster cluster;

//     QSignalSpy frontFogSpy(&cluster, &InstrumentCluster::frontFogLightChanged);
//     cluster.setFrontFogLight(true);
//     QCOMPARE(cluster.getFrontFogLight(), true);
//     QCOMPARE(frontFogSpy.count(), 1);

//     cluster.setFrontFogLight(false);
//     QCOMPARE(cluster.getFrontFogLight(), false);
//     QCOMPARE(frontFogSpy.count(), 2);

//     QSignalSpy rearFogSpy(&cluster, &InstrumentCluster::rearFogLightChanged);
//     cluster.setRearFogLight(true);
//     QCOMPARE(cluster.getRearFogLight(), true);
//     QCOMPARE(rearFogSpy.count(), 1);

//     cluster.setRearFogLight(false);
//     QCOMPARE(cluster.getRearFogLight(), false);
//     QCOMPARE(rearFogSpy.count(), 2);

//     QSignalSpy hazardSpy(&cluster, &InstrumentCluster::hazardLightChanged);
//     cluster.setHazardLight(true);
//     QCOMPARE(cluster.getHazardLight(), true);
//     QCOMPARE(hazardSpy.count(), 1);

//     cluster.setHazardLight(false);
//     QCOMPARE(cluster.getHazardLight(), false);
//     QCOMPARE(hazardSpy.count(), 2);

//     QSignalSpy parkingSpy(&cluster, &InstrumentCluster::parkingLightChanged);
//     cluster.setParkingLight(true);
//     QCOMPARE(cluster.getParkingLight(), true);
//     QCOMPARE(parkingSpy.count(), 1);

//     cluster.setParkingLight(false);
//     QCOMPARE(cluster.getParkingLight(), false);
//     QCOMPARE(parkingSpy.count(), 2);
// }

// void TestInstrumentCluster::testPercentage()
// {
//     InstrumentCluster cluster;
//     QSignalSpy spy(&cluster, &InstrumentCluster::percentageChanged);

//     cluster.setPercentage(50);
//     QCOMPARE(cluster.getPercentage(), 50);
//     QCOMPARE(spy.count(), 1);

//     cluster.setPercentage(75);
//     QCOMPARE(cluster.getPercentage(), 75);
//     QCOMPARE(spy.count(), 2);
// }

// void TestInstrumentCluster::testAutonomy()
// {
//     InstrumentCluster cluster;
//     QSignalSpy spy(&cluster, &InstrumentCluster::autonomyLevelChanged);

//     cluster.setAutonomyLevel(200);
//     QCOMPARE(cluster.getAutonomyLevel(), 200);
//     QCOMPARE(spy.count(), 1);

//     cluster.setAutonomyLevel(300);
//     QCOMPARE(cluster.getAutonomyLevel(), 300);
//     QCOMPARE(spy.count(), 2);
// }

// void TestInstrumentCluster::testGear()
// {
//     InstrumentCluster cluster;
//     QSignalSpy spy(&cluster, &InstrumentCluster::gearChanged);

//     cluster.setGear(1);
//     QCOMPARE(cluster.getGear(), 1);
//     QCOMPARE(spy.count(), 1);

//     cluster.setGear(2);
//     QCOMPARE(cluster.getGear(), 2);
//     QCOMPARE(spy.count(), 2);
// }


// void TestInstrumentCluster::testSetSignDetected()
// {
//     // Create a Zenoh session
//     auto config = zenoh::Config::create_default();
//     auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
//     QVERIFY(session != nullptr);

//     // Create an InstrumentCluster instance
//     InstrumentCluster cluster(session);

//     // Test setting different signs
//     cluster.setSignDetected(0);  // Set to "20"
//     QCOMPARE(cluster.getSignDetected(), 0);

//     cluster.setSignDetected(1);  // Set to "30"
//     QCOMPARE(cluster.getSignDetected(), 1);

//     cluster.setSignDetected(2);  // Set to "40"
//     QCOMPARE(cluster.getSignDetected(), 2);

//     cluster.setSignDetected(3);  // Set to "50"
//     QCOMPARE(cluster.getSignDetected(), 3);

//     cluster.setSignDetected(4);  // Set to "60"
//     QCOMPARE(cluster.getSignDetected(), 4);

//     cluster.setSignDetected(5);  // Set to "70"
//     QCOMPARE(cluster.getSignDetected(), 5);

//     cluster.setSignDetected(6);  // Set to "80"
//     QCOMPARE(cluster.getSignDetected(), 6);

//     cluster.setSignDetected(7);  // Set to "90"
//     QCOMPARE(cluster.getSignDetected(), 7);

//     cluster.setSignDetected(8);  // Set to "100"
//     QCOMPARE(cluster.getSignDetected(), 8);

//     cluster.setSignDetected(9);  // Set to "120"
//     QCOMPARE(cluster.getSignDetected(), 9);

//     // Test setting an invalid sign
//     cluster.setSignDetected(99);  // Invalid value
//     QCOMPARE(cluster.getSignDetected(), 0);  // Falls back to default or error handling
// }

// void TestInstrumentCluster::testLaneDeparture()
// {
//     InstrumentCluster cluster;

//     QCOMPARE(cluster.getLaneDeparture(), false);

//     bool signalEmitted = false;
//     QObject::connect(&cluster, &InstrumentCluster::laneDepartureChanged, [&](bool state) {
//         signalEmitted = true;
//         QCOMPARE(state, true);
//     });

//     cluster.setLaneDeparture(true);
//     QCOMPARE(cluster.getLaneDeparture(), true);
//     QVERIFY(signalEmitted);

//     signalEmitted = false;

//     cluster.setLaneDeparture(false);
//     QCOMPARE(cluster.getLaneDeparture(), false); 
//     QVERIFY(signalEmitted);

//     signalEmitted = false;
//     cluster.setLaneDeparture(false);
//     QCOMPARE(cluster.getLaneDeparture(), false); 
//     QVERIFY(!signalEmitted); 
// }

// void TestInstrumentCluster::testSubscriptionsIntegration()
// {
//     auto config = zenoh::Config::create_default();
//     auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
//     QVERIFY(session != nullptr);

//     InstrumentCluster cluster(session);
//     cluster.setupSubscriptions();
//     QTest::qWait(200); 

//     auto publish = [&](const std::string& resource, const std::string& value) {
//         std::vector<uint8_t> payload(value.begin(), value.end());
//         session->put(resource, payload);
//     };

//     // Test basic existing topics
//     publish("Vehicle/1/Speed", "100");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSpeed(), 100);

//     publish("Vehicle/1/Body/Lights/Beam/Low", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getLowBeam(), true);

//     publish("Vehicle/1/Body/Lights/Beam/High", "0");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getHighBeam(), false);

//     publish("Vehicle/1/Powertrain/TractionBattery/StateOfCharge", "85");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getPercentage(), 85);

//     publish("Vehicle/1/Powertrain/Transmission/CurrentGear", "3");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getGear(), 3);

//     // ✅ New topics to test
//     publish("Vehicle/1/Body/Lights/DirectionIndicator/Left", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getLeftBlinker(), true);

//     publish("Vehicle/1/Body/Lights/DirectionIndicator/Right", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getRightBlinker(), true);

//     publish("Vehicle/1/Body/Lights/Hazard", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getHazardLight(), true);

//     publish("Vehicle/1/Body/Lights/Fog/Front", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getFrontFogLight(), true);

//     publish("Vehicle/1/Body/Lights/Fog/Rear", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getRearFogLight(), true);

//     publish("Vehicle/1/Body/Lights/Parking", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getParkingLight(), true);


//     publish("Vehicle/1/Scene/Lanes/Left", R"({"a":1,"b":2,"c":3})");
//     QTest::qWait(100);
//     {
//         QVariantMap expected;
//         expected.insert("a", 1);
//         expected.insert("b", 2);
//         expected.insert("c", 3);
//         QCOMPARE(cluster.getLeftLaneCoefs(), expected);
//     }

//     // Publish right lane data
//     publish("Vehicle/1/Scene/Lanes/Right", R"({"a":4,"b":5,"c":6})");
//     QTest::qWait(100);
//     {
//         QVariantMap expected;
//         expected.insert("a", 4);
//         expected.insert("b", 5);
//         expected.insert("c", 6);
//         QCOMPARE(cluster.getRightLaneCoefs(), expected);
//     }

//     // Test lane departure to the left (code 10)
//     publish("Vehicle/1/ADAS/LaneDeparture/Detected", "10");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getLaneDeparture(), 10);
//     QCOMPARE(cluster.getWarningCode(), 2);

//     // Test lane departure cleared (code 11)
//     publish("Vehicle/1/ADAS/LaneDeparture/Detected", "11");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getLaneDeparture(), 11);
//     QCOMPARE(cluster.getWarningCode(), 0);

//     // Test lane departure to the right (code 20)
//     publish("Vehicle/1/ADAS/LaneDeparture/Detected", "20");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getLaneDeparture(), 20);
//     QCOMPARE(cluster.getWarningCode(), 2);
    
//         // 🚦 Test speed limit sign detection via Zenoh
//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "20");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 0);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "30");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 1);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "40");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 2);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "50");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 3);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "60");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 4);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "70");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 5);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "80");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 6);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "90");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 7);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "100");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 8);

//     publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "120");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getSignDetected(), 9);

//     publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_0", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getAutonomyLevel(), 0);

//     publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getAutonomyLevel(), 1);

//     publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_2", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getAutonomyLevel(), 2);

//     publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5", "1");
//     QTest::qWait(100);
//     QCOMPARE(cluster.getAutonomyLevel(), 5);


// }

// void TestInstrumentCluster::testAutonomyLevel()
// {
//     // Create an InstrumentCluster instance
//     InstrumentCluster cluster;

//     // Set autonomy level to 2
//     cluster.setAutonomyLevel(2);
//     QCOMPARE(cluster.getAutonomyLevel(), 2); // Verify state is updated

//     // Set autonomy level to 5
//     cluster.setAutonomyLevel(5);
//     QCOMPARE(cluster.getAutonomyLevel(), 5); // Verify state is updated

//     // Test setting the same level (signal should not be emitted)
//     cluster.setAutonomyLevel(5);
//     QCOMPARE(cluster.getAutonomyLevel(), 5); // State remains unchanged
// }

// void TestInstrumentCluster::testInstrumentClusterConstructor()
// {
//     // Path to a valid Zenoh configuration file
//     const std::string configFile = "../zenoh-config-test-file.json";

//     // Ensure the configuration file exists
//     QVERIFY(QFile::exists(QString::fromStdString(configFile)));

//     // Create an InstrumentCluster instance
//     InstrumentCluster cluster(configFile);
//     // Verify that the constructor does not throw exceptions
// }

// QTEST_MAIN(TestInstrumentCluster)


#include "InstrumentClusterTest.hpp"
#include "../include/InstrumentCluster.hpp"

#include <QFontDatabase>
#include <QSignalSpy>
#include <QTest>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

// Your test methods are already thorough and impressive.
// Below are just a few suggestions and one small fix to make it more comprehensive and aligned with your full implementation:

// Add a test to validate constructor from config file
void TestInstrumentCluster::testInstrumentClusterConstructorFromFile()
{
    const std::string configFile = "../zenoh-config-test-file.json";
    QVERIFY(QFile::exists(QString::fromStdString(configFile)));

    InstrumentCluster cluster(configFile);
}

// Add a test for cruise control
void TestInstrumentCluster::testCruiseControl()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::cruiseControlChanged);

    cluster.setCruiseControl(true);
    QCOMPARE(cluster.getCruiseControl(), true);
    QCOMPARE(spy.count(), 1);

    cluster.setCruiseControl(false);
    QCOMPARE(cluster.getCruiseControl(), false);
    QCOMPARE(spy.count(), 2);

    cluster.setCruiseControl(false);
    QCOMPARE(spy.count(), 2); // No new signal should be emitted
}

// Add a test for sign detection fallback
#include "InstrumentClusterTest.hpp"
#include "../include/InstrumentCluster.hpp"

#include <QFontDatabase>
#include <QSignalSpy>
#include <QTest>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

void TestInstrumentCluster::testFontLoading()
{
    int fontId = QFontDatabase::addApplicationFont("/usr/share/fonts/electrolize.ttf");
    QVERIFY(fontId != -1);
}

void TestInstrumentCluster::testInstrumentClusterInitialization()
{
    InstrumentCluster cluster;
    cluster.setObjectName("InstrumentCluster");
    QVERIFY(!cluster.objectName().isEmpty());
}

void TestInstrumentCluster::testSetSpeed()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::speedChanged);

    cluster.setSpeed(80);
    QCOMPARE(cluster.getSpeed(), 80);
    QCOMPARE(spy.count(), 1);

    cluster.setSpeed(80);
    QCOMPARE(spy.count(), 1);
}

void TestInstrumentCluster::testParseLaneData()
{
    InstrumentCluster cluster;

    // Test left lane
    QSignalSpy leftSpy(&cluster, &InstrumentCluster::leftLaneChanged);
    cluster.parseLaneData("1.0 2.0 3.0", "leftLane");
    QVariantMap leftCoefs = cluster.getLeftLaneCoefs();

    QCOMPARE(leftCoefs["a"].toFloat(), 1.0f);
    QCOMPARE(leftCoefs["b"].toFloat(), 2.0f);
    QCOMPARE(leftCoefs["c"].toFloat(), 3.0f);
    QCOMPARE(leftSpy.count(), 1);

    // Test right lane
    QSignalSpy rightSpy(&cluster, &InstrumentCluster::rightLaneChanged);
    cluster.parseLaneData("4.0 5.0 6.0", "rightLane");
    QVariantMap rightCoefs = cluster.getRightLaneCoefs();

    QCOMPARE(rightCoefs["a"].toFloat(), 4.0f);
    QCOMPARE(rightCoefs["b"].toFloat(), 5.0f);
    QCOMPARE(rightCoefs["c"].toFloat(), 6.0f);
    QCOMPARE(rightSpy.count(), 1);
}


void TestInstrumentCluster::testSetWarningCode()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::warningCodeChanged);

    cluster.setWarningCode(3);
    QCOMPARE(cluster.getWarningCode(), 3);
    QCOMPARE(spy.count(), 1);
}

void TestInstrumentCluster::testSetHighBeam()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::highBeamChanged);

    cluster.setHighBeam(true);
    QCOMPARE(cluster.getHighBeam(), true);
    QCOMPARE(spy.count(), 1);
}

void TestInstrumentCluster::testSetLowBeam()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::lowBeamChanged);

    cluster.setLowBeam(true);
    QCOMPARE(cluster.getLowBeam(), true);
    QCOMPARE(spy.count(), 1);

    cluster.setLowBeam(false);
    QCOMPARE(cluster.getLowBeam(), false);
    QCOMPARE(spy.count(), 2);
}

void TestInstrumentCluster::testBlinkers()
{
    InstrumentCluster cluster;

    // Test right blinker
    QSignalSpy rightBlinkerSpy(&cluster, &InstrumentCluster::rightBlinkerChanged);
    cluster.setRightBlinker(true);
    QCOMPARE(cluster.getRightBlinker(), true);
    QCOMPARE(rightBlinkerSpy.count(), 1);

    cluster.setRightBlinker(false);
    QCOMPARE(cluster.getRightBlinker(), false);
    QCOMPARE(rightBlinkerSpy.count(), 2);

    // Test left blinker
    QSignalSpy leftBlinkerSpy(&cluster, &InstrumentCluster::leftBlinkerChanged);
    cluster.setLeftBlinker(true);
    QCOMPARE(cluster.getLeftBlinker(), true);
    QCOMPARE(leftBlinkerSpy.count(), 1);

    cluster.setLeftBlinker(false);
    QCOMPARE(cluster.getLeftBlinker(), false);
    QCOMPARE(leftBlinkerSpy.count(), 2);
}

void TestInstrumentCluster::testLights()
{
    InstrumentCluster cluster;

    QSignalSpy frontFogSpy(&cluster, &InstrumentCluster::frontFogLightChanged);
    cluster.setFrontFogLight(true);
    QCOMPARE(cluster.getFrontFogLight(), true);
    QCOMPARE(frontFogSpy.count(), 1);

    cluster.setFrontFogLight(false);
    QCOMPARE(cluster.getFrontFogLight(), false);
    QCOMPARE(frontFogSpy.count(), 2);

    QSignalSpy rearFogSpy(&cluster, &InstrumentCluster::rearFogLightChanged);
    cluster.setRearFogLight(true);
    QCOMPARE(cluster.getRearFogLight(), true);
    QCOMPARE(rearFogSpy.count(), 1);

    cluster.setRearFogLight(false);
    QCOMPARE(cluster.getRearFogLight(), false);
    QCOMPARE(rearFogSpy.count(), 2);

    QSignalSpy hazardSpy(&cluster, &InstrumentCluster::hazardLightChanged);
    cluster.setHazardLight(true);
    QCOMPARE(cluster.getHazardLight(), true);
    QCOMPARE(hazardSpy.count(), 1);

    cluster.setHazardLight(false);
    QCOMPARE(cluster.getHazardLight(), false);
    QCOMPARE(hazardSpy.count(), 2);

    QSignalSpy parkingSpy(&cluster, &InstrumentCluster::parkingLightChanged);
    cluster.setParkingLight(true);
    QCOMPARE(cluster.getParkingLight(), true);
    QCOMPARE(parkingSpy.count(), 1);

    cluster.setParkingLight(false);
    QCOMPARE(cluster.getParkingLight(), false);
    QCOMPARE(parkingSpy.count(), 2);
}

void TestInstrumentCluster::testPercentage()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::percentageChanged);

    cluster.setPercentage(50);
    QCOMPARE(cluster.getPercentage(), 50);
    QCOMPARE(spy.count(), 1);

    cluster.setPercentage(75);
    QCOMPARE(cluster.getPercentage(), 75);
    QCOMPARE(spy.count(), 2);
}

void TestInstrumentCluster::testAutonomy()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::autonomyLevelChanged);

    cluster.setAutonomyLevel(200);
    QCOMPARE(cluster.getAutonomyLevel(), 200);
    QCOMPARE(spy.count(), 1);

    cluster.setAutonomyLevel(300);
    QCOMPARE(cluster.getAutonomyLevel(), 300);
    QCOMPARE(spy.count(), 2);
}

void TestInstrumentCluster::testGear()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::gearChanged);

    cluster.setGear(1);
    QCOMPARE(cluster.getGear(), 1);
    QCOMPARE(spy.count(), 1);

    cluster.setGear(2);
    QCOMPARE(cluster.getGear(), 2);
    QCOMPARE(spy.count(), 2);
}


void TestInstrumentCluster::testSetSignDetected()
{
    // Create a Zenoh session
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    QVERIFY(session != nullptr);

    // Create an InstrumentCluster instance
    InstrumentCluster cluster(session);

    // Test setting different signs
    cluster.setSignDetected(0);  // Set to "20"
    QCOMPARE(cluster.getSignDetected(), 0);

    cluster.setSignDetected(1);  // Set to "30"
    QCOMPARE(cluster.getSignDetected(), 1);

    cluster.setSignDetected(2);  // Set to "40"
    QCOMPARE(cluster.getSignDetected(), 2);

    cluster.setSignDetected(3);  // Set to "50"
    QCOMPARE(cluster.getSignDetected(), 3);

    cluster.setSignDetected(4);  // Set to "60"
    QCOMPARE(cluster.getSignDetected(), 4);

    cluster.setSignDetected(5);  // Set to "70"
    QCOMPARE(cluster.getSignDetected(), 5);

    cluster.setSignDetected(6);  // Set to "80"
    QCOMPARE(cluster.getSignDetected(), 6);

    cluster.setSignDetected(7);  // Set to "90"
    QCOMPARE(cluster.getSignDetected(), 7);

    cluster.setSignDetected(8);  // Set to "100"
    QCOMPARE(cluster.getSignDetected(), 8);

    cluster.setSignDetected(9);  // Set to "120"
    QCOMPARE(cluster.getSignDetected(), 9);

    // Test setting an invalid sign
    cluster.setSignDetected(99);  // Invalid value
    QCOMPARE(cluster.getSignDetected(), 0);  // Falls back to default or error handling
}

void TestInstrumentCluster::testLaneDeparture()
{
    InstrumentCluster cluster;

    QCOMPARE(cluster.getLaneDeparture(), false);

    bool signalEmitted = false;
    QObject::connect(&cluster, &InstrumentCluster::laneDepartureChanged, [&](bool state) {
        signalEmitted = true;
        QCOMPARE(state, true);
    });

    cluster.setLaneDeparture(true);
    QCOMPARE(cluster.getLaneDeparture(), true);
    QVERIFY(signalEmitted);

    signalEmitted = false;

    cluster.setLaneDeparture(false);
    QCOMPARE(cluster.getLaneDeparture(), false); 
    QVERIFY(signalEmitted);

    signalEmitted = false;
    cluster.setLaneDeparture(false);
    QCOMPARE(cluster.getLaneDeparture(), false); 
    QVERIFY(!signalEmitted); 
}

void TestInstrumentCluster::testSubscriptionsIntegration()
{
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    QVERIFY(session != nullptr);

    InstrumentCluster cluster(session);
    cluster.setupSubscriptions();
    QTest::qWait(200); 

    auto publish = [&](const std::string& resource, const std::string& value) {
        std::vector<uint8_t> payload(value.begin(), value.end());
        session->put(resource, payload);
    };

    // Test basic existing topics
    publish("Vehicle/1/Speed", "100");
    QTest::qWait(100);
    QCOMPARE(cluster.getSpeed(), 100);

    publish("Vehicle/1/Body/Lights/Beam/Low", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getLowBeam(), true);

    publish("Vehicle/1/Body/Lights/Beam/High", "0");
    QTest::qWait(100);
    QCOMPARE(cluster.getHighBeam(), false);

    publish("Vehicle/1/Powertrain/TractionBattery/StateOfCharge", "85");
    QTest::qWait(100);
    QCOMPARE(cluster.getPercentage(), 85);

    publish("Vehicle/1/Powertrain/Transmission/CurrentGear", "3");
    QTest::qWait(100);
    QCOMPARE(cluster.getGear(), 3);

    // ✅ New topics to test
    publish("Vehicle/1/Body/Lights/DirectionIndicator/Left", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getLeftBlinker(), true);

    publish("Vehicle/1/Body/Lights/DirectionIndicator/Right", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getRightBlinker(), true);

    publish("Vehicle/1/Body/Lights/Hazard", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getHazardLight(), true);

    publish("Vehicle/1/Body/Lights/Fog/Front", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getFrontFogLight(), true);

    publish("Vehicle/1/Body/Lights/Fog/Rear", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getRearFogLight(), true);

    publish("Vehicle/1/Body/Lights/Parking", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getParkingLight(), true);


    publish("Vehicle/1/Scene/Lanes/Left", R"({"a":1,"b":2,"c":3})");
    QTest::qWait(100);
    {
        QVariantMap expected;
        expected.insert("a", 1);
        expected.insert("b", 2);
        expected.insert("c", 3);
        QCOMPARE(cluster.getLeftLaneCoefs(), expected);
    }

    // Publish right lane data
    publish("Vehicle/1/Scene/Lanes/Right", R"({"a":4,"b":5,"c":6})");
    QTest::qWait(100);
    {
        QVariantMap expected;
        expected.insert("a", 4);
        expected.insert("b", 5);
        expected.insert("c", 6);
        QCOMPARE(cluster.getRightLaneCoefs(), expected);
    }

    // Test lane departure to the left (code 10)
    publish("Vehicle/1/ADAS/LaneDeparture/Detected", "10");
    QTest::qWait(100);
    QCOMPARE(cluster.getLaneDeparture(), 10);
    QCOMPARE(cluster.getWarningCode(), 2);

    // Test lane departure cleared (code 11)
    publish("Vehicle/1/ADAS/LaneDeparture/Detected", "11");
    QTest::qWait(100);
    QCOMPARE(cluster.getLaneDeparture(), 11);
    QCOMPARE(cluster.getWarningCode(), 0);

    // Test lane departure to the right (code 20)
    publish("Vehicle/1/ADAS/LaneDeparture/Detected", "20");
    QTest::qWait(100);
    QCOMPARE(cluster.getLaneDeparture(), 20);
    QCOMPARE(cluster.getWarningCode(), 2);
    
        // 🚦 Test speed limit sign detection via Zenoh
    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "20");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 0);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "30");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 1);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "40");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 2);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "50");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 3);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "60");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 4);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "70");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 5);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "80");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 6);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "90");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 7);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "100");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 8);

    publish("Vehicle/1/Environment/RoadSigns/SpeedLimit", "120");
    QTest::qWait(100);
    QCOMPARE(cluster.getSignDetected(), 9);

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_0", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getAutonomyLevel(), 0);

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getAutonomyLevel(), 1);

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_2", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getAutonomyLevel(), 2);

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5", "1");
    QTest::qWait(100);
    QCOMPARE(cluster.getAutonomyLevel(), 5);

    std::cout << "Testando Obstacle Detection..." << std::endl;
    QSignalSpy warningSpy(&cluster, &InstrumentCluster::warningCodeChanged);
    publish("Vehicle/1/ADAS/ObstacleDetection/Warning", "1");
    QTest::qWait(100);
    std::cout << "Warning code após publicação: " << cluster.getWarningCode() << std::endl;
    QCOMPARE(warningSpy.count(), 1);
    QCOMPARE(cluster.getWarningCode(), 1);
}

void TestInstrumentCluster::testAutonomyLevelFromZenoh()
{
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    InstrumentCluster cluster(session);
    cluster.setupSubscriptions();

    QSignalSpy spy(&cluster, &InstrumentCluster::autonomyLevelChanged);

    auto publish = [&](const std::string& topic, const std::string& value) {
        std::vector<uint8_t> payload(value.begin(), value.end());
        session->put(topic, payload);
        QTest::qWait(200); // allow async delivery
    };

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_0", "1");
    QCOMPARE(cluster.getAutonomyLevel(), 0);

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_1", "1");
    QCOMPARE(cluster.getAutonomyLevel(), 1);

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_2", "1");
    QCOMPARE(cluster.getAutonomyLevel(), 2);

    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/SAE_5", "1");
    QCOMPARE(cluster.getAutonomyLevel(), 5);

    // Optional: validate signal count
    QVERIFY(spy.count() >= 4);
}

void TestInstrumentCluster::testLaneDepartureFromZenoh()
{
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    InstrumentCluster cluster(session);
    cluster.setupSubscriptions();

    QSignalSpy laneSpy(&cluster, &InstrumentCluster::laneDepartureChanged);
    QSignalSpy warningSpy(&cluster, &InstrumentCluster::warningCodeChanged);

    auto publish = [&](const std::string& value) {
        std::vector<uint8_t> payload(value.begin(), value.end());
        session->put("Vehicle/1/ADAS/LaneDeparture/Detected", payload);
        QTest::qWait(200);  // give it time
    };

    // Departure to left
    publish("10");
    QCOMPARE(cluster.getLaneDeparture(), 10);
    QCOMPARE(cluster.getWarningCode(), 2);

    // Departure cleared
    publish("11");
    QCOMPARE(cluster.getLaneDeparture(), 11);
    QCOMPARE(cluster.getWarningCode(), 0);

    // Departure to right
    publish("20");
    QCOMPARE(cluster.getLaneDeparture(), 20);
    QCOMPARE(cluster.getWarningCode(), 2);

    QVERIFY(laneSpy.count() >= 3);
    QVERIFY(warningSpy.count() >= 3);
}


void TestInstrumentCluster::testObstacleWarning()
{
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    InstrumentCluster cluster(session);
    cluster.setupSubscriptions();

    QSignalSpy spy(&cluster, &InstrumentCluster::warningCodeChanged);

    std::vector<uint8_t> payload{'1'};
    session->put("Vehicle/1/ADAS/ObstacleDetection/Warning", payload);

    QTest::qWait(300);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(cluster.getWarningCode(), 1);
}

void TestInstrumentCluster::testAutonomyLevel()
{
    // Create an InstrumentCluster instance
    InstrumentCluster cluster;

    // Set autonomy level to 2
    cluster.setAutonomyLevel(2);
    QCOMPARE(cluster.getAutonomyLevel(), 2); // Verify state is updated

    // Set autonomy level to 5
    cluster.setAutonomyLevel(5);
    QCOMPARE(cluster.getAutonomyLevel(), 5); // Verify state is updated

    // Test setting the same level (signal should not be emitted)
    cluster.setAutonomyLevel(5);
    QCOMPARE(cluster.getAutonomyLevel(), 5); // State remains unchanged
}

void TestInstrumentCluster::testInstrumentClusterConstructor()
{
    // Path to a valid Zenoh configuration file
    const std::string configFile = "../zenoh-config-test-file.json";

    // Ensure the configuration file exists
    QVERIFY(QFile::exists(QString::fromStdString(configFile)));

    // Create an InstrumentCluster instance
    InstrumentCluster cluster(configFile);
    // Verify that the constructor does not throw exceptions
}

void TestInstrumentCluster::testSpeedLimitFromZenoh()
{
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    InstrumentCluster cluster(session);
    cluster.setupSubscriptions();

    QSignalSpy spy(&cluster, &InstrumentCluster::signDetectedChanged);

    auto publish = [&](const std::string& value, int expectedSignId) {
        std::vector<uint8_t> payload(value.begin(), value.end());
        session->put("Vehicle/1/Environment/RoadSigns/SpeedLimit", payload);
        QTest::qWait(200);
        QCOMPARE(cluster.getSignDetected(), expectedSignId);
    };

    publish("20", 0);
    publish("30", 1);
    publish("40", 2);
    publish("50", 3);
    publish("60", 4);
    publish("70", 5);
    publish("80", 6);
    publish("90", 7);
    publish("100", 8);
    publish("120", 9);

}

void TestInstrumentCluster::testCruiseControlFromZenoh()
{
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    QVERIFY(session != nullptr);

    InstrumentCluster cluster(session);
    cluster.setupSubscriptions();
    QTest::qWait(200); // Aguarda setup

    QSignalSpy spy(&cluster, &InstrumentCluster::cruiseControlChanged);

    auto publish = [&](const std::string& topic, const std::string& value) {
        std::vector<uint8_t> payload(value.begin(), value.end());
        session->put(topic, payload);
        QTest::qWait(150);
    };

    // ✅ Testa ativação do cruise control
    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/CruiseControl", "1");
    QCOMPARE(cluster.getCruiseControl(), true);
    QCOMPARE(spy.count(), 1);

    // ✅ Testa desativação do cruise control
    publish("Vehicle/1/ADAS/ActiveAutonomyLevel/CruiseControl", "0");
    QCOMPARE(cluster.getCruiseControl(), false);
    QCOMPARE(spy.count(), 2);
}

// Possibly test cleanup (optional, for destructor coverage)
void TestInstrumentCluster::testClusterDestruction()
{
    std::shared_ptr<zenoh::Session> session;
    {
        auto config = zenoh::Config::create_default();
        session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
        InstrumentCluster cluster(session);
        cluster.setObjectName("InstrumentClusterDestruction");
    }
    QVERIFY(session != nullptr);
    // Destructor should close the session without crashing
}

void TestInstrumentCluster::testTrafficSignsFromZenoh()
{
    auto config = zenoh::Config::create_default();
    auto session = std::make_shared<zenoh::Session>(zenoh::Session::open(std::move(config)));
    InstrumentCluster cluster(session);
    cluster.setupSubscriptions();

    QSignalSpy spy(&cluster, &InstrumentCluster::signDetectedChanged);

    auto publish = [&](const std::string& topic, const std::string& value) {
        std::vector<uint8_t> payload(value.begin(), value.end());
        session->put(topic, payload);
        QTest::qWait(150);
    };

    // Stop sign: emits 0 then 11
    publish("Vehicle/1/Environment/RoadSigns/Stop", "1");
    QCOMPARE(cluster.getSignDetected(), 11);

    // Yield sign: emits 0 then 12
    publish("Vehicle/1/Environment/RoadSigns/Yield", "1");
    QCOMPARE(cluster.getSignDetected(), 12);

    // Pedestrian zone: emits 0 then 13
    publish("Vehicle/1/Environment/RoadSigns/PedestrianZone", "1");
    QCOMPARE(cluster.getSignDetected(), 13);

    // Danger sign: emits 0 then 17
    publish("Vehicle/1/Environment/RoadSigns/DangerSign", "1");
    QCOMPARE(cluster.getSignDetected(), 17);

    // Traffic lights
    publish("Vehicle/1/Environment/RoadSigns/TrafficLight", "yellow");
    QCOMPARE(cluster.getSignDetected(), 14);

    publish("Vehicle/1/Environment/RoadSigns/TrafficLight", "green");
    QCOMPARE(cluster.getSignDetected(), 15);

    publish("Vehicle/1/Environment/RoadSigns/TrafficLight", "red");
    QCOMPARE(cluster.getSignDetected(), 16);

    // Optional: unknown traffic light value should not crash
    publish("Vehicle/1/Environment/RoadSigns/TrafficLight", "blue");
    QCOMPARE(cluster.getSignDetected(), 16); // remains last valid value

    QVERIFY(spy.count() >= 7); // at least one per unique value
}


QTEST_MAIN(TestInstrumentCluster)
