#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QDateTime>
#include <QDebug>
#include <QSettings>
#include <QtCore/QDir>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>
#include <QtWidgets/QApplication>

#include <router.h>
#include <iostream>

int main(int argc, char *argv[])
{



    qDebug() << "start";

    Router router1,router2,router3,router4,router5;

    router1.setTunNumber(11);
    router2.setTunNumber(12);
    router3.setTunNumber(13);
    router4.setTunNumber(14);
    router5.setTunNumber(15);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.rootContext()->setContextProperty("Router1",&router1);
    engine.rootContext()->setContextProperty("Router2",&router2);
    engine.rootContext()->setContextProperty("Router3",&router3);
    engine.rootContext()->setContextProperty("Router4",&router4);
    engine.rootContext()->setContextProperty("Router5",&router5);

    engine.load(url);




    return app.exec();
}
