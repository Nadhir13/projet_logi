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

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_userId(-1),
    m_backgroundLoaded(false)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Connexion - Système de Gestion Logistique");
    setFixedSize(780, 600); // Increased height for signup form

    // Remove question mark from title bar
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Center the dialog on screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // Set placeholder texts
    ui->leUsername->setPlaceholderText("Nom d'utilisateur");
    ui->lePassword->setPlaceholderText("Mot de passe");
    ui->leSignupUsername->setPlaceholderText("Choisissez un nom d'utilisateur");
    ui->leSignupPassword->setPlaceholderText("Choisissez un mot de passe");
    ui->leConfirmPassword->setPlaceholderText("Confirmez le mot de passe");

    // Set password echo mode
    ui->lePassword->setEchoMode(QLineEdit::Password);
    ui->leSignupPassword->setEchoMode(QLineEdit::Password);
    ui->leConfirmPassword->setEchoMode(QLineEdit::Password);

    // Set focus to username field
    ui->leUsername->setFocus();

    // Connect buttons to their slots
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(ui->btnSignup, &QPushButton::clicked, this, &LoginDialog::onSignupClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &LoginDialog::onCancelClicked);
    connect(ui->btnCancelSignup, &QPushButton::clicked, this, &LoginDialog::onCancelClicked);
    connect(ui->btnSwitchToSignup, &QPushButton::clicked, this, &LoginDialog::onSwitchToSignupClicked);
    connect(ui->btnSwitchToLogin, &QPushButton::clicked, this, &LoginDialog::onSwitchToLoginClicked);

    // Connect return pressed to buttons
    connect(ui->leUsername, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);
    connect(ui->lePassword, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);
    connect(ui->leSignupUsername, &QLineEdit::returnPressed, this, &LoginDialog::onSignupClicked);
    connect(ui->leSignupPassword, &QLineEdit::returnPressed, this, &LoginDialog::onSignupClicked);
    connect(ui->leConfirmPassword, &QLineEdit::returnPressed, this, &LoginDialog::onSignupClicked);

    // Load background image
    loadBackgroundImage();

    // Apply transparent styles to make text readable
    applyTransparentStyles();

    // Setup animations
    setupAnimations();

    // Show login form by default
    showLoginForm();
}

void LoginDialog::setupAnimations()
{
    // We'll create animations dynamically when needed
}

void LoginDialog::showLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->leUsername->setFocus();
}

void LoginDialog::showSignupForm()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->leSignupUsername->setFocus();
}

void LoginDialog::animateTransition(bool toSignup)
{
    QWidget *currentWidget = ui->stackedWidget->currentWidget();
    QWidget *nextWidget = ui->stackedWidget->widget(toSignup ? 1 : 0);

    // Create fade out animation for current widget
    QPropertyAnimation *fadeOut = new QPropertyAnimation(currentWidget, "windowOpacity");
    fadeOut->setDuration(300);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    // Create fade in animation for next widget
    QPropertyAnimation *fadeIn = new QPropertyAnimation(nextWidget, "windowOpacity");
    fadeIn->setDuration(300);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);

    // Create sequential animation group
    QSequentialAnimationGroup *sequence = new QSequentialAnimationGroup(this);
    sequence->addAnimation(fadeOut);
    sequence->addAnimation(fadeIn);

    // Change widget after fade out
    connect(fadeOut, &QPropertyAnimation::finished, this, [this, toSignup]() {
        ui->stackedWidget->setCurrentIndex(toSignup ? 1 : 0);
    });

    sequence->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginDialog::loadBackgroundImage()
{
    QString imagePath = ":/image/nature.jpg";
    qDebug() << "Trying to load image from:" << imagePath;

    // Check if file exists in resources
    if (QFile::exists(imagePath)) {
        qDebug() << "Image file exists in resources";

        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            qDebug() << "Image loaded successfully. Size:" << pixmap.size();
            m_background = pixmap;
            m_backgroundLoaded = true;
            update();
            return;
        } else {
            qDebug() << "Failed to load pixmap from resource";
        }
    } else {
        qDebug() << "Image file does NOT exist in resources";
    }

    // If no image found, use solid color
    m_backgroundLoaded = false;
    qDebug() << "Using fallback blue background";
    setStyleSheet("QDialog { background-color: #3498db; }");
}

void LoginDialog::paintEvent(QPaintEvent *event)
{
    // First paint the background if loaded
    if (m_backgroundLoaded) {
        QPainter painter(this);

        // Scale image to fit the dialog while maintaining aspect ratio
        QPixmap scaledBg = m_background.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        // Draw centered
        int x = (width() - scaledBg.width()) / 2;
        int y = (height() - scaledBg.height()) / 2;
        painter.drawPixmap(x, y, scaledBg);
    }

    // Then paint the normal UI elements
    QDialog::paintEvent(event);
}

