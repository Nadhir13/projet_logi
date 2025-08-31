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
    ~ClientController();

    void setupUi();
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
    void onClientTableSelectionChanged();

private:
    void populateFormWithSelectedClient();
    bool validateForm();

    MainWindow* m_mainWindow;
    ClientDao m_dao;
    int m_selectedClientId = -1;
};
