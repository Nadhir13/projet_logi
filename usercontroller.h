#pragma once

#include <QObject>
#include "user.h"
#include "userdao.h"

class MainWindow; // Forward declaration

class UserController : public QObject
{
    Q_OBJECT

public:
    explicit UserController(MainWindow* mainWindow, QObject* parent = nullptr);
    ~UserController();

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
    void onUserTableSelectionChanged();

private:
    void populateFormWithSelectedUser();
    bool validateForm(bool isNewUser = false);

    MainWindow* m_mainWindow;
    UserDao m_dao;
    int m_selectedUserId = -1;
    bool m_isEditMode = false;
};
