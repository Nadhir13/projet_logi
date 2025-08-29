#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_userId(-1)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Connexion - Système de Gestion Logistique");
    setFixedSize(400, 400);

    // Remove question mark from title bar
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Center the dialog on screen (Qt 6 compatible)
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // Set placeholder texts
    ui->leUsername->setPlaceholderText("Nom d'utilisateur");
    ui->lePassword->setPlaceholderText("Mot de passe");

    // Set password echo mode
    ui->lePassword->setEchoMode(QLineEdit::Password);

    // Set focus to username field
    ui->leUsername->setFocus();

    // Connect buttons to their slots
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &LoginDialog::onCancelClicked);

    // Connect return pressed to login button
    connect(ui->leUsername, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);
    connect(ui->lePassword, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);

    // Load background image from resources
    QPixmap pixmap(":/images/blue.jpg");
    if (!pixmap.isNull()) {
        pixmap = pixmap.scaled(ui->lblImage->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);
    } else {
        ui->lblImage->setText("Image non trouvée");
        ui->lblImage->setStyleSheet("color: #ff0000; background-color: #ffeeee;");
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUsername() const
{
    return m_username;
}

QString LoginDialog::getRole() const
{
    return m_role;
}

int LoginDialog::getUserId() const
{
    return m_userId;
}

void LoginDialog::onLoginClicked()
{
    QString username = ui->leUsername->text().trimmed();
    QString password = ui->lePassword->text();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Connexion", "Veuillez saisir un nom d'utilisateur");
        ui->leUsername->setFocus();
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "Connexion", "Veuillez saisir un mot de passe");
        ui->lePassword->setFocus();
        return;
    }

    if (authenticateUser(username, password)) {
        accept(); // Close dialog with success
    } else {
        QMessageBox::warning(this, "Connexion", "Nom d'utilisateur ou mot de passe incorrect");
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}

void LoginDialog::onCancelClicked()
{
    reject(); // Close dialog with failure
}

bool LoginDialog::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query(Db::instance().conn());
    query.prepare("SELECT ID_USER, USERNAME, ROLE FROM USERS WHERE USERNAME = :username AND PASSWORD = :password AND STATUS = 'ACTIVE'");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        m_userId = query.value(0).toInt();
        m_username = query.value(1).toString();
        m_role = query.value(2).toString();

        // Map database roles to French role names for display
        if (m_role == "ADMIN") m_role = "Administrateur";
        else if (m_role == "MANAGER") m_role = "Gestionnaire logistique";
        else if (m_role == "DELIVERY") m_role = "Livreur";

        return true;
    }

    return false;
}
