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
};
