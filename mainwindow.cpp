#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include "db.h"
#include "clientdao.h"
#include "orderdao.h"
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QHeaderView>
#include <QInputDialog>
#include <QTextStream>
#include <QSqlQuery>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>

// User structure
struct User {
    int id = 0;
    QString username;
    QString role;
    QString status;
    QDate created;
};

// User DAO class
class UserDao {
public:
    static bool add(const QString &username, const QString &password, const QString &role) {
        QSqlQuery q(Db::instance().conn());
        q.prepare("INSERT INTO USERS (USERNAME, PASSWORD, ROLE, STATUS) VALUES (:user, :pass, :role, 'ACTIVE')");
        q.bindValue(":user", username);
        q.bindValue(":pass", password);
        q.bindValue(":role", role);
        return q.exec();
    }

    static bool update(int userId, const QString &username, const QString &role, const QString &status) {
        QSqlQuery q(Db::instance().conn());
        q.prepare("UPDATE USERS SET USERNAME = :user, ROLE = :role, STATUS = :status WHERE ID_USER = :id");
        q.bindValue(":user", username);
        q.bindValue(":role", role);
        q.bindValue(":status", status);
        q.bindValue(":id", userId);
        return q.exec();
    }

    static bool updatePassword(int userId, const QString &password) {
        QSqlQuery q(Db::instance().conn());
        q.prepare("UPDATE USERS SET PASSWORD = :pass WHERE ID_USER = :id");
        q.bindValue(":pass", password);
        q.bindValue(":id", userId);
        return q.exec();
    }

    static bool remove(int userId) {
        QSqlQuery q(Db::instance().conn());
        q.prepare("DELETE FROM USERS WHERE ID_USER = :id");
        q.bindValue(":id", userId);
        return q.exec();
    }

    static QVector<User> all() {
        QVector<User> users;
        QSqlQuery q("SELECT ID_USER, USERNAME, ROLE, STATUS, DATE_CREATION FROM USERS ORDER BY ID_USER", Db::instance().conn());
        if (q.exec()) {
            while (q.next()) {
                User u;
                u.id = q.value(0).toInt();
                u.username = q.value(1).toString();
                u.role = q.value(2).toString();
                u.status = q.value(3).toString();
                u.created = q.value(4).toDate();
                users.append(u);
            }
        }
        return users;
    }

    static User getById(int userId) {
        User u;
        QSqlQuery q(Db::instance().conn());
        q.prepare("SELECT ID_USER, USERNAME, ROLE, STATUS, DATE_CREATION FROM USERS WHERE ID_USER = :id");
        q.bindValue(":id", userId);
        if (q.exec() && q.next()) {
            u.id = q.value(0).toInt();
            u.username = q.value(1).toString();
            u.role = q.value(2).toString();
            u.status = q.value(3).toString();
            u.created = q.value(4).toDate();
        }
        return u;
    }
};

bool MainWindow::validateClientForm() {
    if (ui->leNom->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom est obligatoire");
        ui->leNom->setFocus();
        return false;
    }
    if (ui->lePrenom->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le prénom est obligatoire");
        ui->lePrenom->setFocus();
        return false;
    }
    if (!ui->leEmail->text().isEmpty() && !ui->leEmail->text().contains('@')) {
        QMessageBox::warning(this, "Validation", "Email invalide");
        ui->leEmail->setFocus();
        return false;
    }
    return true;
}

bool MainWindow::validateOrderForm() {
    if (ui->cbClient->currentData().toInt() <= 0) {
        QMessageBox::warning(this, "Validation", "Veuillez sélectionner un client");
        ui->cbClient->setFocus();
        return false;
    }
    if (ui->dsMontant->value() <= 0) {
        QMessageBox::warning(this, "Validation", "Le montant doit être positif");
        ui->dsMontant->setFocus();
        return false;
    }
    if (ui->leAdrLiv->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "L'adresse de livraison est obligatoire");
        ui->leAdrLiv->setFocus();
        return false;
    }
    return true;
}

