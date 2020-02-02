#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "transmissionmanager.h"
#include "peermodel.h"
#include "transmissionmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Universal");

    qRegisterMetaType<QHostAddress>();

    qmlRegisterType<PeerModel>("NetApp", 1, 0, "PeerModel");
    qmlRegisterType<TransmissionModel>("NetApp", 1, 0, "TransmissionModel");
    qmlRegisterUncreatableType<Peer>("NetApp", 1, 0, "Peer", "Backend type");
    qmlRegisterUncreatableType<TransmissionManager>("NetApp", 1, 0, "TrManager", "Main backend type");

    TransmissionManager manager;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("trManager"), &manager);
    engine.load(QStringLiteral("qrc:/main.qml"));
    if (engine.rootObjects().empty())
        return -1;
    return app.exec();
}
