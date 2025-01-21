#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "InstrumentCluster.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    InstrumentCluster instrumentCluster;
    engine.rootContext()->setContextProperty("instrumentCluster",
                                             &instrumentCluster);

    qmlRegisterUncreatableType<GearPosition>(
        "com.example.gearPosition", 1, 0, "GearPosition",
        "Cannot create GearPosition in QML");

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

    return app.exec();
}