bool MainWindow::validateUserForm() {
    if (ui->leUserUsername->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom d'utilisateur est obligatoire");
        ui->leUserUsername->setFocus();
        return false;
    }
    if (ui->leUserPassword->text().isEmpty() && ui->stackedUser->currentIndex() == 0) {
        QMessageBox::warning(this, "Validation", "Le mot de passe est obligatoire");
        ui->leUserPassword->setFocus();
        return false;
    }
    return true;
}

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

    ui->leSearchClient->setToolTip("Recherche par nom et prénom");
    ui->leEmailFilter->setToolTip("Filtrer par email spécifique");
    ui->leSearchOrder->setToolTip("Recherche par état et adresse");
    ui->dsMinAmount->setToolTip("Montant minimum");
    ui->dsMaxAmount->setToolTip("Montant maximum");
    ui->leSearchUser->setToolTip("Recherche par nom d'utilisateur");

    // wire buttons
    connect(ui->btnAddClient, &QPushButton::clicked, this, &MainWindow::addClient);
    connect(ui->btnUpdClient, &QPushButton::clicked, this, &MainWindow::updClient);
    connect(ui->btnDelClient, &QPushButton::clicked, this, &MainWindow::delClient);
    connect(ui->btnRefClient, &QPushButton::clicked, this, &MainWindow::refClient);

    connect(ui->btnAddOrd, &QPushButton::clicked, this, &MainWindow::addOrder);
    connect(ui->btnUpdOrd, &QPushButton::clicked, this, &MainWindow::updOrder);
    connect(ui->btnDelOrd, &QPushButton::clicked, this, &MainWindow::delOrder);
    connect(ui->btnRefOrd, &QPushButton::clicked, this, &MainWindow::refOrder);
    connect(ui->btnPdfOrd, &QPushButton::clicked, this, &MainWindow::exportOrderPdf);

    connect(ui->btnAddUser, &QPushButton::clicked, this, &MainWindow::addUser);
    connect(ui->btnUpdUser, &QPushButton::clicked, this, &MainWindow::updUser);
    connect(ui->btnDelUser, &QPushButton::clicked, this, &MainWindow::delUser);
    connect(ui->btnRefUser, &QPushButton::clicked, this, &MainWindow::refUser);
    connect(ui->btnChangePassword, &QPushButton::clicked, this, &MainWindow::changeUserPassword);

    connect(ui->leEmailFilter, &QLineEdit::textChanged, this, &MainWindow::applyClientFilters);
    connect(ui->cbClientFilter, &QComboBox::currentTextChanged, this, &MainWindow::applyOrderFilters);
    connect(ui->dsMinAmount, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::applyOrderFilters);
    connect(ui->dsMaxAmount, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::applyOrderFilters);
    connect(ui->leSearchUser, &QLineEdit::textChanged, this, &MainWindow::applyUserFilters);
    connect(ui->cbUserRoleFilter, &QComboBox::currentTextChanged, this, &MainWindow::applyUserFilters);
    connect(ui->cbUserStatusFilter, &QComboBox::currentTextChanged, this, &MainWindow::applyUserFilters);

    // Connect business function buttons
    connect(ui->btnClientStats, &QPushButton::clicked, this, &MainWindow::showClientStats);
    connect(ui->btnOrderStats, &QPushButton::clicked, this, &MainWindow::showOrderStats);
    connect(ui->btnExportExcel, &QPushButton::clicked, this, &MainWindow::exportClientsExcel);
    connect(ui->btnUpdateCategory, &QPushButton::clicked, this, &MainWindow::updateClientCategory);
    connect(ui->btnUpdatePriority, &QPushButton::clicked, this, &MainWindow::updateOrderPriority);

    // Connect tab changes
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // Connect selection changes
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

    // initial load
    loadClientsTable();
    loadClientsCombo();
    loadClientFilterCombo();
    loadOrdersTable();
    loadUsersTable();

    // setup charts containers with QtCharts
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

    // wire filters
    connect(ui->leSearchClient, &QLineEdit::textChanged, this, &MainWindow::applyClientFilters);
    connect(ui->cbStatutFilter, &QComboBox::currentTextChanged, this, &MainWindow::applyClientFilters);
    connect(ui->cbClientSort, &QComboBox::currentTextChanged, this, &MainWindow::applyClientFilters);
    connect(ui->leSearchOrder, &QLineEdit::textChanged, this, &MainWindow::applyOrderFilters);
    connect(ui->cbEtatFilter, &QComboBox::currentTextChanged, this, &MainWindow::applyOrderFilters);
    connect(ui->cbOrderSort, &QComboBox::currentTextChanged, this, &MainWindow::applyOrderFilters);

    updateClientChart();
    updateOrderChart();
    updateUserChart();
}

