#pragma once
#include <QVector>
#include <optional>
#include <QSqlDatabase>
#include "client.h"

class ClientDao {
public:
    ClientDao();

    bool add(const Client& c);
    bool update(const Client& c);
    bool remove(int id);
    std::optional<Client> getById(int id);
    QVector<Client> getAll();

    // Search and business functions
    QVector<Client> search(const QString& nameFilter = "",
                           const QString& statusFilter = "",
                           const QString& emailFilter = "");
    bool updateCategory(int clientId, const QString& category);
    QVector<Client> getTopClients(int limit = 5);
    bool autoCategorize();
    int getOrderCount(int clientId) const;

private:
    QSqlDatabase m_db;
};
