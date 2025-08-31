#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientcontroller.h"
#include "ordercontroller.h"
#include "usercontroller.h"
#include "db.h"
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
#include <QStyleFactory>

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

void MainWindow::applyAppStyle()
{
    // Apply Fusion style for a modern look
    qApp->setStyle(QStyleFactory::create("Fusion"));

    // Custom palette for a professional look
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(240, 240, 240));
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, QColor(255, 255, 255));
    palette.setColor(QPalette::AlternateBase, QColor(240, 240, 240));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, QColor(240, 240, 240));
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::HighlightedText, Qt::white);

    qApp->setPalette(palette);

    // Basic stylesheet for button styling
    QString style = R"(
        QPushButton {
            background-color: #f0f0f0;
            border: 1px solid #ccc;
            border-radius: 4px;
            padding: 6px 12px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #e0e0e0;
            border-color: #aaa;
        }

        QPushButton:pressed {
            background-color: #d0d0d0;
        }

        QPushButton:disabled {
            background-color: #f8f8f8;
            color: #aaa;
        }

        QTabWidget::pane {
            border: 1px solid #ccc;
            background: white;
        }

        QTabBar::tab {
            background: #f0f0f0;
            border: 1px solid #ccc;
            padding: 8px 16px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
        }

        QTabBar::tab:selected {
            background: white;
            border-bottom-color: white;
        }

        QTabBar::tab:hover:!selected {
            background: #e8e8e8;
        }

        QTableWidget {
            gridline-color: #ddd;
            alternate-background-color: #f8f8f8;
        }

        QTableWidget::item:selected {
            background-color: #2a82da;
            color: white;
        }

        QHeaderView::section {
            background-color: #f0f0f0;
            padding: 6px;
            border: 1px solid #ddd;
            font-weight: bold;
        }

        QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox {
            border: 1px solid #ccc;
            border-radius: 3px;
            padding: 4px;
            background: white;
        }

        QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus {
            border-color: #2a82da;
        }
    )";

    qApp->setStyleSheet(style);
}

MainWindow::MainWindow(int userId, const QString &username, const QString &role, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_userId(userId), m_username(username), m_role(role)
{
    ui->setupUi(this);

    // Apply application styling
    applyAppStyle();

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
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    // File menu
    QMenu *fileMenu = menuBar->addMenu("&Fichier");

    QAction *exportAction = new QAction("&Exporter", this);
    exportAction->setShortcut(QKeySequence::Save);
    connect(exportAction, &QAction::triggered, [this]() {
        int currentTab = ui->tabWidget->currentIndex();
        switch (currentTab) {
        case 0: // Clients
            m_clientController->exportToExcel();
            break;
        case 1: // Orders
            m_orderController->exportToPdf();
            break;
        case 2: // Users
            QMessageBox::information(this, "Export", "Export des utilisateurs non disponible pour le moment.");
            break;
        }
    });
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
    delete m_clientController;
    delete m_orderController;
    delete m_userController;
    delete ui;
}
