#include "usercontroller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QColor>
#include <QtCharts>

UserController::UserController(MainWindow* mainWindow, QObject* parent)
    : QObject(parent), m_mainWindow(mainWindow)
{}

UserController::~UserController() {}

void UserController::setupUi() {
    Ui::MainWindow* ui = m_mainWindow->getUi();

    // Connect user-related buttons
    connect(ui->btnAddUser, &QPushButton::clicked, this, &UserController::switchToEditMode);
    connect(ui->btnUpdUser, &QPushButton::clicked, this, &UserController::updateUser);
    connect(ui->btnDelUser, &QPushButton::clicked, this, &UserController::deleteUser);
    connect(ui->btnRefUser, &QPushButton::clicked, this, &UserController::refreshUsers);
    connect(ui->btnChangePassword, &QPushButton::clicked, this, &UserController::changePassword);
    connect(ui->btnCancelUser, &QPushButton::clicked, this, &UserController::cancelEdit);

    // Connect filter signals
    connect(ui->leSearchUser, &QLineEdit::textChanged, this, &UserController::applyFilters);
    connect(ui->cbUserRoleFilter, &QComboBox::currentTextChanged, this, &UserController::applyFilters);
    connect(ui->cbUserStatusFilter, &QComboBox::currentTextChanged, this, &UserController::applyFilters);
    connect(ui->cbUserSort, &QComboBox::currentTextChanged, this, &UserController::applyFilters);

    // Connect table selection changed
    connect(ui->tblUsers, &QTableWidget::itemSelectionChanged, this, &UserController::onUserTableSelectionChanged);

    // Set tooltips
    ui->leSearchUser->setToolTip("Recherche par nom d'utilisateur");
}

void UserController::onUserTableSelectionChanged() {
    if (!m_isEditMode) {
        populateFormWithSelectedUser();
    }
}

void UserController::populateFormWithSelectedUser() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblUsers->selectedItems();

    if (items.isEmpty()) {
        m_selectedUserId = -1;
        return;
    }

    int row = items.first()->row();
    int id = ui->tblUsers->item(row, 0)->text().toInt();
    m_selectedUserId = id;
}

void UserController::switchToEditMode() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    ui->stackedUser->setCurrentIndex(1); // Switch to edit mode

    if (m_selectedUserId == -1) {
        // New user mode
        ui->leUserUsername->clear();
        ui->leUserPassword->clear();
        ui->cbUserRole->setCurrentIndex(0);
        ui->cbUserStatus->setCurrentIndex(0);
        m_isEditMode = false;
    } else {
        // Edit existing user mode
        auto userOpt = m_dao.getById(m_selectedUserId);
        if (userOpt.has_value()) {
            User u = userOpt.value();
            ui->leUserUsername->setText(u.username);
            ui->leUserPassword->clear(); // Don't show password
            ui->cbUserRole->setCurrentText(u.role);
            ui->cbUserStatus->setCurrentText(u.status);
        }
        m_isEditMode = true;
    }

    ui->leUserUsername->setFocus();
}

void UserController::addUser() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (!validateForm(true)) return;

    User u;
    u.username = ui->leUserUsername->text();
    u.password = ui->leUserPassword->text();
    u.role = ui->cbUserRole->currentText();
    u.status = ui->cbUserStatus->currentText();

    if (m_dao.add(u)) {
        QMessageBox::information(m_mainWindow, "Utilisateur", "Utilisateur ajouté avec succès");
        // Clear form and switch to view mode
        ui->leUserUsername->clear();
        ui->leUserPassword->clear();
        ui->cbUserRole->setCurrentIndex(0);
        ui->cbUserStatus->setCurrentIndex(0);
        ui->stackedUser->setCurrentIndex(0); // Switch to view mode
        refreshUsers();
    } else {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Échec de l'ajout: " + Db::instance().lastError());
    }
}

