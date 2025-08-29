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

    // Search and business functions
    QVector<Order> search(int clientId = -1,
                          const QString& statusFilter = "",
                          double minAmount = -1,
                          double maxAmount = -1);
    double getTotalRevenue() const;
    QVector<QPair<QString, int>> getOrdersByStatus() const;
    bool updateOrderPriority(int orderId, const QString& priority);
};
