/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *leftPanel;
    QVBoxLayout *verticalLayout;
    QLabel *logoLabel;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QSpacerItem *verticalSpacerTop;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *lblUsername;
    QLineEdit *leUsername;
    QLabel *lblPassword;
    QLineEdit *lePassword;
    QPushButton *btnLogin;
    QPushButton *btnSwitchToRegister;
    QWidget *registerPage;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout_2;
    QLabel *lblRegUsername;
    QLineEdit *leRegUsername;
    QLabel *lblRegPassword;
    QLineEdit *leRegPassword;
    QLabel *lblRegRole;
    QComboBox *cbRegRole;
    QPushButton *btnRegister;
    QPushButton *btnSwitchToLogin;
    QSpacerItem *verticalSpacerBottom;
    QLabel *footerLabel;
    QFrame *rightPanel;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QLabel *welcomeLabel;
    QLabel *descriptionLabel;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(1000, 700);
        LoginDialog->setMinimumSize(QSize(900, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/app_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        LoginDialog->setWindowIcon(icon);
        LoginDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                               stop:0 #667eea, stop:1 #764ba2);\n"
"}"));
        horizontalLayout = new QHBoxLayout(LoginDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftPanel = new QFrame(LoginDialog);
        leftPanel->setObjectName("leftPanel");
        leftPanel->setMinimumSize(QSize(400, 0));
        leftPanel->setMaximumSize(QSize(400, 16777215));
        leftPanel->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background: rgba(255, 255, 255, 0.95);\n"
"    border-radius: 0px;\n"
"}"));
        verticalLayout = new QVBoxLayout(leftPanel);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, 30, 30, 30);
        logoLabel = new QLabel(leftPanel);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(0, 80));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/icons/logo.png")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(logoLabel);

        titleLabel = new QLabel(leftPanel);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2d3748;\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(leftPanel);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #718096;\n"
"    font-size: 14px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        subtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(subtitleLabel);

        verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacerTop);

        stackedWidget = new QStackedWidget(leftPanel);
        stackedWidget->setObjectName("stackedWidget");
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        verticalLayout_2 = new QVBoxLayout(loginPage);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(15);
        formLayout->setVerticalSpacing(15);
        lblUsername = new QLabel(loginPage);
        lblUsername->setObjectName("lblUsername");
        lblUsername->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4a5568;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        lblUsername->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, lblUsername);

        leUsername = new QLineEdit(loginPage);
        leUsername->setObjectName("leUsername");
        leUsername->setMinimumSize(QSize(200, 40));
        leUsername->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #e2e8f0;\n"
"    border-radius: 8px;\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    background: white;\n"
"    color: #2d3748;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #667eea;\n"
"    background: #f7fafc;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #a0aec0;\n"
"}"));

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, leUsername);

        lblPassword = new QLabel(loginPage);
        lblPassword->setObjectName("lblPassword");
        lblPassword->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4a5568;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        lblPassword->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, lblPassword);

        lePassword = new QLineEdit(loginPage);
        lePassword->setObjectName("lePassword");
        lePassword->setMinimumSize(QSize(200, 40));
        lePassword->setEchoMode(QLineEdit::Password);
        lePassword->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #e2e8f0;\n"
"    border-radius: 8px;\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    background: white;\n"
"    color: #2d3748;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #667eea;\n"
"    background: #f7fafc;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #a0aec0;\n"
"}"));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lePassword);


        verticalLayout_2->addLayout(formLayout);

        btnLogin = new QPushButton(loginPage);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setMinimumSize(QSize(0, 45));
        btnLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                               stop:0 #667eea, stop:1 #764ba2);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                               stop:0 #5a67d8, stop:1 #6b46c1);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                               stop:0 #4c51bf, stop:1 #553c9a);\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background: #a0aec0;\n"
