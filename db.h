#pragma once
#include <QSqlDatabase>
#include <QString>

class Db {
public:
    static Db& instance();

    bool open(const QString& host, int port, const QString& sid,
              const QString& user, const QString& pass);
    QSqlDatabase conn() const { return m_db; }
    QString lastError() const { return m_lastErr; }

private:
    Db() = default;
    Db(const Db&) = delete;
    Db& operator=(const Db&) = delete;

    QSqlDatabase m_db;
    QString m_lastErr;
};
