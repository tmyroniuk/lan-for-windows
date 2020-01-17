#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "transmissionmanager.h"
#include "peerlist.h"
#include "peermodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    qmlRegisterType<TransmissionManager>("TrManager", 1, 0, "TrManager");
    qmlRegisterType<PeerModel>("PeerModel", 1, 0, "PeerModel");
    qmlRegisterUncreatableType<PeerList>("PeerList", 1, 0, "PeerList", "Backend type");

    PeerList list;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("peerList", &list);
    engine.load(QStringLiteral("qrc:/main.qml"));
    if (engine.rootObjects().empty())
        return -1;

    return app.exec();
}
