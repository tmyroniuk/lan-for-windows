#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "peermanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<PeerManager>("SocketQML.peermanager", 1, 0, "PeerManager");

    engine.load(QStringLiteral("qrc:/main.qml"));
    if (engine.rootObjects().empty())
        return -1;

    return app.exec();
}
