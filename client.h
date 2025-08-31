#pragma once
#include <QString>
#include <QDate>

struct Client {
    int id = 0;
    QString nom;
    QString prenom;
    QString tel;
    QString email;
    QString adr;
    QString statut = "ACTIVE";
    QDate created = QDate::currentDate();
    QString category = "REGULAR";
    int totalOrders = 0;

    // Helper methods
    QString fullName() const { return nom + " " + prenom; }
    bool isValid() const { return !nom.isEmpty() && !prenom.isEmpty(); }
};