MainWindow::~MainWindow() { delete ui; }

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
        refClient();
    } else if (index == 1) { // Orders tab
        refOrder();
    } else if (index == 2) { // Users tab
        refUser();
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
        this->close();
    }
}

// ===== Clients
void MainWindow::addClient() {
    if (!validateClientForm()) return;

    ClientDao dao;
    Client c;
    c.nom = ui->leNom->text();
    c.prenom = ui->lePrenom->text();
    c.tel = ui->leTel->text();
    c.email = ui->leEmail->text();
    c.adr = ui->leAdr->text();
    c.statut = ui->cbStatut->currentText();
    c.category = "REGULAR";
    if (!dao.add(c)) {
        QMessageBox::warning(this, "Client", "Échec de l'ajout: " + Db::instance().lastError());
    }
    refClient();
}

void MainWindow::updClient() {
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Client", "Veuillez sélectionner un client à modifier");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

    ClientDao dao;
    auto clientOpt = dao.byId(id);
    if (!clientOpt.has_value()) {
        QMessageBox::warning(this, "Client", "Client non trouvé");
        return;
    }

    Client c = clientOpt.value();
    c.nom = ui->leNom->text();
    c.prenom = ui->lePrenom->text();
    c.tel = ui->leTel->text();
    c.email = ui->leEmail->text();
    c.adr = ui->leAdr->text();
    c.statut = ui->cbStatut->currentText();

    if (!dao.upd(c)) {
        QMessageBox::warning(this, "Client", "Échec de la modification: " + Db::instance().lastError());
    } else {
        QMessageBox::information(this, "Client", "Client modifié avec succès");
        refClient();
    }
}

void MainWindow::delClient() {
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

    ClientDao dao;
    if (!dao.del(id)) {
        QMessageBox::warning(this, "Client", "Échec de la suppression: " + Db::instance().lastError());
    }
    refClient();
}

void MainWindow::refClient() {
    loadClientsTable();
    loadClientsCombo();
    loadClientFilterCombo();
}

// ===== Orders
void MainWindow::addOrder() {
    if (!validateOrderForm()) return;

    OrderDao dao;
    Order o;
    o.clientId = ui->cbClient->currentData().toInt();
    o.etat = ui->cbEtat->currentText();
    o.montant = ui->dsMontant->value();
    o.adrLiv = ui->leAdrLiv->text();
    o.priority = ui->cbPriority->currentText();
    if (!dao.add(o)) {
        QMessageBox::warning(this, "Commande", "Échec de l'ajout: " + Db::instance().lastError());
    }
    refOrder();
}

void MainWindow::updOrder() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Commande", "Veuillez sélectionner une commande à modifier");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();

    OrderDao dao;
    auto orderOpt = dao.byId(id);
    if (!orderOpt.has_value()) {
        QMessageBox::warning(this, "Commande", "Commande non trouvée");
        return;
    }

    Order o = orderOpt.value();
    o.clientId = ui->cbClient->currentData().toInt();
    o.etat = ui->cbEtat->currentText();
    o.montant = ui->dsMontant->value();
    o.adrLiv = ui->leAdrLiv->text();
    o.priority = ui->cbPriority->currentText();

    if (!dao.upd(o)) {
        QMessageBox::warning(this, "Commande", "Échec de la modification: " + Db::instance().lastError());
    } else {
        QMessageBox::information(this, "Commande", "Commande modifiée avec succès");
        refOrder();
    }
}

