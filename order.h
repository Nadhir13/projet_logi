#pragma once
#include <QString>
#include <QDate>

struct Order {
    int id = 0;
    int clientId = 0;
    QDate date = QDate::currentDate();
    QString etat = "EN_ATTENTE";
    double montant = 0.0;
    QString adrLiv;
    QString priority = "NORMAL";
    QDate estimatedDelivery;
};
