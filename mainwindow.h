#pragma once

#include <QMainWindow>
#include <QAbstractItemView>
#include <QtCharts>

// Forward declarations for the controllers
class ClientController;
class OrderController;
class UserController;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(int userId, const QString &username, const QString &role, QWidget *parent = nullptr);
    ~MainWindow();

    // Make the UI accessible to the controllers
    Ui::MainWindow* getUi() const { return ui; }

    // Getters for user information
    int getUserId() const { return m_userId; }
    QString getUsername() const { return m_username; }
    QString getRole() const { return m_role; }

    // Chart views accessible to controllers
    QChartView* clientChartView = nullptr;
    QChartView* orderChartView = nullptr;
    QChartView* userChartView = nullptr;

private slots:
    void logout();
    void onTabChanged(int index);

private:
    void setupPermissionsBasedOnRole();
    void setupMenuBar();
    void initializeChartViews();
    void setupStatusBar();
    void applyAppStyle();

    Ui::MainWindow *ui;
    int m_userId;
    QString m_username;
    QString m_role;

    // Pointers to the controllers
    ClientController* m_clientController = nullptr;
    OrderController* m_orderController = nullptr;
    UserController* m_userController = nullptr;
};
