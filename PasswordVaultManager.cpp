#include "PasswordVaultManager.h"

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

    entries.append(PasswordEntry(
        "Gmail",
        "mijn.email@gmail.com",
        "wachtwoord123",
        "https://mail.google.com",
        "Persoonlijk account",
        QStringList{"email", "persoonlijk"},
        QDateTime::currentDateTime(),
        QDateTime::currentDateTime()
        ));

    endResetModel();
}
