#pragma once
#include <QVector>
#include <optional>
#include <QSqlDatabase>
#include "user.h"

class UserDao {
public:
    UserDao();

    bool add(const User& u);
    bool update(const User& u);
    bool updateWithoutPassword(int userId, const QString& username, const QString& role, const QString& status);
    bool updatePassword(int userId, const QString& password);
    bool remove(int id);
    std::optional<User> getById(int id);
    std::optional<User> getByUsername(const QString& username);
    QVector<User> getAll();

    // Search and business functions
    QVector<User> search(const QString& usernameFilter = "",
                         const QString& roleFilter = "",
                         const QString& statusFilter = "");
    QVector<QPair<QString, int>> getUsersByRole() const;
    bool usernameExists(const QString& username) const;

private:
    QSqlDatabase m_db;
};