void MainWindow::delOrder() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();

    OrderDao dao;
    if (!dao.del(id)) {
        QMessageBox::warning(this, "Commande", "Échec de la suppression: " + Db::instance().lastError());
    }
    refOrder();
}

void MainWindow::refOrder() {
    loadOrdersTable();
}

// ===== Users
void MainWindow::addUser() {
    if (!validateUserForm()) return;

    QString username = ui->leUserUsername->text();
    QString password = ui->leUserPassword->text();
    QString role = ui->cbUserRole->currentText().toUpper();

    if (UserDao::add(username, password, role)) {
        QMessageBox::information(this, "Utilisateur", "Utilisateur ajouté avec succès");
        // Clear form and switch to view mode
        ui->leUserUsername->clear();
        ui->leUserPassword->clear();
        ui->cbUserRole->setCurrentIndex(0);
        ui->stackedUser->setCurrentIndex(0);
        refUser();
    } else {
        QMessageBox::warning(this, "Utilisateur", "Échec de l'ajout: " + Db::instance().lastError());
    }
}

void MainWindow::updUser() {
    auto items = ui->tblUsers->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Utilisateur", "Veuillez sélectionner un utilisateur à modifier");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblUsers->item(row, 0)->text().toInt();

    QString username = ui->leUserUsername->text();
    QString role = ui->cbUserRole->currentText().toUpper();
    QString status = ui->cbUserStatus->currentText();

    if (UserDao::update(id, username, role, status)) {
        QMessageBox::information(this, "Utilisateur", "Utilisateur modifié avec succès");
        // Switch back to view mode
        ui->stackedUser->setCurrentIndex(0);
        refUser();
    } else {
        QMessageBox::warning(this, "Utilisateur", "Échec de la modification: " + Db::instance().lastError());
    }
}

void MainWindow::delUser() {
    auto items = ui->tblUsers->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Utilisateur", "Veuillez sélectionner un utilisateur à supprimer");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblUsers->item(row, 0)->text().toInt();
    QString username = ui->tblUsers->item(row, 1)->text();

    // Prevent self-deletion
    if (id == m_userId) {
        QMessageBox::warning(this, "Utilisateur", "Vous ne pouvez pas supprimer votre propre compte");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  QString("Êtes-vous sûr de vouloir supprimer l'utilisateur %1?").arg(username),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (UserDao::remove(id)) {
            QMessageBox::information(this, "Utilisateur", "Utilisateur supprimé avec succès");
            refUser();
        } else {
            QMessageBox::warning(this, "Utilisateur", "Échec de la suppression: " + Db::instance().lastError());
        }
    }
}

void MainWindow::refUser() {
    loadUsersTable();
}

void MainWindow::changeUserPassword() {
    auto items = ui->tblUsers->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Utilisateur", "Veuillez sélectionner un utilisateur");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblUsers->item(row, 0)->text().toInt();
    QString username = ui->tblUsers->item(row, 1)->text();

    QString password = QInputDialog::getText(this, "Changer le mot de passe",
                                             QString("Nouveau mot de passe pour %1:").arg(username),
                                             QLineEdit::Password);

    if (password.isEmpty()) {
        return;
    }

    if (UserDao::updatePassword(id, password)) {
        QMessageBox::information(this, "Utilisateur", "Mot de passe changé avec succès");
    } else {
        QMessageBox::warning(this, "Utilisateur", "Échec du changement de mot de passe: " + Db::instance().lastError());
    }
}

