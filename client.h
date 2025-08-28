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
};
