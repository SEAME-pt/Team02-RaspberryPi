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
    engine.rootContext()->setContextProperty("instrumentCluster", &instrumentCluster);

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

    auto subSpeed   = session.declare_subscriber("seame/car/1/speedSensor",
                                                 speed_handler, closures::none);
    auto subBattery = session.declare_subscriber(
        "seame/car/1/batterySensor", battery_handler, closures::none);
    std::cout << "Subs created!" << std::endl;

    return app.exec();
}
