#pragma once
#include <QMainWindow>
#include "ui_mainwindow.h"


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

private:
    void loadClientsTable();
    void loadOrdersTable();
    void loadClientsCombo();

private:
    Ui::MainWindow *ui;
};
