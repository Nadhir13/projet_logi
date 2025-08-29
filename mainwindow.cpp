#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientcontroller.h"
#include "ordercontroller.h"
#include "usercontroller.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QtCharts>

MainWindow::MainWindow(int userId, const QString &username, const QString &role, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_userId(userId), m_username(username), m_role(role)
{
    ui->setupUi(this);

    // Set window title with user info
    setWindowTitle(QString("Système de Gestion Logistique - Connecté en tant que: %1 (%2)").arg(username).arg(role));

    // Setup menu bar with logout option
    setupMenuBar();

    // Setup UI based on user role
    setupPermissionsBasedOnRole();

    // Create the controllers
    m_clientController = new ClientController(this);
    m_orderController = new OrderController(this);
    m_userController = new UserController(this);

    // Let each controller set up its part of the UI and connections
    m_clientController->setupUi();
    m_orderController->setupUi();
    m_userController->setupUi();

    // Connect the main window's tab change signal
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // Connect selection changes for form population
    connect(ui->tblClients, &QTableWidget::itemSelectionChanged, this, [this]() {
        auto items = ui->tblClients->selectedItems();
        if (!items.isEmpty()) {
            int row = items.first()->row();
            ui->leNom->setText(ui->tblClients->item(row, 1)->text());
            ui->lePrenom->setText(ui->tblClients->item(row, 2)->text());
            ui->leTel->setText(ui->tblClients->item(row, 3)->text());
            ui->leEmail->setText(ui->tblClients->item(row, 4)->text());
            ui->leAdr->setText(ui->tblClients->item(row, 5)->text());

            QString statut = ui->tblClients->item(row, 6)->text();
            int index = ui->cbStatut->findText(statut);
            if (index >= 0) ui->cbStatut->setCurrentIndex(index);
        }
    });

    connect(ui->tblOrders, &QTableWidget::itemSelectionChanged, this, [this]() {
        auto items = ui->tblOrders->selectedItems();
        if (!items.isEmpty()) {
            int row = items.first()->row();
            int clientId = ui->tblOrders->item(row, 1)->text().toInt();

            for (int i = 0; i < ui->cbClient->count(); ++i) {
                if (ui->cbClient->itemData(i).toInt() == clientId) {
                    ui->cbClient->setCurrentIndex(i);
                    break;
                }
            }

            QString etat = ui->tblOrders->item(row, 3)->text();
            int index = ui->cbEtat->findText(etat);
            if (index >= 0) ui->cbEtat->setCurrentIndex(index);

            ui->dsMontant->setValue(ui->tblOrders->item(row, 4)->text().toDouble());
            ui->leAdrLiv->setText(ui->tblOrders->item(row, 5)->text());

            QString priority = ui->tblOrders->item(row, 6)->text();
            index = ui->cbPriority->findText(priority);
            if (index >= 0) ui->cbPriority->setCurrentIndex(index);
        }
    });

    connect(ui->tblUsers, &QTableWidget::itemSelectionChanged, this, [this]() {
        auto items = ui->tblUsers->selectedItems();
        if (!items.isEmpty()) {
            int row = items.first()->row();
            ui->leUserUsername->setText(ui->tblUsers->item(row, 1)->text());

            QString role = ui->tblUsers->item(row, 2)->text();
            int index = ui->cbUserRole->findText(role);
            if (index >= 0) ui->cbUserRole->setCurrentIndex(index);

            QString status = ui->tblUsers->item(row, 3)->text();
            index = ui->cbUserStatus->findText(status);
            if (index >= 0) ui->cbUserStatus->setCurrentIndex(index);

            // Switch to edit mode
            ui->stackedUser->setCurrentIndex(1);
        }
    });

    // Connect business function buttons
    connect(ui->btnClientStats, &QPushButton::clicked, m_clientController, &ClientController::showStats);
    connect(ui->btnOrderStats, &QPushButton::clicked, m_orderController, &OrderController::showStats);
    connect(ui->btnExportExcel, &QPushButton::clicked, m_clientController, &ClientController::exportToExcel);
    connect(ui->btnUpdateCategory, &QPushButton::clicked, m_clientController, &ClientController::updateClientCategory);
    connect(ui->btnUpdatePriority, &QPushButton::clicked, m_orderController, &OrderController::updateOrderPriority);

    // Load initial data
    m_clientController->loadClientsTable();
    m_clientController->loadClientsCombo();
    m_clientController->loadClientFilterCombo();
    m_orderController->loadOrdersTable();
    m_userController->loadUsersTable();

    // Setup charts containers with QtCharts
    clientChartView = new QChartView();
    clientChartView->setRenderHint(QPainter::Antialiasing);
    auto clientContainer = this->findChild<QWidget*>("clientChartContainer");
    if (clientContainer) {
        auto lay = new QVBoxLayout(clientContainer);
        lay->setContentsMargins(0,0,0,0);
        lay->addWidget(clientChartView);
    }

    orderChartView = new QChartView();
    orderChartView->setRenderHint(QPainter::Antialiasing);
    auto orderContainer = this->findChild<QWidget*>("orderChartContainer");
    if (orderContainer) {
        auto lay = new QVBoxLayout(orderContainer);
        lay->setContentsMargins(0,0,0,0);
        lay->addWidget(orderChartView);
    }

    userChartView = new QChartView();
    userChartView->setRenderHint(QPainter::Antialiasing);
    auto userContainer = this->findChild<QWidget*>("userChartContainer");
    if (userContainer) {
        auto lay = new QVBoxLayout(userContainer);
        lay->setContentsMargins(0,0,0,0);
        lay->addWidget(userChartView);
    }

    // Update charts
    m_clientController->updateChart();
    m_orderController->updateChart();
    m_userController->updateChart();
}

MainWindow::~MainWindow() {
    delete ui;
    // Delete the controllers
    delete m_clientController;
    delete m_orderController;
    delete m_userController;
}

void MainWindow::setupMenuBar()
{
    // Create menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Create user menu
    QMenu *userMenu = menuBar->addMenu("Utilisateur");

    // Add user info action
    QAction *userInfoAction = new QAction(QString("Connecté: %1").arg(m_username), this);
    userInfoAction->setEnabled(false);
    userMenu->addAction(userInfoAction);

    userMenu->addSeparator();

    // Add logout action
    QAction *logoutAction = new QAction("Déconnexion", this);
    logoutAction->setShortcut(QKeySequence::Quit);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::logout);
    userMenu->addAction(logoutAction);
}

