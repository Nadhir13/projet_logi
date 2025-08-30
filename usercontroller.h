#pragma once

#include <QObject>

class MainWindow;

class UserController : public QObject
{
    Q_OBJECT

public:
    explicit UserController(MainWindow* mainWindow, QObject* parent = nullptr);
    void setupUi();
    void loadUsersTable();
    void applyFilters();
    void updateChart();

public slots:
    void addUser();
    void updateUser();
    void deleteUser();
    void refreshUsers();
    void changePassword();
    void cancelEdit();
    void switchToEditMode();

private:
    MainWindow* m_mainWindow;
    bool validateForm();
};
