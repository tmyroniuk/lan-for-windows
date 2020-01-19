#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "transmissionmanager.h"
#include "peerlist.h"
#include "peermodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Universal");

    qmlRegisterType<PeerModel>("NetApp", 1, 0, "PeerModel");
    qmlRegisterUncreatableType<PeerList>("NetApp", 1, 0, "PeerList", "Backend type");


    PeerList list;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("peerList"), &list);
    engine.load(QStringLiteral("qrc:/main.qml"));
    if (engine.rootObjects().empty())
        return -1;
    return app.exec();
}
