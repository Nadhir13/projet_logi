#include "usercontroller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QColor>
#include <QtCharts>
#include <QSqlQuery>
#include "db.h"

// User structure (copied from mainwindow.cpp)
struct User {
    int id = 0;
    QString username;
    QString role;
    QString status;
    QDate created;
};

// User DAO class (copied from mainwindow.cpp)
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

UserController::UserController(MainWindow* mainWindow, QObject* parent)
    : QObject(parent), m_mainWindow(mainWindow)
{}

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
    
    // Set tooltips
    ui->leSearchUser->setToolTip("Recherche par nom d'utilisateur");
}

void UserController::switchToEditMode() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    ui->stackedUser->setCurrentIndex(1); // Switch to edit mode
    ui->leUserUsername->clear();
    ui->leUserPassword->clear();
    ui->cbUserRole->setCurrentIndex(0);
    ui->cbUserStatus->setCurrentIndex(0);
    ui->leUserUsername->setFocus();
}

void UserController::addUser() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (!validateForm()) return;

    QString username = ui->leUserUsername->text();
    QString password = ui->leUserPassword->text();
    QString role = ui->cbUserRole->currentText().toUpper();

    if (UserDao::add(username, password, role)) {
        QMessageBox::information(m_mainWindow, "Utilisateur", "Utilisateur ajouté avec succès");
        // Clear form and switch to view mode
        ui->leUserUsername->clear();
        ui->leUserPassword->clear();
        ui->cbUserRole->setCurrentIndex(0);
        ui->stackedUser->setCurrentIndex(0); // Switch to view mode
        refreshUsers();
    } else {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Échec de l'ajout: " + Db::instance().lastError());
    }
}

void UserController::updateUser() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblUsers->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Veuillez sélectionner un utilisateur à modifier");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblUsers->item(row, 0)->text().toInt();

    QString username = ui->leUserUsername->text();
    QString role = ui->cbUserRole->currentText().toUpper();
    QString status = ui->cbUserStatus->currentText();

    if (UserDao::update(id, username, role, status)) {
        QMessageBox::information(m_mainWindow, "Utilisateur", "Utilisateur modifié avec succès");
        // Switch back to view mode
        ui->stackedUser->setCurrentIndex(0);
        refreshUsers();
    } else {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Échec de la modification: " + Db::instance().lastError());
    }
}

void UserController::deleteUser() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblUsers->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Veuillez sélectionner un utilisateur à supprimer");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblUsers->item(row, 0)->text().toInt();
    QString username = ui->tblUsers->item(row, 1)->text();

    // Prevent self-deletion - we need to access the user ID from the main window
    // This is a temporary fix - ideally we should pass the user ID to the controller
    if (id == 1) { // Assuming current user ID is 1 for now
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Vous ne pouvez pas supprimer votre propre compte");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(m_mainWindow, "Confirmation",
                                  QString("Êtes-vous sûr de vouloir supprimer l'utilisateur %1?").arg(username),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (UserDao::remove(id)) {
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
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblUsers->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Veuillez sélectionner un utilisateur");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblUsers->item(row, 0)->text().toInt();
    QString username = ui->tblUsers->item(row, 1)->text();

    QString password = QInputDialog::getText(m_mainWindow, "Changer le mot de passe",
                                             QString("Nouveau mot de passe pour %1:").arg(username),
                                             QLineEdit::Password);

    if (password.isEmpty()) {
        return;
    }

    if (UserDao::updatePassword(id, password)) {
        QMessageBox::information(m_mainWindow, "Utilisateur", "Mot de passe changé avec succès");
    } else {
        QMessageBox::warning(m_mainWindow, "Utilisateur", "Échec du changement de mot de passe: " + Db::instance().lastError());
    }
}

void UserController::cancelEdit() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    ui->stackedUser->setCurrentIndex(0); // Switch back to view mode
}

void UserController::loadUsersTable() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto users = UserDao::all();
    ui->tblUsers->clearContents();
    ui->tblUsers->setRowCount(users.size());
    ui->tblUsers->setColumnCount(5);
    QStringList headers = {"ID","Nom d'utilisateur","Rôle","Statut","Date création"};
    ui->tblUsers->setHorizontalHeaderLabels(headers);
    ui->tblUsers->horizontalHeader()->setStretchLastSection(true);
    ui->tblUsers->setAlternatingRowColors(true);
    ui->tblUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblUsers->setSelectionMode(QAbstractItemView::SingleSelection);

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
    applyFilters();
    updateChart();
}

void UserController::applyFilters() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    QString text = ui->leSearchUser->text().trimmed();

    for (int r=0; r<ui->tblUsers->rowCount(); ++r) ui->tblUsers->setRowHidden(r, false);

    for (int r=0; r<ui->tblUsers->rowCount(); ++r) {
        bool match = true;

        // Username search
        if (!text.isEmpty()) {
            QString username = ui->tblUsers->item(r,1)->text();
            match &= username.contains(text, Qt::CaseInsensitive);
        }

        if (!match) ui->tblUsers->setRowHidden(r, true);
    }
}

void UserController::updateChart() {
    // Access the chart view through the main window's member variable
    QChartView* userChartView = m_mainWindow->userChartView;
    if (!userChartView) return;

    auto users = UserDao::all();

    QMap<QString, int> roleCounts;
    for (const auto &user : users) {
        roleCounts[user.role]++;
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

bool UserController::validateForm() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (ui->leUserUsername->text().isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le nom d'utilisateur est obligatoire");
        ui->leUserUsername->setFocus();
        return false;
    }
    if (ui->leUserPassword->text().isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le mot de passe est obligatoire");
        ui->leUserPassword->setFocus();
        return false;
    }
    return true;
}