// ===== loads
void MainWindow::loadClientsTable() {
    ClientDao dao;
    auto v = dao.all();
    ui->tblClients->clearContents();
    ui->tblClients->setRowCount(v.size());
    ui->tblClients->setColumnCount(9);
    QStringList headers = {"ID","Nom","Prénom","Tel","Email","Adresse","Statut","Créé","Catégorie"};
    ui->tblClients->setHorizontalHeaderLabels(headers);
    ui->tblClients->horizontalHeader()->setStretchLastSection(true);
    for (int i=0;i<v.size();++i) {
        const auto &c = v[i];
        ui->tblClients->setItem(i,0,new QTableWidgetItem(QString::number(c.id)));
        ui->tblClients->setItem(i,1,new QTableWidgetItem(c.nom));
        ui->tblClients->setItem(i,2,new QTableWidgetItem(c.prenom));
        ui->tblClients->setItem(i,3,new QTableWidgetItem(c.tel));
        ui->tblClients->setItem(i,4,new QTableWidgetItem(c.email));
        ui->tblClients->setItem(i,5,new QTableWidgetItem(c.adr));
        ui->tblClients->setItem(i,6,new QTableWidgetItem(c.statut));
        ui->tblClients->setItem(i,7,new QTableWidgetItem(c.created.toString("yyyy-MM-dd")));
        ui->tblClients->setItem(i,8,new QTableWidgetItem(c.category));
        QTableWidgetItem *categoryItem = new QTableWidgetItem(c.category);
        if (c.category == "PLATINUM") {
            categoryItem->setBackground(QColor("#E5E4E2")); // Platinum color
        } else if (c.category == "GOLD") {
            categoryItem->setBackground(QColor("#FFD700")); // Gold color
        } else if (c.category == "SILVER") {
            categoryItem->setBackground(QColor("#C0C0C0")); // Silver color
        }
        ui->tblClients->setItem(i,8,categoryItem);
    }
    applyClientFilters();
    updateClientChart();
}

void MainWindow::loadOrdersTable() {
    OrderDao dao;
    auto v = dao.all();
    ui->tblOrders->clearContents();
    ui->tblOrders->setRowCount(v.size());
    ui->tblOrders->setColumnCount(8);
    QStringList headers = {"ID","Client ID","Date","État","Montant","Adresse Livraison","Priorité","Livraison Estimée"};
    ui->tblOrders->setHorizontalHeaderLabels(headers);
    ui->tblOrders->horizontalHeader()->setStretchLastSection(true);
    for (int i=0;i<v.size();++i) {
        const auto &o = v[i];
        ui->tblOrders->setItem(i,0,new QTableWidgetItem(QString::number(o.id)));
        ui->tblOrders->setItem(i,1,new QTableWidgetItem(QString::number(o.clientId)));
        ui->tblOrders->setItem(i,2,new QTableWidgetItem(o.date.toString("yyyy-MM-dd")));
        ui->tblOrders->setItem(i,3,new QTableWidgetItem(o.etat));
        ui->tblOrders->setItem(i,4,new QTableWidgetItem(QString::number(o.montant, 'f', 3)));
        ui->tblOrders->setItem(i,5,new QTableWidgetItem(o.adrLiv));
        ui->tblOrders->setItem(i,6,new QTableWidgetItem(o.priority));
        ui->tblOrders->setItem(i,7,new QTableWidgetItem(o.estimatedDelivery.toString("yyyy-MM-dd")));
    }
    applyOrderFilters();
    updateOrderChart();
}

void MainWindow::loadUsersTable() {
    auto users = UserDao::all();
    ui->tblUsers->clearContents();
    ui->tblUsers->setRowCount(users.size());
    ui->tblUsers->setColumnCount(5);
    QStringList headers = {"ID","Nom d'utilisateur","Rôle","Statut","Date création"};
    ui->tblUsers->setHorizontalHeaderLabels(headers);
    ui->tblUsers->horizontalHeader()->setStretchLastSection(true);

    for (int i = 0; i < users.size(); ++i) {
        const auto &u = users[i];
        ui->tblUsers->setItem(i, 0, new QTableWidgetItem(QString::number(u.id)));
        ui->tblUsers->setItem(i, 1, new QTableWidgetItem(u.username));
        ui->tblUsers->setItem(i, 2, new QTableWidgetItem(u.role));
        ui->tblUsers->setItem(i, 3, new QTableWidgetItem(u.status));
        ui->tblUsers->setItem(i, 4, new QTableWidgetItem(u.created.toString("yyyy-MM-dd")));

        // Color code based on status
        QTableWidgetItem *statusItem = new QTableWidgetItem(u.status);
        if (u.status == "ACTIVE") {
            statusItem->setBackground(QColor("#d4edda")); // Light green
            statusItem->setForeground(QColor("#155724")); // Dark green
        } else {
            statusItem->setBackground(QColor("#f8d7da")); // Light red
            statusItem->setForeground(QColor("#721c24")); // Dark red
        }
        ui->tblUsers->setItem(i, 3, statusItem);
    }
    applyUserFilters();
    updateUserChart();
}

