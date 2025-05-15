#include "InstrumentClusterTest.hpp"
#include "../include/InstrumentCluster.hpp"

#include <QFontDatabase>
#include <QSignalSpy>
#include <QTest>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

// Teste de carregamento da fonte
void TestInstrumentCluster::testFontLoading()
{
    int fontId = QFontDatabase::addApplicationFont("/usr/share/fonts/electrolize.ttf");
    QVERIFY(fontId != -1);
}

// Teste de inicialização do InstrumentCluster
void TestInstrumentCluster::testInstrumentClusterInitialization()
{
    InstrumentCluster cluster;
    cluster.setObjectName("InstrumentCluster");  // Necessário se testado diretamente
    QVERIFY(!cluster.objectName().isEmpty());
}

// Teste do setter de velocidade
void TestInstrumentCluster::testSetSpeed()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::speedChanged);

    cluster.setSpeed(80);
    QCOMPARE(cluster.getSpeed(), 80);
    QCOMPARE(spy.count(), 1);

    // Não deve emitir novamente se o valor não mudar
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


// Teste de warning code
void TestInstrumentCluster::testSetWarningCode()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::warningCodeChanged);

    cluster.setWarningCode(3);
    QCOMPARE(cluster.getWarningCode(), 3);
    QCOMPARE(spy.count(), 1);
}

// Teste de sinal de farol alto
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

    // Test front fog light
    QSignalSpy frontFogSpy(&cluster, &InstrumentCluster::frontFogLightChanged);
    cluster.setFrontFogLight(true);
    QCOMPARE(cluster.getFrontFogLight(), true);
    QCOMPARE(frontFogSpy.count(), 1);

    cluster.setFrontFogLight(false);
    QCOMPARE(cluster.getFrontFogLight(), false);
    QCOMPARE(frontFogSpy.count(), 2);

    // Test rear fog light
    QSignalSpy rearFogSpy(&cluster, &InstrumentCluster::rearFogLightChanged);
    cluster.setRearFogLight(true);
    QCOMPARE(cluster.getRearFogLight(), true);
    QCOMPARE(rearFogSpy.count(), 1);

    cluster.setRearFogLight(false);
    QCOMPARE(cluster.getRearFogLight(), false);
    QCOMPARE(rearFogSpy.count(), 2);

    // Test hazard light
    QSignalSpy hazardSpy(&cluster, &InstrumentCluster::hazardLightChanged);
    cluster.setHazardLight(true);
    QCOMPARE(cluster.getHazardLight(), true);
    QCOMPARE(hazardSpy.count(), 1);

    cluster.setHazardLight(false);
    QCOMPARE(cluster.getHazardLight(), false);
    QCOMPARE(hazardSpy.count(), 2);

    // Test parking light
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
    QSignalSpy spy(&cluster, &InstrumentCluster::autonomyChanged);

    cluster.setAutonomy(200);
    QCOMPARE(cluster.getAutonomy(), 200);
    QCOMPARE(spy.count(), 1);

    cluster.setAutonomy(300);
    QCOMPARE(cluster.getAutonomy(), 300);
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

void TestInstrumentCluster::testGetDetectedObjects()
{
    InstrumentCluster cluster;

    // Simulate detected objects
    QVariantList detectedObjects;
    detectedObjects.append(QVariantMap{{"id", 1}, {"type", "car"}, {"distance", 10.5}});
    detectedObjects.append(QVariantMap{{"id", 2}, {"type", "pedestrian"}, {"distance", 5.2}});

    // Assuming there is a method to set detected objects
    cluster.setDetectedObjects(detectedObjects);

    // Verify that getDetectedObjects() returns the correct list
    QCOMPARE(cluster.getDetectedObjects(), detectedObjects);
}


void TestInstrumentCluster::testSetDetectedObjects()
{
    InstrumentCluster cluster;
    QSignalSpy spy(&cluster, &InstrumentCluster::detectedObjectsUpdated);

    QVariantMap obj;
    obj["x"] = 1.0;
    obj["y"] = 2.0;
    obj["width"] = 3.0;
    obj["height"] = 4.0;
    obj["type"] = "car";

    QVariantList list;
    list << obj;

    cluster.setDetectedObjects(list);
    QCOMPARE(spy.count(), 1);

    // Repetir o mesmo valor não deve emitir novamente
    cluster.setDetectedObjects(list);
    QCOMPARE(spy.count(), 1);
}

void TestInstrumentCluster::testParseObjectData()
{
    InstrumentCluster cluster;

    // Simulate JSON input
    std::string objectData = R"([
        {"x": 10.5, "y": 20.5, "width": 5.0, "height": 10.0, "type": "car"},
        {"x": 15.0, "y": 25.0, "width": 6.0, "height": 12.0, "type": "pedestrian"}
    ])";

    // Call the function
    cluster.parseObjectData(objectData);

    // Expected detected objects
    QVariantList expectedObjects;
    expectedObjects.append(QVariantMap{
        {"x", 10.5},
        {"y", 20.5},
        {"width", 5.0},
        {"height", 10.0},
        {"type", "car"}
    });
    expectedObjects.append(QVariantMap{
        {"x", 15.0},
        {"y", 25.0},
        {"width", 6.0},
        {"height", 12.0},
        {"type", "pedestrian"}
    });

    // Verify that the detected objects were set correctly
    QCOMPARE(cluster.getDetectedObjects(), expectedObjects);
}

void TestInstrumentCluster::testParseObjectData_InvalidJson()
{
    InstrumentCluster cluster;

    // Simulate invalid JSON input
    std::string invalidJson = "{invalid json}";

    // Call the function
    QSignalSpy spy(&cluster, &InstrumentCluster::detectedObjectsUpdated);
    cluster.parseObjectData(invalidJson);

    // Verify that no objects were detected and no signal was emitted
    QCOMPARE(cluster.getDetectedObjects().size(), 0);
    QCOMPARE(spy.count(), 0);
}

void TestInstrumentCluster::testParseObjectData_NonArrayJson()
{
    InstrumentCluster cluster("/home/lpicoli-/Documents/Team02-Course/RaspberryPi/deployLocal/zenoh-test.conf");

    // Simulate non-array JSON input
    std::string nonArrayJson = R"({"key": "value"})";

    // Call the function
    QSignalSpy spy(&cluster, &InstrumentCluster::detectedObjectsUpdated);
    cluster.parseObjectData(nonArrayJson);

    // Verify that no objects were detected and no signal was emitted
    QCOMPARE(cluster.getDetectedObjects().size(), 0);
    QCOMPARE(spy.count(), 0);
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

    // Publish detected objects (array of objects)
    publish("Vehicle/1/Scene/Objects", R"([{"id":1},{"id":2}])");
    QTest::qWait(100);
    QCOMPARE(cluster.getDetectedObjects().size(), 2);

    // Publish warning code
    publish("Vehicle/1/Scene/Warning", "7");
    QTest::qWait(100);
    QCOMPARE(cluster.getWarningCode(), 7);

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

}


QTEST_MAIN(TestInstrumentCluster)
