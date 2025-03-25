#include "MasterPasswordManager.h"
#include <QSettings>

MasterPasswordManager::MasterPasswordManager(QObject* parent) : QObject(parent) {}

bool MasterPasswordManager::hasPassword() const{
    QSettings settings;
    return settings.contains(SETTINGS_KEY);
}

void MasterPasswordManager::savePassword(const QString& password) {
    if(!password.isEmpty() && !hasPassword()){
        QSettings settings;
        settings.setValue(SETTINGS_KEY, password);
        settings.sync();
    }
}

bool MasterPasswordManager::verifyPassword(const QString& input) const{
    QSettings settings;
    return input == settings.value(SETTINGS_KEY).toString();
}

QString MasterPasswordManager::getMasterPassword() const{
    QSettings settings;
    return settings.value(SETTINGS_KEY).toString();
}

void MasterPasswordManager::resetPassword() {
    QSettings settings;
    settings.remove(SETTINGS_KEY);
    settings.sync();
}
