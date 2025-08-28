#include "clientdao.h"
#include "db.h"
#include <QSqlQuery>
#include <QSqlError>

bool ClientDao::add(const Client& c) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(INSERT INTO CLIENT (NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, STATUT)
                 VALUES (:n,:p,:t,:e,:a,:s))");
    q.bindValue(":n", c.nom);
    q.bindValue(":p", c.prenom);
    q.bindValue(":t", c.tel);
    q.bindValue(":e", c.email);
    q.bindValue(":a", c.adr);
    q.bindValue(":s", c.statut);
    return q.exec();
}

bool ClientDao::upd(const Client& c) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(UPDATE CLIENT SET NOM=:n, PRENOM=:p, TELEPHONE=:t, EMAIL=:e, ADRESSE=:a, STATUT=:s
                 WHERE ID_CLIENT=:id)");
    q.bindValue(":n", c.nom);
    q.bindValue(":p", c.prenom);
    q.bindValue(":t", c.tel);
    q.bindValue(":e", c.email);
    q.bindValue(":a", c.adr);
    q.bindValue(":s", c.statut);
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
    q.prepare("SELECT ID_CLIENT,NOM,PRENOM,TELEPHONE,EMAIL,ADRESSE,STATUT,DATE_CREATION FROM CLIENT WHERE ID_CLIENT=:id");
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
        return c;
    }
    return std::nullopt;
}

QVector<Client> ClientDao::all() {
    QVector<Client> v;
    QSqlQuery q("SELECT ID_CLIENT,NOM,PRENOM,TELEPHONE,EMAIL,ADRESSE,STATUT,DATE_CREATION FROM CLIENT", Db::instance().conn());
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
            v.push_back(c);
        }
    }
    return v;
}
