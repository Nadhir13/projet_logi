#include "clientdao.h"
#include "db.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

ClientDao::ClientDao() {
    m_db = Db::instance().conn();
}

bool ClientDao::add(const Client& c) {
    QSqlQuery q(m_db);
    q.prepare(R"(INSERT INTO CLIENT (NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, STATUT, CATEGORY)
                 VALUES (:n, :p, :t, :e, :a, :s, :cat))");
    q.bindValue(":n", c.nom);
    q.bindValue("p", c.prenom);
    q.bindValue(":t", c.tel);
    q.bindValue(":e", c.email);
    q.bindValue(":a", c.adr);
    q.bindValue(":s", c.statut);
    q.bindValue(":cat", c.category);

    bool success = q.exec();
    if (!success) {
        qDebug() << "ClientDao::add error:" << q.lastError().text();
    }
    return success;
}

bool ClientDao::update(const Client& c) {
    QSqlQuery q(m_db);
    q.prepare(R"(UPDATE CLIENT SET NOM=:n, PRENOM=:p, TELEPHONE=:t, EMAIL=:e,
                 ADRESSE=:a, STATUT=:s, CATEGORY=:cat WHERE ID_CLIENT=:id)");
    q.bindValue(":n", c.nom);
    q.bindValue(":p", c.prenom);
    q.bindValue(":t", c.tel);
    q.bindValue(":e", c.email);
    q.bindValue(":a", c.adr);
    q.bindValue(":s", c.statut);
    q.bindValue(":cat", c.category);
    q.bindValue(":id", c.id);

    bool success = q.exec();
    if (!success) {
        qDebug() << "ClientDao::update error:" << q.lastError().text();
    }
    return success;
}

bool ClientDao::remove(int id) {
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM CLIENT WHERE ID_CLIENT=:id");
    q.bindValue(":id", id);

    bool success = q.exec();
    if (!success) {
        qDebug() << "ClientDao::remove error:" << q.lastError().text();
    }
    return success;
}

std::optional<Client> ClientDao::getById(int id) {
    QSqlQuery q(m_db);
    q.prepare("SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, STATUT, DATE_CREATION, CATEGORY FROM CLIENT WHERE ID_CLIENT=:id");
    q.bindValue(":id", id);

    if (q.exec() && q.next()) {
        Client c;
        c.id = q.value(0).toInt();
        c.nom = q.value(1).toString();
        c.prenom = q.value(2).toString();
        c.tel = q.value(3).toString();
        c.email = q.value(4).toString();
        c.adr = q.value(5).toString();
        c.statut = q.value(6).toString();
        c.created = q.value(7).toDate();
        c.category = q.value(8).toString();
        return c;
    }

    qDebug() << "ClientDao::getById error:" << q.lastError().text();
    return std::nullopt;
}

QVector<Client> ClientDao::getAll() {
    QVector<Client> clients;
    QSqlQuery q("SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, STATUT, DATE_CREATION, CATEGORY FROM CLIENT ORDER BY NOM, PRENOM", m_db);

    if (q.exec()) {
        while (q.next()) {
            Client c;
            c.id = q.value(0).toInt();
            c.nom = q.value(1).toString();
            c.prenom = q.value(2).toString();
            c.tel = q.value(3).toString();
            c.email = q.value(4).toString();
            c.adr = q.value(5).toString();
            c.statut = q.value(6).toString();
            c.created = q.value(7).toDate();
            c.category = q.value(8).toString();
            clients.append(c);
        }
    } else {
        qDebug() << "ClientDao::getAll error:" << q.lastError().text();
    }

    return clients;
}