void UserController::updateUser() {
    if (m_selectedUserId == -1) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Veuillez sélectionner un utilisateur à modifier");
        return;
    }

    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (!validateForm(false)) return;

    QString username = ui->leUserUsername->text();
    QString password = ui->leUserPassword->text();
    QString role = ui->cbUserRole->currentText();
    QString status = ui->cbUserStatus->currentText();

    // If password is empty, don't update it
    bool success;
    if (password.isEmpty()) {
        success = m_dao.updateWithoutPassword(m_selectedUserId, username, role, status);
    } else {
        User u;
        u.id = m_selectedUserId;
        u.username = username;
        u.password = password;
        u.role = role;
        u.status = status;
        success = m_dao.update(u);
    }

    if (success) {
        QMessageBox::information(m_mainWindow, "Utilisateur", "Utilisateur modifié avec succès");
        // Clear form and switch to view mode
        ui->leUserUsername->clear();
        ui->leUserPassword->clear();
        ui->cbUserRole->setCurrentIndex(0);
        ui->cbUserStatus->setCurrentIndex(0);
        ui->stackedUser->setCurrentIndex(0);
        refreshUsers();
    } else {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Échec de la modification: " + Db::instance().lastError());
    }
}

void UserController::deleteUser() {
    if (m_selectedUserId == -1) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Veuillez sélectionner un utilisateur à supprimer");
        return;
    }

    auto userOpt = m_dao.getById(m_selectedUserId);
    if (!userOpt.has_value()) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Utilisateur non trouvé");
        return;
    }

    User u = userOpt.value();

    // Prevent self-deletion
    if (u.id == m_mainWindow->getUserId()) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Vous ne pouvez pas supprimer votre propre compte");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(m_mainWindow, "Confirmation",
                                  QString("Êtes-vous sûr de vouloir supprimer l'utilisateur %1?").arg(u.username),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_dao.remove(m_selectedUserId)) {
            QMessageBox::information(m_mainWindow, "Utilisateur", "Utilisateur supprimé avec succès");
            refreshUsers();
        } else {
            QMessageBox::warning(m_mainWindow, "Utilisateur", "Échec de la suppression: " + Db::instance().lastError());
        }
    }
}

void UserController::refreshUsers() {
    loadUsersTable();
}

void UserController::changePassword() {
    if (m_selectedUserId == -1) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Veuillez sélectionner un utilisateur");
        return;
    }

    auto userOpt = m_dao.getById(m_selectedUserId);
    if (!userOpt.has_value()) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Utilisateur non trouvé");
        return;
    }

    User u = userOpt.value();

    QString password = QInputDialog::getText(m_mainWindow, "Changer le mot de passe",
                                             QString("Nouveau mot de passe pour %1:").arg(u.username),
                                             QLineEdit::Password);

    if (password.isEmpty()) {
        return;
    }

    if (password.length() < 6) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le mot de passe doit contenir au moins 6 caractères");
        return;
    }

    if (m_dao.updatePassword(m_selectedUserId, password)) {
        QMessageBox::information(m_mainWindow, "Utilisateur", "Mot de passe changé avec succès");
    } else {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Échec du changement de mot de passe: " + Db::instance().lastError());
    }
}

void UserController::cancelEdit() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    ui->stackedUser->setCurrentIndex(0); // Switch back to view mode
    m_isEditMode = false;
}

void UserController::loadUsersTable() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto users = m_dao.getAll();

    ui->tblUsers->clearContents();
    ui->tblUsers->setRowCount(users.size());
    ui->tblUsers->setColumnCount(5);

    QStringList headers = {"ID", "Nom d'utilisateur", "Rôle", "Statut", "Date création"};
    ui->tblUsers->setHorizontalHeaderLabels(headers);
    ui->tblUsers->horizontalHeader()->setStretchLastSection(true);
    ui->tblUsers->setAlternatingRowColors(true);
    ui->tblUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblUsers->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < users.size(); ++i) {
        const auto &u = users[i];

        ui->tblUsers->setItem(i, 0, new QTableWidgetItem(QString::number(u.id)));
        ui->tblUsers->setItem(i, 1, new QTableWidgetItem(u.username));
        ui->tblUsers->setItem(i, 2, new QTableWidgetItem(u.roleText()));
        ui->tblUsers->setItem(i, 3, new QTableWidgetItem(u.statusText()));
        ui->tblUsers->setItem(i, 4, new QTableWidgetItem(u.created.toString("yyyy-MM-dd")));

        // Color code based on status
        QTableWidgetItem *statusItem = ui->tblUsers->item(i, 3);
        if (u.status == "ACTIVE") {
            statusItem->setBackground(QColor("#d4edda")); // Light green
            statusItem->setForeground(QColor("#155724")); // Dark green
        } else {
            statusItem->setBackground(QColor("#f8d7da")); // Light red
            statusItem->setForeground(QColor("#721c24")); // Dark red
        }

        // Color code based on role
        QTableWidgetItem *roleItem = ui->tblUsers->item(i, 2);
        if (u.role == "ADMIN") {
            roleItem->setBackground(QColor("#d1ecf1")); // Light blue
            roleItem->setForeground(QColor("#0c5460")); // Dark blue
        } else if (u.role == "MANAGER") {
            roleItem->setBackground(QColor("#fff3cd")); // Light yellow
            roleItem->setForeground(QColor("#856404")); // Dark yellow
        }
    }

    applyFilters();
    updateChart();
}

