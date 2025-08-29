#pragma once
#include <QVector>
#include <optional>
#include "client.h"

class ClientDao {
public:
    bool add(const Client& c);
    bool upd(const Client& c);
    bool del(int id);
    std::optional<Client> byId(int id);
    QVector<Client> all();

    // Search and business functions
    QVector<Client> search(const QString& nameFilter = "",
                           const QString& statusFilter = "",
                           const QString& emailFilter = "");
    bool updateClientCategory(int clientId, const QString& category);
    QVector<Client> getTopClients(int limit = 5);
    bool autoCategorizeClients();
};
