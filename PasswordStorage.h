#ifndef PASSWORDSTORAGE_H
#define PASSWORDSTORAGE_H

#include <QString>
#include <QList>
#include <QByteArray>

#include "PasswordEntry.h"

class PasswordStorage {
public:
    explicit PasswordStorage(const QString& filePath);

    void setMasterPassword(const QString& password);

    bool saveEntries(const QList<PasswordEntry>& entries);
    QList<PasswordEntry> loadEntries();

private:
    QString filePath;
    QByteArray encryptionKey;

    QByteArray encrypt(const QByteArray& plainData);
    QByteArray decrypt(const QByteArray& encryptedData);
};

#endif // PASSWORDSTORAGE_H
