#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "InstrumentCluster.hpp"

using namespace zenoh;

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    InstrumentCluster instrumentCluster;
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

    return app.exec();
}
