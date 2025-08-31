#include "orderdao.h"
#include "db.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

OrderDao::OrderDao() {
    m_db = Db::instance().conn();
}

bool OrderDao::add(const Order& o) {
    QSqlQuery q(m_db);
    q.prepare(R"(INSERT INTO COMMANDE (ID_CLIENT, ETAT, MONTANT, ADRESSE_LIVRAISON, PRIORITY, ESTIMATED_DELIVERY)
                 VALUES (:c, :e, :m, :a, :p, :ed))");
    q.bindValue(":c", o.clientId);
    q.bindValue(":e", o.etat);
    q.bindValue(":m", o.montant);
    q.bindValue(":a", o.adrLiv);
    q.bindValue(":p", o.priority);
    q.bindValue(":ed", o.estimatedDelivery);

    bool success = q.exec();
    if (!success) {
        qDebug() << "OrderDao::add error:" << q.lastError().text();
    }
    return success;
}

bool OrderDao::update(const Order& o) {
    QSqlQuery q(m_db);
    q.prepare(R"(UPDATE COMMANDE SET ID_CLIENT=:c, ETAT=:e, MONTANT=:m,
                 ADRESSE_LIVRAISON=:a, PRIORITY=:p, ESTIMATED_DELIVERY=:ed
                 WHERE ID_COMMANDE=:id)");
    q.bindValue(":c", o.clientId);
    q.bindValue(":e", o.etat);
    q.bindValue(":m", o.montant);
    q.bindValue(":a", o.adrLiv);
    q.bindValue(":p", o.priority);
    q.bindValue(":ed", o.estimatedDelivery);
    q.bindValue(":id", o.id);

    bool success = q.exec();
    if (!success) {
        qDebug() << "OrderDao::update error:" << q.lastError().text();
    }
    return success;
}

bool OrderDao::remove(int id) {
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM COMMANDE WHERE ID_COMMANDE=:id");
    q.bindValue(":id", id);

    bool success = q.exec();
    if (!success) {
        qDebug() << "OrderDao::remove error:" << q.lastError().text();
    }
    return success;
}

std::optional<Order> OrderDao::getById(int id) {
    QSqlQuery q(m_db);
    q.prepare("SELECT ID_COMMANDE, ID_CLIENT, DATE_COMMANDE, ETAT, MONTANT, ADRESSE_LIVRAISON, PRIORITY, ESTIMATED_DELIVERY FROM COMMANDE WHERE ID_COMMANDE=:id");
    q.bindValue(":id", id);

    if (q.exec() && q.next()) {
        Order o;
        o.id = q.value(0).toInt();
        o.clientId = q.value(1).toInt();
        o.date = q.value(2).toDate();
        o.etat = q.value(3).toString();
        o.montant = q.value(4).toDouble();
        o.adrLiv = q.value(5).toString();
        o.priority = q.value(6).toString();
        o.estimatedDelivery = q.value(7).toDate();
        return o;
    }

    qDebug() << "OrderDao::getById error:" << q.lastError().text();
    return std::nullopt;
}

QVector<Order> OrderDao::getAll() {
    QVector<Order> orders;
    QSqlQuery q("SELECT ID_COMMANDE, ID_CLIENT, DATE_COMMANDE, ETAT, MONTANT, ADRESSE_LIVRAISON, PRIORITY, ESTIMATED_DELIVERY FROM COMMANDE ORDER BY ID_COMMANDE DESC", m_db);

    if (q.exec()) {
        while (q.next()) {
            Order o;
            o.id = q.value(0).toInt();
            o.clientId = q.value(1).toInt();
            o.date = q.value(2).toDate();
            o.etat = q.value(3).toString();
            o.montant = q.value(4).toDouble();
            o.adrLiv = q.value(5).toString();
            o.priority = q.value(6).toString();
            o.estimatedDelivery = q.value(7).toDate();
            orders.append(o);
        }
    } else {
        qDebug() << "OrderDao::getAll error:" << q.lastError().text();
    }

    return orders;
}

QVector<Order> OrderDao::search(int clientId, const QString& statusFilter, double minAmount, double maxAmount) {
    QVector<Order> orders;
    QString queryStr = "SELECT ID_COMMANDE, ID_CLIENT, DATE_COMMANDE, ETAT, MONTANT, ADRESSE_LIVRAISON, PRIORITY, ESTIMATED_DELIVERY FROM COMMANDE WHERE 1=1";

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

    QSqlQuery q(m_db);
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
            o.id = q.value(0).toInt();
            o.clientId = q.value(1).toInt();
            o.date = q.value(2).toDate();
            o.etat = q.value(3).toString();
            o.montant = q.value(4).toDouble();
            o.adrLiv = q.value(5).toString();
            o.priority = q.value(6).toString();
            o.estimatedDelivery = q.value(7).toDate();
            orders.append(o);
        }
    } else {
        qDebug() << "OrderDao::search error:" << q.lastError().text();
    }

    return orders;
}

double OrderDao::getTotalRevenue() const {
    QSqlQuery q("SELECT SUM(MONTANT) FROM COMMANDE WHERE ETAT = 'LIVREE'", m_db);
    if (q.exec() && q.next()) {
        return q.value(0).toDouble();
    }

    qDebug() << "OrderDao::getTotalRevenue error:" << q.lastError().text();
    return 0.0;
}

QVector<QPair<QString, int>> OrderDao::getOrdersByStatus() const {
    QVector<QPair<QString, int>> result;
    QSqlQuery q("SELECT ETAT, COUNT(*) FROM COMMANDE GROUP BY ETAT", m_db);

    if (q.exec()) {
        while (q.next()) {
            result.append(qMakePair(q.value(0).toString(), q.value(1).toInt()));
        }
    } else {
        qDebug() << "OrderDao::getOrdersByStatus error:" << q.lastError().text();
    }

    return result;
}

bool OrderDao::updatePriority(int orderId, const QString& priority) {
    QSqlQuery q(m_db);
    q.prepare("UPDATE COMMANDE SET PRIORITY = :priority WHERE ID_COMMANDE = :id");
    q.bindValue(":priority", priority);
    q.bindValue(":id", orderId);

    bool success = q.exec();
    if (!success) {
        qDebug() << "OrderDao::updatePriority error:" << q.lastError().text();
    }
    return success;
}

bool OrderDao::autoUpdatePriorities() {
    QSqlQuery q(m_db);
    q.prepare(R"(
        UPDATE COMMANDE
        SET PRIORITY = CASE
            WHEN MONTANT > 500 THEN 'URGENT'
            WHEN MONTANT > 200 THEN 'HIGH'
            WHEN MONTANT > 50 THEN 'NORMAL'
            ELSE 'LOW'
        END
        WHERE ETAT IN ('EN_ATTENTE', 'EN_COURS')
    )");

    bool success = q.exec();
    if (!success) {
        qDebug() << "OrderDao::autoUpdatePriorities error:" << q.lastError().text();
    }
    return success;
}
