#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../include/InstrumentCluster.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Config config = Config::create_default();
    auto session  = Session::open(std::move(config));

    InstrumentCluster instrumentCluster(session);
    engine.rootContext()->setContextProperty("instrumentCluster",
                                             &instrumentCluster);

    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    auto speed_handler = [&instrumentCluster](const Sample& sample)
    {
        int speed = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub speed: " << speed << std::endl;
        instrumentCluster.setSpeed(speed);
    };

    auto battery_handler = [&instrumentCluster](const Sample& sample)
    {
        int battery = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub battery: " << battery << std::endl;
        instrumentCluster.setBattery(battery);
    };

    auto rightBlinker_handler = [&instrumentCluster](const Sample& sample)
    {
        int rightBlinker = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub rightBlinker: " << rightBlinker << std::endl;
        instrumentCluster.setRightBlinker(rightBlinker);
    };

    auto leftBlinker_handler = [&instrumentCluster](const Sample& sample)
    {
        int leftBlinker = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub leftBlinker: " << leftBlinker << std::endl;
        instrumentCluster.setLeftBlinker(leftBlinker);
    };

    auto lowBeam_handler = [&instrumentCluster](const Sample& sample)
    {
        int lowBeam = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub lowBeam: " << lowBeam << std::endl;
        instrumentCluster.setLowBeam(lowBeam);
    };

    auto highBeam_handler = [&instrumentCluster](const Sample& sample)
    {
        int highBeam = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub highBeam: " << highBeam << std::endl;
        instrumentCluster.setHighBeam(highBeam);
    };

    auto frontFogLight_handler = [&instrumentCluster](const Sample& sample)
    {
        int frontFogLight = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub frontFogLight: " << frontFogLight << std::endl;
        instrumentCluster.setFrontFogLight(frontFogLight);
    };

    auto rearFogLight_handler = [&instrumentCluster](const Sample& sample)
    {
        int rearFogLight = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub rearFogLight: " << rearFogLight << std::endl;
        instrumentCluster.setRearFogLight(rearFogLight);
    };

    auto hazardLight_handler = [&instrumentCluster](const Sample& sample)
    {
        int hazardLight = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub frontFogLight: " << hazardLight << std::endl;
        instrumentCluster.setHazardLight(hazardLight);
    };

    auto parkingLight_handler = [&instrumentCluster](const Sample& sample)
    {
        int parkingLight = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub parkingLight: " << parkingLight << std::endl;
        instrumentCluster.setParkingLight(parkingLight);
    };

    auto gear_handler = [&instrumentCluster](const Sample& sample)
    {
        int gear = std::stoi(sample.get_payload().as_string());
        std::cout << "Sub gear: " << gear << std::endl;
        instrumentCluster.setGear(InstrumentCluster::GearPosition::PARK);
    };

    auto subSpeed = session.declare_subscriber("seame/car/1/speedSensor",
                                               speed_handler, closures::none);

    auto subBattery = session.declare_subscriber(
        "seame/car/1/batterySensor", battery_handler, closures::none);

    auto subRightBlinker = session.declare_subscriber(
        "seame/car/1/rightBlinker", rightBlinker_handler, closures::none);

    auto subLeftBlinker = session.declare_subscriber(
        "seame/car/1/leftBlinker", leftBlinker_handler, closures::none);

    auto subLowBeam = session.declare_subscriber(
        "seame/car/1/lowBeam", lowBeam_handler, closures::none);

    auto subHighBeam = session.declare_subscriber(
        "seame/car/1/highBeam", highBeam_handler, closures::none);

    auto subFrontFogLight = session.declare_subscriber(
        "seame/car/1/frontFogLight", frontFogLight_handler, closures::none);

    auto subRearFogLight = session.declare_subscriber(
        "seame/car/1/rearFogLight", rearFogLight_handler, closures::none);

    auto subHazardLight = session.declare_subscriber(
        "seame/car/1/hazardLight", hazardLight_handler, closures::none);

    auto subParkingLight = session.declare_subscriber(
        "seame/car/1/parkingLight", parkingLight_handler, closures::none);

    auto subGear = session.declare_subscriber("seame/car/1/gear", gear_handler,
                                              closures::none);

    std::cout << "Subs created!" << std::endl;

    return app.exec();
}
