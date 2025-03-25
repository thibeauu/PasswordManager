#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "MasterPasswordManager.h"
#include "PasswordVaultManager.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Buh joh maniga");
    QCoreApplication::setApplicationName("PasswordManager");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MasterPasswordManager manager;
    PasswordVaultManager vault;
    engine.rootContext()->setContextProperty("passwordManager", &manager);
    engine.rootContext()->setContextProperty("passwordVault", &vault);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("PasswordManager", "Main");

    return app.exec();
}
