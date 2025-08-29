#include "logindialog.h"
#include "ui_logindialog.h"
#include "db.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QResizeEvent>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_userId(-1)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Système de Gestion Logistique - Connexion");
    setFixedSize(1000, 700);

    // Remove question mark from title bar and make frameless
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    // Center the dialog on screen
    centerOnScreen();

    // Set placeholder texts
    ui->leUsername->setPlaceholderText("Entrez votre nom d'utilisateur");
    ui->lePassword->setPlaceholderText("Entrez votre mot de passe");
    ui->leRegUsername->setPlaceholderText("Choisissez un nom d'utilisateur");
    ui->leRegPassword->setPlaceholderText("Choisissez un mot de passe");

    // Set password echo mode
    ui->lePassword->setEchoMode(QLineEdit::Password);
    ui->leRegPassword->setEchoMode(QLineEdit::Password);

    // Set focus to username field
    ui->leUsername->setFocus();

    // Connect buttons to their slots
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(ui->btnRegister, &QPushButton::clicked, this, &LoginDialog::onRegisterClicked);
    connect(ui->btnSwitchToRegister, &QPushButton::clicked, this, &LoginDialog::onSwitchToRegisterClicked);
    connect(ui->btnSwitchToLogin, &QPushButton::clicked, this, &LoginDialog::onSwitchToLoginClicked);

    // Connect return pressed to buttons
    connect(ui->leUsername, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);
    connect(ui->lePassword, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);
    connect(ui->leRegUsername, &QLineEdit::returnPressed, this, &LoginDialog::onRegisterClicked);
    connect(ui->leRegPassword, &QLineEdit::returnPressed, this, &LoginDialog::onRegisterClicked);

    // Setup animations
    setupAnimations();

    // Show login form by default
    showLoginForm();
}

void LoginDialog::centerOnScreen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void LoginDialog::setupAnimations()
{
    // Create fade animations for smooth transitions
    m_fadeInAnimation = new QPropertyAnimation(this, "windowOpacity");
    m_fadeInAnimation->setDuration(300);
    m_fadeInAnimation->setStartValue(0.0);
    m_fadeInAnimation->setEndValue(1.0);

    m_fadeOutAnimation = new QPropertyAnimation(this, "windowOpacity");
    m_fadeOutAnimation->setDuration(300);
    m_fadeOutAnimation->setStartValue(1.0);
    m_fadeOutAnimation->setEndValue(0.0);

    // Start with fade in
    m_fadeInAnimation->start();
}

void LoginDialog::showLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->leUsername->setFocus();
    ui->titleLabel->setText("Système de Gestion Logistique");
    ui->subtitleLabel->setText("Connectez-vous à votre compte");
}

void LoginDialog::showRegisterForm()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->leRegUsername->setFocus();
    ui->titleLabel->setText("Création de Compte");
    ui->subtitleLabel->setText("Créez votre nouveau compte");
}

void LoginDialog::animateTransition(bool toRegister)
{
    // Create a smooth transition animation
    QPropertyAnimation *slideAnimation = new QPropertyAnimation(ui->stackedWidget, "pos");
    slideAnimation->setDuration(300);
    
    if (toRegister) {
        slideAnimation->setStartValue(QPoint(0, 0));
        slideAnimation->setEndValue(QPoint(-ui->stackedWidget->width(), 0));
    } else {
        slideAnimation->setStartValue(QPoint(ui->stackedWidget->width(), 0));
        slideAnimation->setEndValue(QPoint(0, 0));
    }
    
    slideAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginDialog::onLoginClicked()
{
    QString username = ui->leUsername->text().trimmed();
    QString password = ui->lePassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Validate credentials against database
    QSqlQuery query(Db::instance().conn());
    query.prepare("SELECT ID_USER, USERNAME, ROLE FROM USERS WHERE USERNAME = :username AND PASSWORD = :password AND STATUS = 'ACTIVE'");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        m_userId = query.value(0).toInt();
        m_username = query.value(1).toString();
        m_role = query.value(2).toString();
        
        // Fade out and accept
        connect(m_fadeOutAnimation, &QPropertyAnimation::finished, this, &QDialog::accept);
        m_fadeOutAnimation->start();
    } else {
        QMessageBox::critical(this, "Erreur", "Nom d'utilisateur ou mot de passe incorrect.");
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}

void LoginDialog::onRegisterClicked()
{
    QString username = ui->leRegUsername->text().trimmed();
    QString password = ui->leRegPassword->text();
    QString role = ui->cbRegRole->currentText().toUpper();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    if (password.length() < 6) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit contenir au moins 6 caractères.");
        return;
    }

    // Check if username already exists
    QSqlQuery checkQuery(Db::instance().conn());
    checkQuery.prepare("SELECT COUNT(*) FROM USERS WHERE USERNAME = :username");
    checkQuery.bindValue(":username", username);
    
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "Ce nom d'utilisateur existe déjà.");
        return;
    }

    // Insert new user
    QSqlQuery insertQuery(Db::instance().conn());
    insertQuery.prepare("INSERT INTO USERS (USERNAME, PASSWORD, ROLE, STATUS, DATE_CREATION) VALUES (:username, :password, :role, 'ACTIVE', CURRENT_DATE)");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);
    insertQuery.bindValue(":role", role);

    if (insertQuery.exec()) {
        QMessageBox::information(this, "Succès", "Compte créé avec succès! Vous pouvez maintenant vous connecter.");
        
        // Clear form and switch to login
        ui->leRegUsername->clear();
        ui->leRegPassword->clear();
        ui->cbRegRole->setCurrentIndex(0);
        
        onSwitchToLoginClicked();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la création du compte: " + insertQuery.lastError().text());
    }
}

void LoginDialog::onSwitchToRegisterClicked()
{
    animateTransition(true);
    showRegisterForm();
}

void LoginDialog::onSwitchToLoginClicked()
{
    animateTransition(false);
    showLoginForm();
}

int LoginDialog::getUserId() const
{
    return m_userId;
}

QString LoginDialog::getUsername() const
{
    return m_username;
}

QString LoginDialog::getRole() const
{
    return m_role;
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

void LoginDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    }
    QDialog::keyPressEvent(event);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
