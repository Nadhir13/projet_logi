#include "db.h"
#include <QSqlDatabase>
#include <QSqlError>

Db& Db::instance() {
    static Db i;
    return i;
}

bool Db::open(const QString& host, int port, const QString& sid,
              const QString& user, const QString& pass) {
    if (!QSqlDatabase::contains("oracle_conn")) {
        m_db = QSqlDatabase::addDatabase("QOCI", "oracle_conn");
    } else {
        m_db = QSqlDatabase::database("oracle_conn");
    }
    m_db.setHostName(host);
    m_db.setPort(port);
    m_db.setDatabaseName(sid); // XE
    m_db.setUserName(user);
    m_db.setPassword(pass);
    if (!m_db.open()) {
        m_lastErr = m_db.lastError().text();
        return false;
    }
    return true;
}