void LoginDialog::applyTransparentStyles()
{
    // Make all UI elements semi-transparent with more rounded corners
    QString transparentStyle = "background-color: rgba(255, 255, 255, 220); "
                               "color: #000000; "
                               "border-radius: 10px; "
                               "padding: 8px; "
                               "font-size: 11px;";

    QString titleStyle = "background-color: rgba(255, 255, 255, 220); "
                         "color: #2c3e50; "
                         "border-radius: 15px; "
                         "padding: 12px; "
                         "font-weight: 600; "
                         "font-size: 18px;";

    QString buttonStyle = "QPushButton { "
                          "background-color: rgba(77, 144, 254, 220); "
                          "color: white; "
                          "border: 2px solid #3079ed; "
                          "border-radius: 8px; "
                          "padding: 8px 20px; "
                          "font-size: 12px; "
                          "min-width: 100px; "
                          "} "
                          "QPushButton:hover { "
                          "background-color: rgba(90, 154, 254, 240); "
                          "}";

    QString cancelButtonStyle = "QPushButton { "
                                "background-color: rgba(245, 245, 245, 220); "
                                "color: #333333; "
                                "border: 2px solid #cccccc; "
                                "border-radius: 8px; "
                                "padding: 8px 20px; "
                                "font-size: 12px; "
                                "min-width: 100px; "
                                "} "
                                "QPushButton:hover { "
                                "background-color: rgba(255, 255, 255, 240); "
                                "}";

    QString linkButtonStyle = "QPushButton { "
                              "background-color: transparent; "
                              "color: #3498db; "
                              "border: none; "
                              "text-decoration: underline; "
                              "padding: 5px; "
                              "font-size: 11px; "
                              "} "
                              "QPushButton:hover { "
                              "color: #2980b9; "
                              "}";

    QString versionStyle = "background-color: rgba(255, 255, 255, 180); "
                           "color: #666666; "
                           "border-radius: 8px; "
                           "padding: 4px 8px; "
                           "font-size: 10px;";

    // Apply styles to login form elements
    ui->label->setStyleSheet(titleStyle);
    ui->lblUsername->setStyleSheet(transparentStyle);
    ui->lblPassword->setStyleSheet(transparentStyle);
    ui->leUsername->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->lePassword->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->btnLogin->setStyleSheet(buttonStyle);
    ui->btnCancel->setStyleSheet(cancelButtonStyle);
    ui->btnSwitchToSignup->setStyleSheet(linkButtonStyle);
    ui->lblVersion->setStyleSheet(versionStyle);

    // Apply styles to signup form elements
    ui->label_2->setStyleSheet(titleStyle);
    ui->lblSignupUsername->setStyleSheet(transparentStyle);
    ui->lblSignupPassword->setStyleSheet(transparentStyle);
    ui->lblConfirmPassword->setStyleSheet(transparentStyle);
    ui->lblRole->setStyleSheet(transparentStyle);
    ui->leSignupUsername->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->leSignupPassword->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->leConfirmPassword->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->cbRole->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->btnSignup->setStyleSheet(buttonStyle);
    ui->btnCancelSignup->setStyleSheet(cancelButtonStyle);
    ui->btnSwitchToLogin->setStyleSheet(linkButtonStyle);

    // Center align all text
    ui->label->setAlignment(Qt::AlignCenter);
    ui->lblUsername->setAlignment(Qt::AlignCenter);
    ui->lblPassword->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->lblSignupUsername->setAlignment(Qt::AlignCenter);
    ui->lblSignupPassword->setAlignment(Qt::AlignCenter);
    ui->lblConfirmPassword->setAlignment(Qt::AlignCenter);
    ui->lblRole->setAlignment(Qt::AlignCenter);
    ui->lblVersion->setAlignment(Qt::AlignCenter);

    // Set input fields to center alignment
    ui->leUsername->setAlignment(Qt::AlignCenter);
    ui->lePassword->setAlignment(Qt::AlignCenter);
    ui->leSignupUsername->setAlignment(Qt::AlignCenter);
    ui->leSignupPassword->setAlignment(Qt::AlignCenter);
    ui->leConfirmPassword->setAlignment(Qt::AlignCenter);
}

void LoginDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    update();
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
        accept();
    } else {
        QMessageBox::warning(this, "Connexion", "Nom d'utilisateur ou mot de passe incorrect");
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}

void LoginDialog::onSignupClicked()
{
    QString username = ui->leSignupUsername->text().trimmed();
    QString password = ui->leSignupPassword->text();
    QString confirmPassword = ui->leConfirmPassword->text();
    QString role = ui->cbRole->currentText().toUpper();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Inscription", "Veuillez saisir un nom d'utilisateur");
        ui->leSignupUsername->setFocus();
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "Inscription", "Veuillez saisir un mot de passe");
        ui->leSignupPassword->setFocus();
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Inscription", "Les mots de passe ne correspondent pas");
        ui->leConfirmPassword->clear();
        ui->leConfirmPassword->setFocus();
        return;
    }

    if (registerUser(username, password, role)) {
        QMessageBox::information(this, "Inscription", "Compte créé avec succès! Vous pouvez maintenant vous connecter.");
        animateTransition(false); // Switch back to login form
        ui->leUsername->setText(username);
        ui->lePassword->setFocus();
    } else {
        QMessageBox::warning(this, "Inscription", "Échec de la création du compte. Le nom d'utilisateur existe peut-être déjà.");
    }
}

void LoginDialog::onCancelClicked()
{
    reject();
}

void LoginDialog::onSwitchToSignupClicked()
{
    animateTransition(true);
}

void LoginDialog::onSwitchToLoginClicked()
{
    animateTransition(false);
}

bool LoginDialog::authenticateUser(const QString &username, const QString &password)
{
    // Check if Db connection is available
    if (!Db::instance().conn().isOpen()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données non disponible");
        return false;
    }

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

bool LoginDialog::registerUser(const QString &username, const QString &password, const QString &role)
{
    // Check if Db connection is available
    if (!Db::instance().conn().isOpen()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données non disponible");
        return false;
    }

    // Check if username already exists
    QSqlQuery checkQuery(Db::instance().conn());
    checkQuery.prepare("SELECT COUNT(*) FROM USERS WHERE USERNAME = :username");
    checkQuery.bindValue(":username", username);

    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        return false; // Username already exists
    }

    // Insert new user
    QSqlQuery insertQuery(Db::instance().conn());
    insertQuery.prepare("INSERT INTO USERS (USERNAME, PASSWORD, ROLE, STATUS) VALUES (:username, :password, :role, 'ACTIVE')");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);
    insertQuery.bindValue(":role", role);

    return insertQuery.exec();
}