void UserController::applyFilters() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    QString text = ui->leSearchUser->text().trimmed();
    QString roleFilter = ui->cbUserRoleFilter->currentText();
    QString statusFilter = ui->cbUserStatusFilter->currentText();
    QString sortKey = ui->cbUserSort->currentText();

    for (int r = 0; r < ui->tblUsers->rowCount(); ++r) {
        ui->tblUsers->setRowHidden(r, false);
    }

    for (int r = 0; r < ui->tblUsers->rowCount(); ++r) {
        bool match = true;

        // Username search
        if (!text.isEmpty()) {
            QString username = ui->tblUsers->item(r, 1)->text();
            match &= username.contains(text, Qt::CaseInsensitive);
        }

        // Role filter
        if (roleFilter != "Tous les rôles") {
            QString role = ui->tblUsers->item(r, 2)->text();
            match &= (role == roleFilter);
        }

        // Status filter
        if (statusFilter != "Tous les statuts") {
            QString status = ui->tblUsers->item(r, 3)->text();
            match &= (status == statusFilter);
        }

        if (!match) {
            ui->tblUsers->setRowHidden(r, true);
        }
    }

    if (sortKey == "Nom d'utilisateur") {
        ui->tblUsers->sortItems(1);
    } else if (sortKey == "Rôle") {
        ui->tblUsers->sortItems(2);
    } else if (sortKey == "Statut") {
        ui->tblUsers->sortItems(3);
    } else if (sortKey == "Date création") {
        ui->tblUsers->sortItems(4);
    }
}

void UserController::updateChart() {
    QChartView* userChartView = m_mainWindow->userChartView;
    if (!userChartView) return;

    auto roleCounts = m_dao.getUsersByRole();

    QPieSeries *series = new QPieSeries();
    for (const auto &pair : roleCounts) {
        QString roleName;
        if (pair.first == "ADMIN") roleName = "Administrateurs";
        else if (pair.first == "MANAGER") roleName = "Gestionnaires";
        else if (pair.first == "DELIVERY") roleName = "Livreurs";
        else roleName = pair.first;

        series->append(roleName, pair.second);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des utilisateurs par rôle");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    userChartView->setChart(chart);
}

bool UserController::validateForm(bool isNewUser) {
    Ui::MainWindow* ui = m_mainWindow->getUi();

    if (ui->leUserUsername->text().isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le nom d'utilisateur est obligatoire");
        ui->leUserUsername->setFocus();
        return false;
    }

    if (isNewUser && ui->leUserPassword->text().isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le mot de passe est obligatoire");
        ui->leUserPassword->setFocus();
        return false;
    }

    if (isNewUser && ui->leUserPassword->text().length() < 6) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le mot de passe doit contenir au moins 6 caractères");
        ui->leUserPassword->setFocus();
        return false;
    }

    // Check if username already exists (for new users)
    if (isNewUser && m_dao.usernameExists(ui->leUserUsername->text())) {
        QMessageBox::warning(m_mainWindow, "Validation", "Ce nom d'utilisateur existe déjà");
        ui->leUserUsername->setFocus();
        return false;
    }

    return true;
}
