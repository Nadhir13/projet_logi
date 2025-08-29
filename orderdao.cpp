#include "orderdao.h"
#include "db.h"
#include <QSqlQuery>
#include <QSqlError>

bool OrderDao::add(const Order& o) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(INSERT INTO COMMANDE (ID_CLIENT, ETAT, MONTANT, ADRESSE_LIVRAISON, PRIORITY, ESTIMATED_DELIVERY)
                 VALUES (:c,:e,:m,:a,:p,:ed))");
    q.bindValue(":c", o.clientId);
    q.bindValue(":e", o.etat);
    q.bindValue(":m", o.montant);
    q.bindValue(":a", o.adrLiv);
    q.bindValue(":p", o.priority);
    q.bindValue(":ed", o.estimatedDelivery);
    return q.exec();
}

bool OrderDao::upd(const Order& o) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(UPDATE COMMANDE SET ID_CLIENT=:c, ETAT=:e, MONTANT=:m, ADRESSE_LIVRAISON=:a, PRIORITY=:p, ESTIMATED_DELIVERY=:ed
                 WHERE ID_COMMANDE=:id)");
    q.bindValue(":c", o.clientId);
    q.bindValue(":e", o.etat);
    q.bindValue(":m", o.montant);
    q.bindValue(":a", o.adrLiv);
    q.bindValue(":p", o.priority);
    q.bindValue(":ed", o.estimatedDelivery);
    q.bindValue(":id", o.id);
    return q.exec();
}

bool OrderDao::del(int id) {
    QSqlQuery q(Db::instance().conn());
    q.prepare("DELETE FROM COMMANDE WHERE ID_COMMANDE=:id");
    q.bindValue(":id", id);
    return q.exec();
}

std::optional<Order> OrderDao::byId(int id) {
    QSqlQuery q(Db::instance().conn());
    q.prepare("SELECT ID_COMMANDE,ID_CLIENT,DATE_COMMANDE,ETAT,MONTANT,ADRESSE_LIVRAISON,PRIORITY,ESTIMATED_DELIVERY FROM COMMANDE WHERE ID_COMMANDE=:id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        Order o;
        o.id      = q.value(0).toInt();
        o.clientId= q.value(1).toInt();
        o.date    = q.value(2).toDate();
        o.etat    = q.value(3).toString();
        o.montant = q.value(4).toDouble();
        o.adrLiv  = q.value(5).toString();
        o.priority = q.value(6).toString();
        o.estimatedDelivery = q.value(7).toDate();
        return o;
    }
    return std::nullopt;
}

QVector<Order> OrderDao::all() {
    QVector<Order> v;
    QSqlQuery q("SELECT ID_COMMANDE,ID_CLIENT,DATE_COMMANDE,ETAT,MONTANT,ADRESSE_LIVRAISON,PRIORITY,ESTIMATED_DELIVERY FROM COMMANDE ORDER BY ID_COMMANDE DESC", Db::instance().conn());
    if (q.exec()) {
        while (q.next()) {
            Order o;
            o.id      = q.value(0).toInt();
            o.clientId= q.value(1).toInt();
            o.date    = q.value(2).toDate();
            o.etat    = q.value(3).toString();
            o.montant = q.value(4).toDouble();
            o.adrLiv  = q.value(5).toString();
            o.priority = q.value(6).toString();
            o.estimatedDelivery = q.value(7).toDate();
            v.push_back(o);
        }
    }
    return v;
}

QVector<Order> OrderDao::search(int clientId,
                                const QString& statusFilter,
                                double minAmount,
                                double maxAmount) {
    QVector<Order> v;
    QString queryStr = "SELECT ID_COMMANDE,ID_CLIENT,DATE_COMMANDE,ETAT,MONTANT,ADRESSE_LIVRAISON,PRIORITY,ESTIMATED_DELIVERY FROM COMMANDE WHERE 1=1";

    if (clientId > 0) {
        queryStr += " AND ID_CLIENT = :clientId";
    }
    if (!statusFilter.isEmpty() && statusFilter != "Tous") {
        queryStr += " AND ETAT = :status";
    }
    if (minAmount >= 0) {
        queryStr += " AND MONTANT >= :minAmount";
    }
    if (maxAmount >= 0) {
        queryStr += " AND MONTANT <= :maxAmount";
    }

    queryStr += " ORDER BY ID_COMMANDE DESC";

    QSqlQuery q(Db::instance().conn());
    q.prepare(queryStr);

    if (clientId > 0) {
        q.bindValue(":clientId", clientId);
    }
    if (!statusFilter.isEmpty() && statusFilter != "Tous") {
        q.bindValue(":status", statusFilter);
    }
    if (minAmount >= 0) {
        q.bindValue(":minAmount", minAmount);
    }
    if (maxAmount >= 0) {
        q.bindValue(":maxAmount", maxAmount);
    }

    if (q.exec()) {
        while (q.next()) {
            Order o;
            o.id      = q.value(0).toInt();
            o.clientId= q.value(1).toInt();
            o.date    = q.value(2).toDate();
            o.etat    = q.value(3).toString();
            o.montant = q.value(4).toDouble();
            o.adrLiv  = q.value(5).toString();
            o.priority = q.value(6).toString();
            o.estimatedDelivery = q.value(7).toDate();
            v.push_back(o);
        }
    }
    return v;
}

double OrderDao::getTotalRevenue() const {
    QSqlQuery q("SELECT SUM(MONTANT) FROM COMMANDE WHERE ETAT = 'LIVREE'", Db::instance().conn());
    if (q.exec() && q.next()) {
        return q.value(0).toDouble();
    }
    return 0.0;
}

QVector<QPair<QString, int>> OrderDao::getOrdersByStatus() const {
    QVector<QPair<QString, int>> result;
    QSqlQuery q("SELECT ETAT, COUNT(*) FROM COMMANDE GROUP BY ETAT", Db::instance().conn());
    if (q.exec()) {
        while (q.next()) {
            result.append(qMakePair(q.value(0).toString(), q.value(1).toInt()));
        }
    }
    return result;
}

bool OrderDao::updateOrderPriority(int orderId, const QString& priority) {
    QSqlQuery q(Db::instance().conn());
    q.prepare("UPDATE COMMANDE SET PRIORITY = :priority WHERE ID_COMMANDE = :id");
    q.bindValue(":priority", priority);
    q.bindValue(":id", orderId);
    return q.exec();
}
