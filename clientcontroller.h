#pragma once

#include <QObject>
#include "client.h"
#include "clientdao.h"

class MainWindow; // Forward declaration

class ClientController : public QObject
{
    Q_OBJECT

public:
    explicit ClientController(MainWindow* mainWindow, QObject* parent = nullptr);
    void setupUi(); // Connects signals/slots and initializes UI state for the client tab
    void loadClientsTable();
    void loadClientsCombo();
    void loadClientFilterCombo();
    void applyFilters();
    void updateChart();

public slots:
    void addClient();
    void updateClient();
    void deleteClient();
    void refreshClients();
    void showStats();
    void exportToExcel();
    void updateClientCategory();
    void autoCategorizeClients();

private:
    MainWindow* m_mainWindow; // Pointer to the main window for UI access
    ClientDao m_dao;
    bool validateForm();
};
