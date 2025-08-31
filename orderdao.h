#pragma once
#include <QVector>
#include <optional>
#include <QSqlDatabase>
#include "order.h"

class OrderDao {
public:
    OrderDao();

    bool add(const Order& o);
    bool update(const Order& o);
    bool remove(int id);
    std::optional<Order> getById(int id);
    QVector<Order> getAll();

    // Search and business functions
    QVector<Order> search(int clientId = -1,
                          const QString& statusFilter = "",
                          double minAmount = -1,
                          double maxAmount = -1);
    double getTotalRevenue() const;
    QVector<QPair<QString, int>> getOrdersByStatus() const;
    bool updatePriority(int orderId, const QString& priority);
    bool autoUpdatePriorities();

private:
    QSqlDatabase m_db;
};