void MainWindow::loadClientsCombo() {
    ClientDao dao;
    auto v = dao.all();
    ui->cbClient->clear();
    for (const auto& c: v) {
        ui->cbClient->addItem(QString("%1 %2").arg(c.nom, c.prenom), c.id);
    }
}

void MainWindow::loadClientFilterCombo() {
    ClientDao dao;
    auto v = dao.all();
    ui->cbClientFilter->clear();
    ui->cbClientFilter->addItem("Tous les clients", -1);
    for (const auto& c: v) {
        ui->cbClientFilter->addItem(QString("%1 %2").arg(c.nom, c.prenom), c.id);
    }
}

void MainWindow::exportOrderPdf() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "PDF", "Veuillez sélectionner une commande.");
        return;
    }
    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();

    OrderDao dao;
    auto orderOpt = dao.byId(id);
    if (!orderOpt.has_value()) {
        QMessageBox::warning(this, "PDF", "Commande introuvable.");
        return;
    }
    Order o = orderOpt.value();

    QString defaultName = QString("commande_%1.pdf").arg(o.id);
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", defaultName, "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "PDF", "Impossible de créer le PDF.");
        return;
    }

    int x = 500;
    int y = 500;
    int line = 400;

    QFont titleFont = painter.font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(x, y, QString("Commande #%1").arg(o.id));
    y += line * 2;

    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);
    painter.setFont(bodyFont);

    painter.drawText(x, y, QString("Date: %1").arg(o.date.toString("yyyy-MM-dd"))); y += line;
    painter.drawText(x, y, QString("Client ID: %1").arg(o.clientId)); y += line;
    painter.drawText(x, y, QString("État: %1").arg(o.etat)); y += line;
    painter.drawText(x, y, QString("Montant: %1 DT").arg(QString::number(o.montant, 'f', 3))); y += line;
    painter.drawText(x, y, QString("Adresse de livraison: %1").arg(o.adrLiv)); y += line;
    painter.drawText(x, y, QString("Priorité: %1").arg(o.priority)); y += line;
    if (o.estimatedDelivery.isValid()) {
        painter.drawText(x, y, QString("Livraison estimée: %1").arg(o.estimatedDelivery.toString("yyyy-MM-dd"))); y += line;
    }

    painter.end();
    QMessageBox::information(this, "PDF", "PDF généré avec succès.");
}

void MainWindow::applyClientFilters() {
    QString text = ui->leSearchClient->text().trimmed();
    QString emailFilter = ui->leEmailFilter->text().trimmed();
    QString statut = ui->cbStatutFilter->currentText();
    QString sortKey = ui->cbClientSort->currentText();

    for (int r=0; r<ui->tblClients->rowCount(); ++r) ui->tblClients->setRowHidden(r, false);

    for (int r=0; r<ui->tblClients->rowCount(); ++r) {
        bool match = true;

        // Name search (nom, prénom)
        if (!text.isEmpty()) {
            QString rowText = ui->tblClients->item(r,1)->text() + " " + ui->tblClients->item(r,2)->text();
            match &= rowText.contains(text, Qt::CaseInsensitive);
        }

        // Email filter
        if (!emailFilter.isEmpty()) {
            QString email = ui->tblClients->item(r,4)->text();
            match &= email.contains(emailFilter, Qt::CaseInsensitive);
        }

        // Status filter
        if (statut != "Tous") {
            match &= ui->tblClients->item(r,6)->text() == statut;
        }

        if (!match) ui->tblClients->setRowHidden(r, true);
    }

    if (sortKey == "Nom") ui->tblClients->sortItems(1);
    else if (sortKey == "Prénom") ui->tblClients->sortItems(2);
    else if (sortKey == "Créé") ui->tblClients->sortItems(7);
}

