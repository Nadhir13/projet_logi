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

    // Helper methods
    bool isValid() const { return clientId > 0 && montant > 0 && !adrLiv.isEmpty(); }
    QString statusText() const {
        if (etat == "EN_ATTENTE") return "En attente";
        if (etat == "EN_COURS") return "En cours";
        if (etat == "LIVREE") return "Livrée";
        if (etat == "ANNULEE") return "Annulée";
        return etat;
    }
};
