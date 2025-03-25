#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <QString>
#include <QDateTime>
#include <QStringList>

class PasswordEntry{
public:
    PasswordEntry();
    PasswordEntry(const QString& title,
                  const QString& username,
                  const QString& password,
                  const QString& url = "",
                  const QString& notes = "",
                  const QStringList& tags = {},
                  const QDateTime& createdAt = QDateTime::currentDateTime(),
                  const QDateTime& modifiedAt = QDateTime::currentDateTime());
    QString title;
    QString username;
    QString password;
    QString url;
    QString notes;
    QStringList tags;
    QDateTime createdAt;
    QDateTime modifiedAt;
};



#endif // PASSWORDENTRY_H


