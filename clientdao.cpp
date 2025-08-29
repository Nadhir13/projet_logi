#include "clientdao.h"
#include "db.h"
#include <QSqlQuery>
#include <QSqlError>

bool ClientDao::add(const Client& c) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(INSERT INTO CLIENT (NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, STATUT, CATEGORY)
                 VALUES (:n,:p,:t,:e,:a,:s,:cat))");
    q.bindValue(":n", c.nom);
    q.bindValue(":p", c.prenom);
    q.bindValue(":t", c.tel);
    q.bindValue(":e", c.email);
    q.bindValue(":a", c.adr);
    q.bindValue(":s", c.statut);
    q.bindValue(":cat", c.category);
    return q.exec();
}

bool ClientDao::upd(const Client& c) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(UPDATE CLIENT SET NOM=:n, PRENOM=:p, TELEPHONE=:t, EMAIL=:e, ADRESSE=:a, STATUT=:s, CATEGORY=:cat
                 WHERE ID_CLIENT=:id)");
    q.bindValue(":n", c.nom);
    q.bindValue(":p", c.prenom);
    q.bindValue(":t", c.tel);
    q.bindValue(":e", c.email);
    q.bindValue(":a", c.adr);
    q.bindValue(":s", c.statut);
    q.bindValue(":cat", c.category);
    q.bindValue(":id", c.id);
    return q.exec();
}

bool ClientDao::del(int id) {
    QSqlQuery q(Db::instance().conn());
    q.prepare("DELETE FROM CLIENT WHERE ID_CLIENT=:id");
    q.bindValue(":id", id);
    return q.exec();
}

std::optional<Client> ClientDao::byId(int id) {
    QSqlQuery q(Db::instance().conn());
    q.prepare("SELECT ID_CLIENT,NOM,PRENOM,TELEPHONE,EMAIL,ADRESSE,STATUT,DATE_CREATION,CATEGORY FROM CLIENT WHERE ID_CLIENT=:id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        Client c;
        c.id      = q.value(0).toInt();
        c.nom     = q.value(1).toString();
        c.prenom  = q.value(2).toString();
        c.tel     = q.value(3).toString();
        c.email   = q.value(4).toString();
        c.adr     = q.value(5).toString();
        c.statut  = q.value(6).toString();
        c.created = q.value(7).toDate();
        c.category = q.value(8).toString();
        return c;
    }
    return std::nullopt;
}

QVector<Client> ClientDao::all() {
    QVector<Client> v;
    QSqlQuery q("SELECT ID_CLIENT,NOM,PRENOM,TELEPHONE,EMAIL,ADRESSE,STATUT,DATE_CREATION,CATEGORY FROM CLIENT", Db::instance().conn());
    if (q.exec()) {
        while (q.next()) {
            Client c;
            c.id      = q.value(0).toInt();
            c.nom     = q.value(1).toString();
            c.prenom  = q.value(2).toString();
            c.tel     = q.value(3).toString();
            c.email   = q.value(4).toString();
            c.adr     = q.value(5).toString();
            c.statut  = q.value(6).toString();
            c.created = q.value(7).toDate();
            c.category = q.value(8).toString();
            v.push_back(c);
        }
    }
    return v;
}

QVector<Client> ClientDao::search(const QString& nameFilter,
                                  const QString& statusFilter,
                                  const QString& emailFilter) {
    QVector<Client> v;
    QString queryStr = "SELECT ID_CLIENT,NOM,PRENOM,TELEPHONE,EMAIL,ADRESSE,STATUT,DATE_CREATION,CATEGORY FROM CLIENT WHERE 1=1";

    if (!nameFilter.isEmpty()) {
        queryStr += " AND (NOM LIKE :name OR PRENOM LIKE :name)";
    }
    if (!statusFilter.isEmpty() && statusFilter != "Tous") {
        queryStr += " AND STATUT = :status";
    }
    if (!emailFilter.isEmpty()) {
        queryStr += " AND EMAIL LIKE :email";
    }

    QSqlQuery q(Db::instance().conn());
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
            c.id      = q.value(0).toInt();
            c.nom     = q.value(1).toString();
            c.prenom  = q.value(2).toString();
            c.tel     = q.value(3).toString();
            c.email   = q.value(4).toString();
            c.adr     = q.value(5).toString();
            c.statut  = q.value(6).toString();
            c.created = q.value(7).toDate();
            c.category = q.value(8).toString();
            v.push_back(c);
        }
    }
    return v;
}

bool ClientDao::updateClientCategory(int clientId, const QString& category) {
    QSqlQuery q(Db::instance().conn());
    q.prepare("UPDATE CLIENT SET CATEGORY = :cat WHERE ID_CLIENT = :id");
    q.bindValue(":cat", category);
    q.bindValue(":id", clientId);
    return q.exec();
}

QVector<Client> ClientDao::getTopClients(int limit) {
    QVector<Client> v;
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(
        SELECT c.ID_CLIENT, c.NOM, c.PRENOM, c.TELEPHONE, c.EMAIL,
               c.ADRESSE, c.STATUT, c.DATE_CREATION, c.CATEGORY, COUNT(o.ID_COMMANDE) as order_count
        FROM CLIENT c
        LEFT JOIN COMMANDE o ON c.ID_CLIENT = o.ID_CLIENT
        GROUP BY c.ID_CLIENT, c.NOM, c.PRENOM, c.TELEPHONE, c.EMAIL, c.ADRESSE, c.STATUT, c.DATE_CREATION, c.CATEGORY
        ORDER BY order_count DESC
        FETCH FIRST :limit ROWS ONLY
    )");
    q.bindValue(":limit", limit);

    if (q.exec()) {
        while (q.next()) {
            Client c;
            c.id      = q.value(0).toInt();
            c.nom     = q.value(1).toString();
            c.prenom  = q.value(2).toString();
            c.tel     = q.value(3).toString();
            c.email   = q.value(4).toString();
            c.adr     = q.value(5).toString();
            c.statut  = q.value(6).toString();
            c.created = q.value(7).toDate();
            c.category = q.value(8).toString();
            c.totalOrders = q.value(9).toInt();
            v.push_back(c);
        }
    }
    return v;
}
