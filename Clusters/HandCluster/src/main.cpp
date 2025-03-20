#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../include/InstrumentCluster.hpp"

using namespace zenoh;

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    InstrumentCluster* instrumentCluster;
    if (argc == 2)
    {
        instrumentCluster = new InstrumentCluster(argv[1]);
    }
    else
    {
        instrumentCluster = new InstrumentCluster();
    }
    
   if (instrumentCluster) {
    engine.rootContext()->setContextProperty("instrumentCluster", instrumentCluster);
    } else {
        std::cout << "ERROR" << std::endl;
        qDebug() << "Error: instrumentCluster is NULL!";
    }
                                
    const QUrl url(QStringLiteral("/home/lpicoli-/Documents/Team02-Course/RaspberryPi/Clusters/HandCluster/ui/Main.qml"));
    engine.load(url);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    int result = app.exec();
    delete instrumentCluster;
    return result;

    
}