"    color: #e2e8f0;\n"
"}"));
        btnLogin->setCursor(Qt::PointingHandCursor);

        verticalLayout_2->addWidget(btnLogin);

        btnSwitchToRegister = new QPushButton(loginPage);
        btnSwitchToRegister->setObjectName("btnSwitchToRegister");
        btnSwitchToRegister->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: transparent;\n"
"    border: 2px solid #e2e8f0;\n"
"    border-radius: 8px;\n"
"    color: #4a5568;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    padding: 12px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: #f7fafc;\n"
"    border-color: #cbd5e0;\n"
"    color: #2d3748;\n"
"}"));
        btnSwitchToRegister->setCursor(Qt::PointingHandCursor);

        verticalLayout_2->addWidget(btnSwitchToRegister);

        stackedWidget->addWidget(loginPage);
        registerPage = new QWidget();
        registerPage->setObjectName("registerPage");
        verticalLayout_3 = new QVBoxLayout(registerPage);
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setObjectName("verticalLayout_3");
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setHorizontalSpacing(15);
        formLayout_2->setVerticalSpacing(15);
        lblRegUsername = new QLabel(registerPage);
        lblRegUsername->setObjectName("lblRegUsername");
        lblRegUsername->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4a5568;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        lblRegUsername->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, lblRegUsername);

        leRegUsername = new QLineEdit(registerPage);
        leRegUsername->setObjectName("leRegUsername");
        leRegUsername->setMinimumSize(QSize(200, 40));
        leRegUsername->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #e2e8f0;\n"
"    border-radius: 8px;\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    background: white;\n"
"    color: #2d3748;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #667eea;\n"
"    background: #f7fafc;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #a0aec0;\n"
"}"));

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, leRegUsername);

        lblRegPassword = new QLabel(registerPage);
        lblRegPassword->setObjectName("lblRegPassword");
        lblRegPassword->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4a5568;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        lblRegPassword->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, lblRegPassword);

        leRegPassword = new QLineEdit(registerPage);
        leRegPassword->setObjectName("leRegPassword");
        leRegPassword->setMinimumSize(QSize(200, 40));
        leRegPassword->setEchoMode(QLineEdit::Password);
        leRegPassword->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #e2e8f0;\n"
"    border-radius: 8px;\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    background: white;\n"
"    color: #2d3748;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #667eea;\n"
"    background: #f7fafc;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #a0aec0;\n"
"}"));

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, leRegPassword);

        lblRegRole = new QLabel(registerPage);
        lblRegRole->setObjectName("lblRegRole");
        lblRegRole->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4a5568;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        lblRegRole->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, lblRegRole);

        cbRegRole = new QComboBox(registerPage);
        cbRegRole->addItem(QString());
        cbRegRole->addItem(QString());
        cbRegRole->addItem(QString());
        cbRegRole->setObjectName("cbRegRole");
        cbRegRole->setMinimumSize(QSize(200, 40));
        cbRegRole->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 2px solid #e2e8f0;\n"
"    border-radius: 8px;\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    background: white;\n"
"    color: #2d3748;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border-color: #667eea;\n"
"    background: #f7fafc;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 30px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGQ9Ik0xIDFMNiA2TDExIDEiIHN0cm9rZT0iIzY5NzM3NyIgc3Ryb2tlLXdpZHRoPSIyIiBzdHJva2UtbGluZWNhcD0icm91bmQiIHN0cm9rZS1saW5lam9pbj0icm91bmQiLz4KPC9zdmc+);\n"
"    width: 12px;\n"
"    height: 8px;\n"
"}"));

        formLayout_2->setWidget(2, QFormLayout::ItemRole::FieldRole, cbRegRole);


        verticalLayout_3->addLayout(formLayout_2);

        btnRegister = new QPushButton(registerPage);
        btnRegister->setObjectName("btnRegister");
        btnRegister->setMinimumSize(QSize(0, 45));
        btnRegister->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                               stop:0 #48bb78, stop:1 #38a169);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                               stop:0 #38a169, stop:1 #2f855a);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                               stop:0 #2f855a, stop:1 #276749);\n"
