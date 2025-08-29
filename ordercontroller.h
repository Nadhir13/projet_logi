#pragma once

#include <QObject>
#include "order.h"
#include "orderdao.h"

class MainWindow; // Forward declaration

class OrderController : public QObject
{
    Q_OBJECT

public:
    explicit OrderController(MainWindow* mainWindow, QObject* parent = nullptr);
    void setupUi();
    void loadOrdersTable();
    void applyFilters();
    void updateChart();

public slots:
    void addOrder();
    void updateOrder();
    void deleteOrder();
    void refreshOrders();
    void exportToPdf();
    void showStats();
    void updateOrderPriority();

private:
    MainWindow* m_mainWindow;
    OrderDao m_dao;
    bool validateForm();
};
