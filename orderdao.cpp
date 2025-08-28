#include "orderdao.h"
#include "db.h"
#include <QSqlQuery>
#include <QSqlError>

bool OrderDao::add(const Order& o) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(INSERT INTO COMMANDE (ID_CLIENT, ETAT, MONTANT, ADRESSE_LIVRAISON)
                 VALUES (:c,:e,:m,:a))");
    q.bindValue(":c", o.clientId);
    q.bindValue(":e", o.etat);
    q.bindValue(":m", o.montant);
    q.bindValue(":a", o.adrLiv);
    return q.exec();
}

bool OrderDao::upd(const Order& o) {
    QSqlQuery q(Db::instance().conn());
    q.prepare(R"(UPDATE COMMANDE SET ID_CLIENT=:c, ETAT=:e, MONTANT=:m, ADRESSE_LIVRAISON=:a
                 WHERE ID_COMMANDE=:id)");
    q.bindValue(":c", o.clientId);
    q.bindValue(":e", o.etat);
    q.bindValue(":m", o.montant);
    q.bindValue(":a", o.adrLiv);
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
    q.prepare("SELECT ID_COMMANDE,ID_CLIENT,DATE_COMMANDE,ETAT,MONTANT,ADRESSE_LIVRAISON FROM COMMANDE WHERE ID_COMMANDE=:id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        Order o;
        o.id      = q.value(0).toInt();
        o.clientId= q.value(1).toInt();
        o.date    = q.value(2).toDate();
        o.etat    = q.value(3).toString();
        o.montant = q.value(4).toDouble();
        o.adrLiv  = q.value(5).toString();
        return o;
    }
    return std::nullopt;
}

QVector<Order> OrderDao::all() {
    QVector<Order> v;
    QSqlQuery q("SELECT ID_COMMANDE,ID_CLIENT,DATE_COMMANDE,ETAT,MONTANT,ADRESSE_LIVRAISON FROM COMMANDE ORDER BY ID_COMMANDE DESC", Db::instance().conn());
    if (q.exec()) {
        while (q.next()) {
            Order o;
            o.id      = q.value(0).toInt();
            o.clientId= q.value(1).toInt();
            o.date    = q.value(2).toDate();
            o.etat    = q.value(3).toString();
            o.montant = q.value(4).toDouble();
            o.adrLiv  = q.value(5).toString();
            v.push_back(o);
        }
    }
    return v;
}
