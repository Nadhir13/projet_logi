#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientcontroller.h"
#include "ordercontroller.h"
#include "usercontroller.h"
#include "stylemanager.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QtCharts>
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QDateTime>

void MainWindow::initializeChartViews()
{
    // Create chart views for each tab
    clientChartView = new QChartView();
    orderChartView = new QChartView();
    userChartView = new QChartView();

    // Set chart view properties
    clientChartView->setRenderHint(QPainter::Antialiasing);
    orderChartView->setRenderHint(QPainter::Antialiasing);
    userChartView->setRenderHint(QPainter::Antialiasing);

    // Create layouts for containers if they don't have them
    if (!ui->clientChartContainer->layout()) {
        ui->clientChartContainer->setLayout(new QVBoxLayout());
        ui->clientChartContainer->layout()->setContentsMargins(0, 0, 0, 0);
    }
    if (!ui->orderChartContainer->layout()) {
        ui->orderChartContainer->setLayout(new QVBoxLayout());
        ui->orderChartContainer->layout()->setContentsMargins(0, 0, 0, 0);
    }
    if (!ui->userChartContainer->layout()) {
        ui->userChartContainer->setLayout(new QVBoxLayout());
        ui->userChartContainer->layout()->setContentsMargins(0, 0, 0, 0);
    }

    // Add chart views to their respective containers
    ui->clientChartContainer->layout()->addWidget(clientChartView);
    ui->orderChartContainer->layout()->addWidget(orderChartView);
    ui->userChartContainer->layout()->addWidget(userChartView);
}

void MainWindow::setupStatusBar()
{
    QStatusBar *statusBar = this->statusBar();

    // Add user info to status bar
    QLabel *userLabel = new QLabel(QString("Utilisateur: %1 (%2)").arg(m_username).arg(m_role));
    statusBar->addPermanentWidget(userLabel);

    // Add current time
    QLabel *timeLabel = new QLabel();
    statusBar->addPermanentWidget(timeLabel);

    // Update time every second
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [timeLabel]() {
        timeLabel->setText(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));
    });
    timer->start(1000);
}

void MainWindow::applyButtonStyling()
{
    // Apply specific button classes for different actions
    if (ui->btnAddClient) ui->btnAddClient->setProperty("class", "success");
    if (ui->btnDelClient) ui->btnDelClient->setProperty("class", "danger");
    if (ui->btnAddOrd) ui->btnAddOrd->setProperty("class", "success");
    if (ui->btnDelOrd) ui->btnDelOrd->setProperty("class", "danger");
    if (ui->btnAddUser) ui->btnAddUser->setProperty("class", "success");
    if (ui->btnDelUser) ui->btnDelUser->setProperty("class", "danger");

    // Force style update
    style()->unpolish(this);
    style()->polish(this);
}

MainWindow::MainWindow(int userId, const QString &username, const QString &role, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_userId(userId), m_username(username), m_role(role)
{
    ui->setupUi(this);

    // Apply modern styling
    StyleManager::instance().applyModernStyle();

    // Set window title with user info
    setWindowTitle(QString("Système de Gestion Logistique - Connecté en tant que: %1 (%2)").arg(username).arg(role));

    // Setup menu bar with logout option
    setupMenuBar();

    // Setup UI based on user role
    setupPermissionsBasedOnRole();

    // Initialize controllers
    m_clientController = new ClientController(this, this);
    m_orderController = new OrderController(this, this);
    m_userController = new UserController(this, this);

    // Setup controllers
    m_clientController->setupUi();
    m_orderController->setupUi();
    m_userController->setupUi();

    // Initialize chart views
    initializeChartViews();

    // Load initial data
    m_clientController->refreshClients();
    m_orderController->refreshOrders();
    m_userController->refreshUsers();

    // Connect tab change signal
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // Setup status bar
    setupStatusBar();

    // Apply button styling
    applyButtonStyling();
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    // File menu
    QMenu *fileMenu = menuBar->addMenu("&Fichier");

    QAction *exportAction = new QAction("&Exporter", this);
    exportAction->setShortcut(QKeySequence::Save);
    fileMenu->addAction(exportAction);

    fileMenu->addSeparator();

    QAction *logoutAction = new QAction("&Déconnexion", this);
    logoutAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(logoutAction, &QAction::triggered, this, &MainWindow::logout);
    fileMenu->addAction(logoutAction);

    QAction *exitAction = new QAction("&Quitter", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QApplication::quit);
    fileMenu->addAction(exitAction);

    // View menu
    QMenu *viewMenu = menuBar->addMenu("&Affichage");

    QAction *modernStyleAction = new QAction("Style &Moderne", this);
    connect(modernStyleAction, &QAction::triggered, [this]() {
        StyleManager::instance().applyModernStyle();
    });
    viewMenu->addAction(modernStyleAction);

    QAction *darkStyleAction = new QAction("Style &Sombre", this);
    connect(darkStyleAction, &QAction::triggered, [this]() {
        StyleManager::instance().applyDarkStyle();
    });
    viewMenu->addAction(darkStyleAction);

    QAction *lightStyleAction = new QAction("Style &Clair", this);
    connect(lightStyleAction, &QAction::triggered, [this]() {
        StyleManager::instance().applyLightStyle();
    });
    viewMenu->addAction(lightStyleAction);

    // Help menu
    QMenu *helpMenu = menuBar->addMenu("&Aide");

    QAction *aboutAction = new QAction("À &propos", this);
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, "À propos",
                           "Système de Gestion Logistique\n\n"
                           "Version 2.0\n"
                           "Développé avec Qt 6\n\n"
                           "© 2024 Tous droits réservés");
    });
    helpMenu->addAction(aboutAction);
}

void MainWindow::setupPermissionsBasedOnRole()
{
    // Disable tabs based on user role
    if (m_role == "DELIVERY") {
        ui->tabWidget->setTabEnabled(2, false); // Disable Users tab
        ui->tabWidget->setTabEnabled(1, false); // Disable Orders tab
    } else if (m_role == "MANAGER") {
        ui->tabWidget->setTabEnabled(2, false); // Disable Users tab
    }
    // ADMIN has access to all tabs
}

void MainWindow::logout()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Déconnexion",
                                                              "Êtes-vous sûr de vouloir vous déconnecter?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        close();
    }
}

void MainWindow::onTabChanged(int index)
{
    // Update status bar with current tab info
    QString tabName = ui->tabWidget->tabText(index);
    statusBar()->showMessage(QString("Onglet actuel: %1").arg(tabName), 3000);

    // Refresh data for the current tab
    switch (index) {
    case 0: // Clients
        m_clientController->refreshClients();
        break;
    case 1: // Orders
        m_orderController->refreshOrders();
        break;
    case 2: // Users
        m_userController->refreshUsers();
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
