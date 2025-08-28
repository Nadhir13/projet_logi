#pragma once
#include <QMainWindow>
#include <QAbstractItemView>  // Add this for table selection properties
// Keep charts types out of the header to avoid compile-time namespace issues

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

private:
    void loadClientsTable();
    void loadOrdersTable();
    void loadClientsCombo();
    bool validateClientForm();  // ADD THIS LINE

    // filters
    void applyClientFilters();
    void applyOrderFilters();

    // charts
    void updateClientChart();
    void updateOrderChart();

private:
    Ui::MainWindow *ui;
    // charts (stored as QWidget* to decouple header from QtCharts)
    QWidget* clientChartView = nullptr;
    QWidget* orderChartView = nullptr;
};
