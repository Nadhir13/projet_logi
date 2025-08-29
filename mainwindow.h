#pragma once
#include <QMainWindow>
#include <QAbstractItemView>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // client
    void addClient();
    void updClient();
    void delClient();
    void refClient();

    // order
    void addOrder();
    void updOrder();
    void delOrder();
    void refOrder();
    void exportOrderPdf();

    // Business functions
    void showClientStats();
    void showOrderStats();
    void exportClientsExcel();
    void updateClientCategory();
    void updateOrderPriority();
    void autoCategorizeClients();

private:
    void loadClientsTable();
    void loadOrdersTable();
    void loadClientsCombo();
    void loadClientFilterCombo();
    bool validateClientForm();
    bool validateOrderForm();

    // filters
    void applyClientFilters();
    void applyOrderFilters();

    // charts
    void updateClientChart();
    void updateOrderChart();

private:
    Ui::MainWindow *ui;
    QChartView* clientChartView = nullptr;
    QChartView* orderChartView = nullptr;
};