void MainWindow::applyOrderFilters() {
    QString text = ui->leSearchOrder->text().trimmed();
    int clientId = ui->cbClientFilter->currentData().toInt();
    QString etat = ui->cbEtatFilter->currentText();
    double minAmount = ui->dsMinAmount->value();
    double maxAmount = ui->dsMaxAmount->value();
    QString sortKey = ui->cbOrderSort->currentText();

    for (int r=0; r<ui->tblOrders->rowCount(); ++r) ui->tblOrders->setRowHidden(r, false);

    for (int r=0; r<ui->tblOrders->rowCount(); ++r) {
        bool match = true;

        // Text search (état, adresse)
        if (!text.isEmpty()) {
            QString rowText = ui->tblOrders->item(r,3)->text() + " " + ui->tblOrders->item(r,5)->text();
            match &= rowText.contains(text, Qt::CaseInsensitive);
        }

        // Client filter
        if (clientId > 0) {
            int rowClientId = ui->tblOrders->item(r,1)->text().toInt();
            match &= (rowClientId == clientId);
        }

        // Status filter
        if (etat != "Tous") {
            match &= ui->tblOrders->item(r,3)->text() == etat;
        }

        // Amount range filter
        double amount = ui->tblOrders->item(r,4)->text().toDouble();
        if (minAmount > 0) match &= (amount >= minAmount);
        if (maxAmount > 0) match &= (amount <= maxAmount);

        if (!match) ui->tblOrders->setRowHidden(r, true);
    }

    if (sortKey == "Date") ui->tblOrders->sortItems(2);
    else if (sortKey == "Montant") ui->tblOrders->sortItems(4);
    else if (sortKey == "État") ui->tblOrders->sortItems(3);
}

void MainWindow::applyUserFilters() {
    QString text = ui->leSearchUser->text().trimmed();
    QString roleFilter = ui->cbUserRoleFilter->currentText();
    QString statusFilter = ui->cbUserStatusFilter->currentText();
    QString sortKey = ui->cbUserSort->currentText();

    for (int r=0; r<ui->tblUsers->rowCount(); ++r) ui->tblUsers->setRowHidden(r, false);

    for (int r=0; r<ui->tblUsers->rowCount(); ++r) {
        bool match = true;

        // Username search
        if (!text.isEmpty()) {
            QString username = ui->tblUsers->item(r,1)->text();
            match &= username.contains(text, Qt::CaseInsensitive);
        }

        // Role filter
        if (roleFilter != "Tous") {
            match &= ui->tblUsers->item(r,2)->text() == roleFilter;
        }

        // Status filter
        if (statusFilter != "Tous") {
            match &= ui->tblUsers->item(r,3)->text() == statusFilter;
        }

        if (!match) ui->tblUsers->setRowHidden(r, true);
    }

    if (sortKey == "Nom d'utilisateur") ui->tblUsers->sortItems(1);
    else if (sortKey == "Rôle") ui->tblUsers->sortItems(2);
    else if (sortKey == "Statut") ui->tblUsers->sortItems(3);
    else if (sortKey == "Date création") ui->tblUsers->sortItems(4);
}

void MainWindow::autoCategorizeClients() {
    ClientDao dao;
    if (dao.autoCategorizeClients()) {
        QMessageBox::information(this, "Catégorisation", "Clients catégorisés automatiquement avec succès");
        refClient();
    } else {
        QMessageBox::warning(this, "Catégorisation", "Échec de la catégorisation automatique");
    }
}

