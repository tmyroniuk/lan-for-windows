#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "transmissionmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<TransmissionManager>("SocketQML.transmissionmanager", 1, 0, "TrManager");

    engine.load(QStringLiteral("qrc:/main.qml"));
    if (engine.rootObjects().empty())
        return -1;

    return app.exec();
}
