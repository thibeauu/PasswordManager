#include "PasswordEntry.h"

PasswordEntry::PasswordEntry() {}

PasswordEntry::PasswordEntry(const QString& title,
                             const QString& username,
                             const QString& password,
                             const QString& url,
                             const QString& notes,
                             const QStringList& tags,
                             const QDateTime& createdAt,
                             const QDateTime& modifiedAt)
    : title(title),
    username(username),
    password(password),
    url(url),
    notes(notes),
    tags(tags),
    createdAt(createdAt),
    modifiedAt(modifiedAt)
{}

