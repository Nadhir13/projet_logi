#pragma once

#include <QMainWindow>
#include <QAbstractItemView>
#include <QtCharts>

// Add forward declarations for the controllers
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

    // Make the UI accessible to the controllers (e.g., via friend class or getters)
    Ui::MainWindow* getUi() const { return ui; }

private slots:
    // Only general app slots remain here
    void logout();
    void onTabChanged(int index);

private:
    void setupPermissionsBasedOnRole();
    void setupMenuBar();

    Ui::MainWindow *ui;
    int m_userId;
    QString m_username;
    QString m_role;

    // Add pointers to the controllers
    ClientController* m_clientController = nullptr;
    OrderController* m_orderController = nullptr;
    UserController* m_userController = nullptr;

public:
    // Make chart views accessible to controllers
    QChartView* clientChartView = nullptr;
    QChartView* orderChartView = nullptr;
    QChartView* userChartView = nullptr;
};
