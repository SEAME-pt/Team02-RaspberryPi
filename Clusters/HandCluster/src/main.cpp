#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include <QDebug>
#include "../include/InstrumentCluster.hpp"

using namespace zenoh;

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Font configuration
    int fontId = QFontDatabase::addApplicationFont("/usr/share/fonts/electrolize.ttf");

    if (fontId == -1) {
        qWarning() << "Falha ao carregar a fonte!";
    } else {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty()) {
            qDebug() << "Fonte carregada com sucesso in main:" << fontFamilies.first();
            app.setFont(QFont(fontFamilies.first())); 
        }
    }

    InstrumentCluster* instrumentCluster;
    if (argc == 2) {
        instrumentCluster = new InstrumentCluster(argv[1]);
    } else {
        instrumentCluster = new InstrumentCluster();
    }

    if (instrumentCluster) {
        engine.rootContext()->setContextProperty("instrumentCluster", instrumentCluster);
    } else {
        std::cout << "ERROR" << std::endl;
        qDebug() << "Error: instrumentCluster is NULL!";
    }

    // QML Load
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    engine.load(url);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );

    int result = app.exec();
    delete instrumentCluster;
    return result;
}
