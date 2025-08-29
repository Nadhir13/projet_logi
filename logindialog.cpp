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

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_userId(-1),
    m_backgroundLoaded(false)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Connexion - Système de Gestion Logistique");
    setFixedSize(800, 600);

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

    // Load background image
    loadBackgroundImage();

    // Apply transparent styles to make text readable
    applyTransparentStyles();
}

void LoginDialog::loadBackgroundImage()
{
    QString imagePath = ":/image/blue.jpg";
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
                               "border-radius: 10px; "  // More rounded corners
                               "padding: 8px; "         // Slightly more padding
                               "font-size: 11px;";      // Smaller font

    QString titleStyle = "background-color: rgba(255, 255, 255, 220); "
                         "color: #2c3e50; "
                         "border-radius: 15px; "       // Very rounded corners
                         "padding: 12px; "
                         "font-weight: 600; "
                         "font-size: 18px;";           // Slightly smaller title

    QString buttonStyle = "QPushButton { "
                          "background-color: rgba(77, 144, 254, 220); "
                          "color: white; "
                          "border: 2px solid #3079ed; "
                          "border-radius: 8px; "       // More rounded buttons
                          "padding: 8px 20px; "
                          "font-size: 12px; "
                          "min-width: 100px; "         // Consistent button width
                          "} "
                          "QPushButton:hover { "
                          "background-color: rgba(90, 154, 254, 240); "
                          "}";

    QString cancelButtonStyle = "QPushButton { "
                                "background-color: rgba(245, 245, 245, 220); "
                                "color: #333333; "
                                "border: 2px solid #cccccc; "
                                "border-radius: 8px; " // More rounded buttons
                                "padding: 8px 20px; "
                                "font-size: 12px; "
                                "min-width: 100px; "   // Consistent button width
                                "} "
                                "QPushButton:hover { "
                                "background-color: rgba(255, 255, 255, 240); "
                                "}";

    QString versionStyle = "background-color: rgba(255, 255, 255, 180); "
                           "color: #666666; "
                           "border-radius: 8px; "      // More rounded
                           "padding: 4px 8px; "
                           "font-size: 10px;";         // Smaller version text

    // Apply styles to all elements
    ui->label->setStyleSheet(titleStyle);
    ui->lblUsername->setStyleSheet(transparentStyle);
    ui->lblPassword->setStyleSheet(transparentStyle);
    ui->leUsername->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->lePassword->setStyleSheet(transparentStyle + "border: 2px solid #cccccc;");
    ui->btnLogin->setStyleSheet(buttonStyle);
    ui->btnCancel->setStyleSheet(cancelButtonStyle);
    ui->lblVersion->setStyleSheet(versionStyle);

    // Center align all text
    ui->label->setAlignment(Qt::AlignCenter);
    ui->lblUsername->setAlignment(Qt::AlignCenter);
    ui->lblPassword->setAlignment(Qt::AlignCenter);
    ui->lblVersion->setAlignment(Qt::AlignCenter);

    // Set input fields to center alignment
    ui->leUsername->setAlignment(Qt::AlignCenter);
    ui->lePassword->setAlignment(Qt::AlignCenter);
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

void LoginDialog::onCancelClicked()
{
    reject();
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
