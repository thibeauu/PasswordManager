#include "PasswordVaultManager.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QClipboard>
#include <QGuiApplication>
#include <QRandomGenerator>

PasswordVaultManager::PasswordVaultManager(QObject* parent): QAbstractListModel(parent){
    loadEntries();
}

int PasswordVaultManager::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return entries.size();
}

QVariant PasswordVaultManager::data(const QModelIndex& index, int role) const {
    if(!index.isValid() || index.row() < 0 || index.row() >= entries.size()){
        return QVariant();
    }

    const PasswordEntry& entry = entries.at(index.row());

    switch (role) {
    case TitleRole:
        return entry.title;
    case UsernameRole:
        return entry.username;
    case PasswordRole:
        return entry.password;
    case UrlRole:
        return entry.url;
    case NotesRole:
        return entry.notes;
    case TagsRole:
        return entry.tags;
    case CreatedAtRole:
        return entry.createdAt.toString(Qt::ISODate);
    case ModifiedAtRole:
        return entry.modifiedAt.toString(Qt::ISODate);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PasswordVaultManager::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[UsernameRole] = "username";
    roles[PasswordRole] = "password";
    roles[UrlRole] = "url";
    roles[NotesRole] = "notes";
    roles[TagsRole] = "tags";
    roles[CreatedAtRole] = "createdAt";
    roles[ModifiedAtRole] = "modifiedAt";
    return roles;
}

void PasswordVaultManager::loadEntries() {
    beginResetModel();
    entries.clear();

    QFile file("passwords.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray array = doc.array();

        for (const QJsonValue& val : array) {
            QJsonObject obj = val.toObject();
            entries.append(PasswordEntry(
                obj["title"].toString(),
                obj["username"].toString(),
                obj["password"].toString(),
                obj["url"].toString(),
                obj["notes"].toString(),
                obj["tags"].toVariant().toStringList(),
                QDateTime::fromString(obj["createdAt"].toString(), Qt::ISODate),
                QDateTime::fromString(obj["modifiedAt"].toString(), Qt::ISODate)
                ));
        }
    }

    endResetModel();
}


void PasswordVaultManager::addEntry(const QString& title,
                                    const QString& username,
                                    const QString& password,
                                    const QString& url)
{
    beginInsertRows(QModelIndex(), entries.size(), entries.size());
    entries.append(PasswordEntry(title, username, password, url, "", {}, QDateTime::currentDateTime(), QDateTime::currentDateTime()));
    endInsertRows();
    saveEntries();
}

void PasswordVaultManager::saveEntries() {
    QJsonArray entryArray;

    for (const PasswordEntry& entry : entries) {
        QJsonObject obj;
        obj["title"] = entry.title;
        obj["username"] = entry.username;
        obj["password"] = entry.password;
        obj["url"] = entry.url;
        obj["notes"] = entry.notes;
        obj["tags"] = QJsonArray::fromStringList(entry.tags);
        obj["createdAt"] = entry.createdAt.toString(Qt::ISODate);
        obj["modifiedAt"] = entry.modifiedAt.toString(Qt::ISODate);
        entryArray.append(obj);
    }

    QJsonDocument doc(entryArray);
    QFile file("passwords.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void PasswordVaultManager::copyToClipboard(const QString &text){
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}

void PasswordVaultManager::removeEntry(const int index) {
    if (index < 0 || index >= entries.size()) {
        qWarning("Invalid index passed to removeEntry: %d", index);
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    entries.removeAt(index);
    endRemoveRows();

    saveEntries();
}

void PasswordVaultManager::updateEntry(int index,
                                       const QString &title,
                                       const QString &username,
                                       const QString &password,
                                       const QString &url)
{
    if (index < 0 || index >= entries.size()) {
        qWarning("Invalid index in updateEntry: %d", index);
        return;
    }

    PasswordEntry &entry = entries[index];
    entry.title = title;
    entry.username = username;
    entry.password = password;
    entry.url = url;
    entry.modifiedAt = QDateTime::currentDateTime();

    QModelIndex changedIndex = this->index(index);
    emit dataChanged(changedIndex, changedIndex);

    saveEntries();
}

QString PasswordVaultManager::generateRandomPassword() {
    int length = QRandomGenerator::global()->bounded(12, 29);

    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}";
    QString password;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        password.append(chars.at(index));
    }
    return password;
}

