#pragma once
#include <QString>
#include <QDate>

struct User {
    int id = 0;
    QString username;
    QString password;
    QString role;
    QString status = "ACTIVE";
    QDate created = QDate::currentDate();

    // Helper methods
    bool isValid() const { return !username.isEmpty() && !password.isEmpty() && !role.isEmpty(); }
    QString roleText() const {
        if (role == "ADMIN") return "Administrateur";
        if (role == "MANAGER") return "Gestionnaire";
        if (role == "DELIVERY") return "Livreur";
        return role;
    }
    QString statusText() const {
        if (status == "ACTIVE") return "Actif";
        if (status == "SUSPENDED") return "Suspendu";
        return status;
    }
};
