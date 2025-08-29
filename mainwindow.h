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
    explicit MainWindow(int userId, const QString &username, const QString &role, QWidget *parent = nullptr);
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

    // user management
    void addUser();
    void updUser();
    void delUser();
    void refUser();
    void changeUserPassword();

    // Business functions
    void showClientStats();
    void showOrderStats();
    void exportClientsExcel();
    void updateClientCategory();
    void updateOrderPriority();
    void autoCategorizeClients();

    // New logout function
    void logout();

    // Tab changed
    void onTabChanged(int index);

private:
    void loadClientsTable();
    void loadOrdersTable();
    void loadUsersTable();
    void loadClientsCombo();
    void loadClientFilterCombo();
    bool validateClientForm();
    bool validateOrderForm();
    bool validateUserForm();

    // filters
    void applyClientFilters();
    void applyOrderFilters();
    void applyUserFilters();

    // charts
    void updateClientChart();
    void updateOrderChart();
    void updateUserChart();

private:
    Ui::MainWindow *ui;
    QChartView* clientChartView = nullptr;
    QChartView* orderChartView = nullptr;
    QChartView* userChartView = nullptr;
    int m_userId;
    QString m_username;
    QString m_role;

    void setupPermissionsBasedOnRole();
    void setupMenuBar();
};