void MainWindow::updateClientChart() {
    if (!clientChartView) return;

    ClientDao dao;
    auto clients = dao.all();

    QMap<QString, int> counts;
    counts["ACTIVE"] = 0;
    counts["INACTIVE"] = 0;

    for (const auto &client : clients) {
        counts[client.statut]++;
    }

    QPieSeries *series = new QPieSeries();
    if (counts["ACTIVE"] > 0) series->append("Actif", counts["ACTIVE"]);
    if (counts["INACTIVE"] > 0) series->append("Inactif", counts["INACTIVE"]);

    if (series->slices().count() > 0) {
        series->slices().at(0)->setColor(QColor("#4caf50"));
        if (series->slices().count() > 1) {
            series->slices().at(1)->setColor(QColor("#f44336"));
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par statut");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    clientChartView->setChart(chart);
}

void MainWindow::updateOrderChart() {
    if (!orderChartView) return;

    OrderDao dao;
    auto statusCounts = dao.getOrdersByStatus();

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Commandes");

    QStringList categories;
    for (const auto &pair : statusCounts) {
        *set << pair.second;
        categories << pair.first;
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Commandes par état");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    orderChartView->setChart(chart);
}

void MainWindow::updateUserChart() {
    if (!userChartView) return;

    auto users = UserDao::all();

    QMap<QString, int> roleCounts;
    QMap<QString, int> statusCounts;

    for (const auto &user : users) {
        roleCounts[user.role]++;
        statusCounts[user.status]++;
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = roleCounts.begin(); it != roleCounts.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des utilisateurs par rôle");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    userChartView->setChart(chart);
}


void MainWindow::showClientStats() {
    ClientDao dao;
    auto topClients = dao.getTopClients(5);

    QString message = "Statistiques clients:\n\n";
    message += "Top 5 clients par nombre de commandes:\n";

    for (const auto &client : topClients) {
        message += QString("%1 %2: %3 commandes\n")
        .arg(client.nom)
            .arg(client.prenom)
            .arg(client.totalOrders);
    }

    QMessageBox::information(this, "Statistiques Clients", message);
}

void MainWindow::showOrderStats() {
    OrderDao dao;
    double totalRevenue = dao.getTotalRevenue();
    auto statusCounts = dao.getOrdersByStatus();

    QString message = "Statistiques commandes:\n\n";
    message += QString("Revenu total: %1 DT\n").arg(totalRevenue, 0, 'f', 3);
    message += "Commandes par état:\n";

    for (const auto &pair : statusCounts) {
        message += QString("%1: %2 commandes\n").arg(pair.first).arg(pair.second);
    }

    QMessageBox::information(this, "Statistiques Commandes", message);
}

void MainWindow::exportClientsExcel() {
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter clients", "clients.csv", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Export", "Impossible de créer le fichier");
        return;
    }

    QTextStream stream(&file);
    stream << "ID,Nom,Prénom,Téléphone,Email,Adresse,Statut,Date création,Catégorie\n";

    ClientDao dao;
    auto clients = dao.all();

    for (const auto &client : clients) {
        stream << client.id << ","
               << client.nom << ","
               << client.prenom << ","
               << client.tel << ","
               << client.email << ","
               << client.adr << ","
               << client.statut << ","
               << client.created.toString("yyyy-MM-dd") << ","
               << client.category << "\n";
    }

    file.close();
    QMessageBox::information(this, "Export", "Clients exportés avec succès");
}

void MainWindow::updateClientCategory() {
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Catégorie", "Veuillez sélectionner un client");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

    QStringList categories = {"REGULAR", "SILVER", "GOLD", "PLATINUM"};
    QString category = QInputDialog::getItem(this, "Catégorie client",
                                             "Sélectionnez la catégorie:", categories, 0, false);

    if (category.isEmpty()) return;

    ClientDao dao;
    if (dao.updateClientCategory(id, category)) {
        QMessageBox::information(this, "Catégorie", "Catégorie mise à jour avec succès");
        refClient();
    } else {
        QMessageBox::warning(this, "Catégorie", "Échec de la mise à jour");
    }
}

void MainWindow::updateOrderPriority() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Priorité", "Veuillez sélectionner une commande");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();

    QStringList priorities = {"LOW", "NORMAL", "HIGH", "URGENT"};
    QString priority = QInputDialog::getItem(this, "Priorité commande",
                                             "Sélectionnez la priorité:", priorities, 1, false);

    if (priority.isEmpty()) return;

    OrderDao dao;
    if (dao.updateOrderPriority(id, priority)) {
        QMessageBox::information(this, "Priorité", "Priorité mise à jour avec succès");
        refOrder();
    } else {
        QMessageBox::warning(this, "Priorité", "Échec de la mise à jour");
    }
}