void MainWindow::setupPermissionsBasedOnRole()
{
    // Admin has full access
    if (m_role == "Administrateur" || m_role == "ADMIN") {
        return; // No restrictions
    }

    // Manager (Gestionnaire logistique) can access everything except user management
    if (m_role == "Gestionnaire logistique" || m_role == "MANAGER") {
        // Hide user management tab
        ui->tabWidget->removeTab(2); // Remove Users tab
        return;
    }

    // Delivery (Livreur) has limited access
    if (m_role == "Livreur" || m_role == "DELIVERY") {
        // Hide client and user management tabs
        ui->tabWidget->removeTab(0); // Remove Clients tab
        ui->tabWidget->removeTab(1); // Remove Users tab (index changed after first removal)

        // Disable order modification buttons
        ui->btnAddOrd->setEnabled(false);
        ui->btnUpdOrd->setEnabled(false);
        ui->btnDelOrd->setEnabled(false);

        // Disable export and statistics buttons
        ui->btnPdfOrd->setEnabled(false);
        ui->btnOrderStats->setEnabled(false);
        ui->btnUpdatePriority->setEnabled(false);
    }
}

void MainWindow::onTabChanged(int index)
{
    if (index == 0) { // Clients tab
        m_clientController->refreshClients();
    } else if (index == 1) { // Orders tab
        m_orderController->refreshOrders();
    } else if (index == 2) { // Users tab
        m_userController->refreshUsers();
    }
}

void MainWindow::logout()
{
    // Confirm logout
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Déconnexion",
                                  "Êtes-vous sûr de vouloir vous déconnecter?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Close main window and show login dialog again
        close();
    }
}
