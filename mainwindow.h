#pragma once
#include <QMainWindow>
#include <QAbstractItemView>  // Add this for table selection properties

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

private:
    Ui::MainWindow *ui;
};
