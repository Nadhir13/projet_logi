#pragma once
#include <QVector>
#include <optional>
#include "order.h"

class OrderDao {
public:
    bool add(const Order& o);
    bool upd(const Order& o);
    bool del(int id);
    std::optional<Order> byId(int id);
    QVector<Order> all();
};