"}"));
        btnRegister->setCursor(Qt::PointingHandCursor);

        verticalLayout_3->addWidget(btnRegister);

        btnSwitchToLogin = new QPushButton(registerPage);
        btnSwitchToLogin->setObjectName("btnSwitchToLogin");
        btnSwitchToLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: transparent;\n"
"    border: 2px solid #e2e8f0;\n"
"    border-radius: 8px;\n"
"    color: #4a5568;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    padding: 12px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: #f7fafc;\n"
"    border-color: #cbd5e0;\n"
"    color: #2d3748;\n"
"}"));
        btnSwitchToLogin->setCursor(Qt::PointingHandCursor);

        verticalLayout_3->addWidget(btnSwitchToLogin);

        stackedWidget->addWidget(registerPage);

        verticalLayout->addWidget(stackedWidget);

        verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacerBottom);

        footerLabel = new QLabel(leftPanel);
        footerLabel->setObjectName("footerLabel");
        footerLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #a0aec0;\n"
"    font-size: 11px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        footerLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(footerLabel);


        horizontalLayout->addWidget(leftPanel);

        rightPanel = new QFrame(LoginDialog);
        rightPanel->setObjectName("rightPanel");
        rightPanel->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background: transparent;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(rightPanel);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        welcomeLabel = new QLabel(rightPanel);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;\n"
"    font-size: 28px;\n"
"    font-weight: bold;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        welcomeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(welcomeLabel);

        descriptionLabel = new QLabel(rightPanel);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: rgba(255, 255, 255, 0.9);\n"
"    font-size: 16px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        descriptionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(descriptionLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(rightPanel);


        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Syst\303\250me de Gestion Logistique - Connexion", nullptr));
        logoLabel->setText(QString());
        titleLabel->setText(QCoreApplication::translate("LoginDialog", "Syst\303\250me de Gestion Logistique", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("LoginDialog", "Connectez-vous \303\240 votre compte", nullptr));
        lblUsername->setText(QCoreApplication::translate("LoginDialog", "Identifiant:", nullptr));
        leUsername->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Entrez votre nom d'utilisateur", nullptr));
        lblPassword->setText(QCoreApplication::translate("LoginDialog", "Mot de passe:", nullptr));
        lePassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Entrez votre mot de passe", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Se connecter", nullptr));
        btnSwitchToRegister->setText(QCoreApplication::translate("LoginDialog", "Cr\303\251er un nouveau compte", nullptr));
        lblRegUsername->setText(QCoreApplication::translate("LoginDialog", "Identifiant:", nullptr));
        leRegUsername->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Choisissez un nom d'utilisateur", nullptr));
        lblRegPassword->setText(QCoreApplication::translate("LoginDialog", "Mot de passe:", nullptr));
        leRegPassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Choisissez un mot de passe", nullptr));
        lblRegRole->setText(QCoreApplication::translate("LoginDialog", "R\303\264le:", nullptr));
        cbRegRole->setItemText(0, QCoreApplication::translate("LoginDialog", "Administrateur", nullptr));
        cbRegRole->setItemText(1, QCoreApplication::translate("LoginDialog", "Gestionnaire logistique", nullptr));
        cbRegRole->setItemText(2, QCoreApplication::translate("LoginDialog", "Livreur", nullptr));

        btnRegister->setText(QCoreApplication::translate("LoginDialog", "Cr\303\251er le compte", nullptr));
        btnSwitchToLogin->setText(QCoreApplication::translate("LoginDialog", "Retour \303\240 la connexion", nullptr));
        footerLabel->setText(QCoreApplication::translate("LoginDialog", "\302\251 2024 Syst\303\250me de Gestion Logistique. Tous droits r\303\251serv\303\251s.", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("LoginDialog", "Bienvenue dans votre syst\303\250me de gestion logistique", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("LoginDialog", "G\303\251rez vos clients, commandes et utilisateurs avec facilit\303\251 et efficacit\303\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
