#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore/QObject>
#include <QQmlContext> 
#include <QtSerialBus/QCanBus>
#include "../include/CANBusHandler.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Set up the QML engine
    QQmlApplicationEngine engine;

    qmlRegisterType<CANBusHandler>("com.example.canbus", 1, 0, "CANBusHandler");
    // Create and expose the CAN bus handler to QML
    CANBusHandler canBusHandler;
    engine.rootContext()->setContextProperty("canBusHandler", &canBusHandler);

    // Load QML file
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
