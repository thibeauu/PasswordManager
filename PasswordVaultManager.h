#ifndef PASSWORDVAULTMANAGER_H
#define PASSWORDVAULTMANAGER_H

#include <QObject>
#include <QAbstractListModel>
#include "PasswordEntry.h"

class PasswordVaultManager : public QAbstractListModel {
    Q_OBJECT

public:
    enum PasswordRoles {
        TitleRole = Qt::UserRole + 1,
        UsernameRole,
        PasswordRole,
        UrlRole,
        NotesRole,
        TagsRole,
        CreatedAtRole,
        ModifiedAtRole
    };
    Q_ENUM(PasswordRoles)

    explicit PasswordVaultManager(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadEntries();

private:
    QList<PasswordEntry> entries;

};

#endif // PASSWORDVAULTMANAGER_H
