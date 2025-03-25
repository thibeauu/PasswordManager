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
    Q_INVOKABLE void addEntry(const QString& title, const QString& username, const QString& password, const QString& url);
    Q_INVOKABLE void copyToClipboard(const QString &text);
    Q_INVOKABLE void removeEntry(int index);
    Q_INVOKABLE void updateEntry(int index, const QString &title, const QString &username, const QString &password, const QString &url);

private:
    QList<PasswordEntry> entries;
    void saveEntries();

};

#endif // PASSWORDVAULTMANAGER_H
