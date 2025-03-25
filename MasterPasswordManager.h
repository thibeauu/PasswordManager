#ifndef MASTERPASSWORDMANAGER_H
#define MASTERPASSWORDMANAGER_H

#include <QObject>
#include <QString>

class MasterPasswordManager : public QObject {
    Q_OBJECT

public:
    explicit MasterPasswordManager(QObject* parent = nullptr);

    Q_INVOKABLE bool hasPassword() const;
    Q_INVOKABLE void savePassword(const QString& password);
    Q_INVOKABLE bool verifyPassword(const QString& input) const;
    Q_INVOKABLE QString getMasterPassword() const;
    Q_INVOKABLE void resetPassword();

private:
    const QString SETTINGS_KEY = "master_password";
};


#endif // MASTERPASSWORDMANAGER_H
