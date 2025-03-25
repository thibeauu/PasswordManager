#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "MasterPasswordManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Buh joh maniga");
    QCoreApplication::setApplicationName("PasswordManager");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MasterPasswordManager manager;
    engine.rootContext()->setContextProperty("passwordManager", &manager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("PasswordManager", "Main");

    return app.exec();
}