QVector<Client> ClientDao::search(const QString& nameFilter, const QString& statusFilter, const QString& emailFilter) {
    QVector<Client> clients;
    QString queryStr = "SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, STATUT, DATE_CREATION, CATEGORY FROM CLIENT WHERE 1=1";

    if (!nameFilter.isEmpty()) {
        queryStr += " AND (NOM LIKE :name OR PRENOM LIKE :name)";
    }
    if (!statusFilter.isEmpty() && statusFilter != "Tous") {
        queryStr += " AND STATUT = :status";
    }
    if (!emailFilter.isEmpty()) {
        queryStr += " AND EMAIL LIKE :email";
    }

    queryStr += " ORDER BY NOM, PRENOM";

    QSqlQuery q(m_db);
    q.prepare(queryStr);

    if (!nameFilter.isEmpty()) {
        q.bindValue(":name", "%" + nameFilter + "%");
    }
    if (!statusFilter.isEmpty() && statusFilter != "Tous") {
        q.bindValue(":status", statusFilter);
    }
    if (!emailFilter.isEmpty()) {
        q.bindValue(":email", "%" + emailFilter + "%");
    }

    if (q.exec()) {
        while (q.next()) {
            Client c;
            c.id = q.value(0).toInt();
            c.nom = q.value(1).toString();
            c.prenom = q.value(2).toString();
            c.tel = q.value(3).toString();
            c.email = q.value(4).toString();
            c.adr = q.value(5).toString();
            c.statut = q.value(6).toString();
            c.created = q.value(7).toDate();
            c.category = q.value(8).toString();
            clients.append(c);
        }
    } else {
        qDebug() << "ClientDao::search error:" << q.lastError().text();
    }

    return clients;
}

bool ClientDao::updateCategory(int clientId, const QString& category) {
    QSqlQuery q(m_db);
    q.prepare("UPDATE CLIENT SET CATEGORY = :cat WHERE ID_CLIENT = :id");
    q.bindValue(":cat", category);
    q.bindValue(":id", clientId);

    bool success = q.exec();
    if (!success) {
        qDebug() << "ClientDao::updateCategory error:" << q.lastError().text();
    }
    return success;
}

QVector<Client> ClientDao::getTopClients(int limit) {
    QVector<Client> clients;
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT c.ID_CLIENT, c.NOM, c.PRENOM, c.TELEPHONE, c.EMAIL,
               c.ADRESSE, c.STATUT, c.DATE_CREATION, c.CATEGORY,
               COUNT(o.ID_COMMANDE) as order_count
        FROM CLIENT c
        LEFT JOIN COMMANDE o ON c.ID_CLIENT = o.ID_CLIENT
        GROUP BY c.ID_CLIENT, c.NOM, c.PRENOM, c.TELEPHONE, c.EMAIL,
                 c.ADRESSE, c.STATUT, c.DATE_CREATION, c.CATEGORY
        ORDER BY order_count DESC
        FETCH FIRST :limit ROWS ONLY
    )");
    q.bindValue(":limit", limit);

    if (q.exec()) {
        while (q.next()) {
            Client c;
            c.id = q.value(0).toInt();
            c.nom = q.value(1).toString();
            c.prenom = q.value(2).toString();
            c.tel = q.value(3).toString();
            c.email = q.value(4).toString();
            c.adr = q.value(5).toString();
            c.statut = q.value(6).toString();
            c.created = q.value(7).toDate();
            c.category = q.value(8).toString();
            c.totalOrders = q.value(9).toInt();
            clients.append(c);
        }
    } else {
        qDebug() << "ClientDao::getTopClients error:" << q.lastError().text();
    }

    return clients;
}

bool ClientDao::autoCategorize() {
    QSqlQuery q(m_db);
    q.prepare(R"(
        UPDATE CLIENT c
        SET CATEGORY = CASE
            WHEN (SELECT COUNT(*) FROM COMMANDE
                  WHERE ID_CLIENT = c.ID_CLIENT AND ETAT = 'LIVREE') >= 10 THEN 'PLATINUM'
            WHEN (SELECT COUNT(*) FROM COMMANDE
                  WHERE ID_CLIENT = c.ID_CLIENT AND ETAT = 'LIVREE') >= 5 THEN 'GOLD'
            WHEN (SELECT COUNT(*) FROM COMMANDE
                  WHERE ID_CLIENT = c.ID_CLIENT AND ETAT = 'LIVREE') >= 2 THEN 'SILVER'
            ELSE 'REGULAR'
        END
    )");

    bool success = q.exec();
    if (!success) {
        qDebug() << "ClientDao::autoCategorize error:" << q.lastError().text();
    }
    return success;
}

int ClientDao::getOrderCount(int clientId) const {
    QSqlQuery q(m_db);
    q.prepare("SELECT COUNT(*) FROM COMMANDE WHERE ID_CLIENT = :id");
    q.bindValue(":id", clientId);

    if (q.exec() && q.next()) {
        return q.value(0).toInt();
    }

    qDebug() << "ClientDao::getOrderCount error:" << q.lastError().text();
    return 0;
}
