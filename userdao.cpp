#include "userdao.h"
#include "db.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

UserDao::UserDao() {
    m_db = Db::instance().conn();
}

bool UserDao::add(const User& u) {
    QSqlQuery q(m_db);
    q.prepare(R"(INSERT INTO USERS (USERNAME, PASSWORD, ROLE, STATUS, DATE_CREATION)
                 VALUES (:user, :pass, :role, :status, SYSDATE))");
    q.bindValue(":user", u.username);
    q.bindValue(":pass", u.password);
    q.bindValue(":role", u.role);
    q.bindValue(":status", u.status);

    bool success = q.exec();
    if (!success) {
        qDebug() << "UserDao::add error:" << q.lastError().text();
    }
    return success;
}

bool UserDao::update(const User& u) {
    QSqlQuery q(m_db);
    q.prepare(R"(UPDATE USERS SET USERNAME=:user, PASSWORD=:pass, ROLE=:role, STATUS=:status
                 WHERE ID_USER=:id)");
    q.bindValue(":user", u.username);
    q.bindValue(":pass", u.password);
    q.bindValue(":role", u.role);
    q.bindValue(":status", u.status);
    q.bindValue(":id", u.id);

    bool success = q.exec();
    if (!success) {
        qDebug() << "UserDao::update error:" << q.lastError().text();
    }
    return success;
}

bool UserDao::updateWithoutPassword(int userId, const QString& username, const QString& role, const QString& status) {
    QSqlQuery q(m_db);
    q.prepare("UPDATE USERS SET USERNAME=:user, ROLE=:role, STATUS=:status WHERE ID_USER=:id");
    q.bindValue(":user", username);
    q.bindValue(":role", role);
    q.bindValue(":status", status);
    q.bindValue(":id", userId);

    bool success = q.exec();
    if (!success) {
        qDebug() << "UserDao::updateWithoutPassword error:" << q.lastError().text();
    }
    return success;
}

bool UserDao::updatePassword(int userId, const QString& password) {
    QSqlQuery q(m_db);
    q.prepare("UPDATE USERS SET PASSWORD=:pass WHERE ID_USER=:id");
    q.bindValue(":pass", password);
    q.bindValue(":id", userId);

    bool success = q.exec();
    if (!success) {
        qDebug() << "UserDao::updatePassword error:" << q.lastError().text();
    }
    return success;
}

bool UserDao::remove(int id) {
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM USERS WHERE ID_USER=:id");
    q.bindValue(":id", id);

    bool success = q.exec();
    if (!success) {
        qDebug() << "UserDao::remove error:" << q.lastError().text();
    }
    return success;
}

std::optional<User> UserDao::getById(int id) {
    QSqlQuery q(m_db);
    q.prepare("SELECT ID_USER, USERNAME, PASSWORD, ROLE, STATUS, DATE_CREATION FROM USERS WHERE ID_USER=:id");
    q.bindValue(":id", id);

    if (q.exec() && q.next()) {
        User u;
        u.id = q.value(0).toInt();
        u.username = q.value(1).toString();
        u.password = q.value(2).toString();
        u.role = q.value(3).toString();
        u.status = q.value(4).toString();
        u.created = q.value(5).toDate();
        return u;
    }

    qDebug() << "UserDao::getById error:" << q.lastError().text();
    return std::nullopt;
}

std::optional<User> UserDao::getByUsername(const QString& username) {
    QSqlQuery q(m_db);
    q.prepare("SELECT ID_USER, USERNAME, PASSWORD, ROLE, STATUS, DATE_CREATION FROM USERS WHERE USERNAME=:user");
    q.bindValue(":user", username);

    if (q.exec() && q.next()) {
        User u;
        u.id = q.value(0).toInt();
        u.username = q.value(1).toString();
        u.password = q.value(2).toString();
        u.role = q.value(3).toString();
        u.status = q.value(4).toString();
        u.created = q.value(5).toDate();
        return u;
    }

    qDebug() << "UserDao::getByUsername error:" << q.lastError().text();
    return std::nullopt;
}

QVector<User> UserDao::getAll() {
    QVector<User> users;
    QSqlQuery q("SELECT ID_USER, USERNAME, PASSWORD, ROLE, STATUS, DATE_CREATION FROM USERS ORDER BY USERNAME", m_db);

    if (q.exec()) {
        while (q.next()) {
            User u;
            u.id = q.value(0).toInt();
            u.username = q.value(1).toString();
            u.password = q.value(2).toString();
            u.role = q.value(3).toString();
            u.status = q.value(4).toString();
            u.created = q.value(5).toDate();
            users.append(u);
        }
    } else {
        qDebug() << "UserDao::getAll error:" << q.lastError().text();
    }

    return users;
}

QVector<User> UserDao::search(const QString& usernameFilter, const QString& roleFilter, const QString& statusFilter) {
    QVector<User> users;
    QString queryStr = "SELECT ID_USER, USERNAME, PASSWORD, ROLE, STATUS, DATE_CREATION FROM USERS WHERE 1=1";

    if (!usernameFilter.isEmpty()) {
        queryStr += " AND USERNAME LIKE :user";
    }
    if (!roleFilter.isEmpty() && roleFilter != "Tous les rôles") {
        queryStr += " AND ROLE = :role";
    }
    if (!statusFilter.isEmpty() && statusFilter != "Tous les statuts") {
        queryStr += " AND STATUS = :status";
    }

    queryStr += " ORDER BY USERNAME";

    QSqlQuery q(m_db);
    q.prepare(queryStr);

    if (!usernameFilter.isEmpty()) {
        q.bindValue(":user", "%" + usernameFilter + "%");
    }
    if (!roleFilter.isEmpty() && roleFilter != "Tous les rôles") {
        q.bindValue(":role", roleFilter);
    }
    if (!statusFilter.isEmpty() && statusFilter != "Tous les statuts") {
        q.bindValue(":status", statusFilter);
    }

    if (q.exec()) {
        while (q.next()) {
            User u;
            u.id = q.value(0).toInt();
            u.username = q.value(1).toString();
            u.password = q.value(2).toString();
            u.role = q.value(3).toString();
            u.status = q.value(4).toString();
            u.created = q.value(5).toDate();
            users.append(u);
        }
    } else {
        qDebug() << "UserDao::search error:" << q.lastError().text();
    }

    return users;
}

QVector<QPair<QString, int>> UserDao::getUsersByRole() const {
    QVector<QPair<QString, int>> result;
    QSqlQuery q("SELECT ROLE, COUNT(*) FROM USERS GROUP BY ROLE", m_db);

    if (q.exec()) {
        while (q.next()) {
            result.append(qMakePair(q.value(0).toString(), q.value(1).toInt()));
        }
    } else {
        qDebug() << "UserDao::getUsersByRole error:" << q.lastError().text();
    }

    return result;
}

bool UserDao::usernameExists(const QString& username) const {
    QSqlQuery q(m_db);
    q.prepare("SELECT COUNT(*) FROM USERS WHERE USERNAME = :user");
    q.bindValue(":user", username);

    if (q.exec() && q.next()) {
        return q.value(0).toInt() > 0;
    }

    qDebug() << "UserDao::usernameExists error:" << q.lastError().text();
    return false;
}
