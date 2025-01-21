#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../include/InstrumentCluster.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<InstrumentCluster>("com.example", 1, 0,
                                       "InstrumentCluster");
    engine.addImportPath("qrc:/LightInfo.qml");
    engine.addImportPath("qrc:/FootbarInfo.qml");
    engine.addImportPath("qrc:/TurnSignalLeft.qml");
    engine.addImportPath("qrc:/TurnSignalRight.qml");
    engine.addImportPath("qrc:/GearShiftInfo.qml");

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
