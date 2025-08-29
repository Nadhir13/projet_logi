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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
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
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacerTop;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacerMiddle1;
    QHBoxLayout *horizontalLayoutCenter;
    QSpacerItem *horizontalSpacerLeft;
    QFormLayout *formLayout;
    QLabel *lblUsername;
    QLineEdit *leUsername;
    QLabel *lblPassword;
    QLineEdit *lePassword;
    QSpacerItem *horizontalSpacerRight;
    QSpacerItem *verticalSpacerMiddle2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnLogin;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnSwitchToSignup;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacerBottom;
    QLabel *lblVersion;
    QWidget *signupPage;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacerMiddle1_2;
    QHBoxLayout *horizontalLayoutCenter_2;
    QSpacerItem *horizontalSpacerLeft_2;
    QFormLayout *formLayout_2;
    QLabel *lblSignupUsername;
    QLineEdit *leSignupUsername;
    QLabel *lblSignupPassword;
    QLineEdit *leSignupPassword;
    QLabel *lblConfirmPassword;
    QLineEdit *leConfirmPassword;
    QLabel *lblRole;
    QComboBox *cbRole;
    QSpacerItem *horizontalSpacerRight_2;
    QSpacerItem *verticalSpacerMiddle2_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnSignup;
    QPushButton *btnCancelSignup;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btnSwitchToLogin;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacerBottom_2;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(800, 600);
        LoginDialog->setMinimumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacerTop);

        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName("stackedWidget");
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        verticalLayout_2 = new QVBoxLayout(loginPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(loginPage);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label, 0, Qt::AlignmentFlag::AlignHCenter);

        verticalSpacerMiddle1 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacerMiddle1);

        horizontalLayoutCenter = new QHBoxLayout();
        horizontalLayoutCenter->setSpacing(20);
        horizontalLayoutCenter->setObjectName("horizontalLayoutCenter");
        horizontalSpacerLeft = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCenter->addItem(horizontalSpacerLeft);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(12);
        formLayout->setVerticalSpacing(12);
        lblUsername = new QLabel(loginPage);
        lblUsername->setObjectName("lblUsername");
        lblUsername->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, lblUsername);

        leUsername = new QLineEdit(loginPage);
        leUsername->setObjectName("leUsername");
        leUsername->setMinimumSize(QSize(200, 35));
        leUsername->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, leUsername);

        lblPassword = new QLabel(loginPage);
        lblPassword->setObjectName("lblPassword");
        lblPassword->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, lblPassword);

        lePassword = new QLineEdit(loginPage);
        lePassword->setObjectName("lePassword");
        lePassword->setMinimumSize(QSize(200, 35));
        lePassword->setEchoMode(QLineEdit::EchoMode::Password);
        lePassword->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lePassword);


        horizontalLayoutCenter->addLayout(formLayout);

        horizontalSpacerRight = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCenter->addItem(horizontalSpacerRight);


        verticalLayout_2->addLayout(horizontalLayoutCenter);

        verticalSpacerMiddle2 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacerMiddle2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnLogin = new QPushButton(loginPage);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(btnLogin);

        btnCancel = new QPushButton(loginPage);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_2 = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnSwitchToSignup = new QPushButton(loginPage);
        btnSwitchToSignup->setObjectName("btnSwitchToSignup");

        horizontalLayout_2->addWidget(btnSwitchToSignup);

        horizontalSpacer_4 = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacerBottom);

        lblVersion = new QLabel(loginPage);
        lblVersion->setObjectName("lblVersion");
        lblVersion->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(lblVersion, 0, Qt::AlignmentFlag::AlignHCenter);

        stackedWidget->addWidget(loginPage);
        signupPage = new QWidget();
        signupPage->setObjectName("signupPage");
        verticalLayout_3 = new QVBoxLayout(signupPage);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(signupPage);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_2, 0, Qt::AlignmentFlag::AlignHCenter);

        verticalSpacerMiddle1_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacerMiddle1_2);

        horizontalLayoutCenter_2 = new QHBoxLayout();
        horizontalLayoutCenter_2->setSpacing(20);
        horizontalLayoutCenter_2->setObjectName("horizontalLayoutCenter_2");
        horizontalSpacerLeft_2 = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCenter_2->addItem(horizontalSpacerLeft_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setHorizontalSpacing(12);
        formLayout_2->setVerticalSpacing(12);
        lblSignupUsername = new QLabel(signupPage);
        lblSignupUsername->setObjectName("lblSignupUsername");
        lblSignupUsername->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, lblSignupUsername);

        leSignupUsername = new QLineEdit(signupPage);
        leSignupUsername->setObjectName("leSignupUsername");
        leSignupUsername->setMinimumSize(QSize(200, 35));
        leSignupUsername->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, leSignupUsername);

        lblSignupPassword = new QLabel(signupPage);
        lblSignupPassword->setObjectName("lblSignupPassword");
        lblSignupPassword->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, lblSignupPassword);

        leSignupPassword = new QLineEdit(signupPage);
        leSignupPassword->setObjectName("leSignupPassword");
        leSignupPassword->setMinimumSize(QSize(200, 35));
        leSignupPassword->setEchoMode(QLineEdit::EchoMode::Password);
        leSignupPassword->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, leSignupPassword);

        lblConfirmPassword = new QLabel(signupPage);
        lblConfirmPassword->setObjectName("lblConfirmPassword");
        lblConfirmPassword->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, lblConfirmPassword);

        leConfirmPassword = new QLineEdit(signupPage);
        leConfirmPassword->setObjectName("leConfirmPassword");
        leConfirmPassword->setMinimumSize(QSize(200, 35));
        leConfirmPassword->setEchoMode(QLineEdit::EchoMode::Password);
        leConfirmPassword->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout_2->setWidget(2, QFormLayout::ItemRole::FieldRole, leConfirmPassword);

        lblRole = new QLabel(signupPage);
        lblRole->setObjectName("lblRole");
        lblRole->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout_2->setWidget(3, QFormLayout::ItemRole::LabelRole, lblRole);

        cbRole = new QComboBox(signupPage);
        cbRole->addItem(QString());
        cbRole->addItem(QString());
        cbRole->addItem(QString());
        cbRole->setObjectName("cbRole");

        formLayout_2->setWidget(3, QFormLayout::ItemRole::FieldRole, cbRole);


        horizontalLayoutCenter_2->addLayout(formLayout_2);

        horizontalSpacerRight_2 = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCenter_2->addItem(horizontalSpacerRight_2);


        verticalLayout_3->addLayout(horizontalLayoutCenter_2);

        verticalSpacerMiddle2_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacerMiddle2_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(20);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_5 = new QSpacerItem(120, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        btnSignup = new QPushButton(signupPage);
        btnSignup->setObjectName("btnSignup");
        btnSignup->setMinimumSize(QSize(120, 40));

        horizontalLayout_3->addWidget(btnSignup);

        btnCancelSignup = new QPushButton(signupPage);
        btnCancelSignup->setObjectName("btnCancelSignup");
        btnCancelSignup->setMinimumSize(QSize(120, 40));

        horizontalLayout_3->addWidget(btnCancelSignup);

        horizontalSpacer_6 = new QSpacerItem(120, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_7 = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        btnSwitchToLogin = new QPushButton(signupPage);
        btnSwitchToLogin->setObjectName("btnSwitchToLogin");

        horizontalLayout_4->addWidget(btnSwitchToLogin);

        horizontalSpacer_8 = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalSpacerBottom_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacerBottom_2);

        stackedWidget->addWidget(signupPage);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Connexion", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "           Syst\303\250me de Gestion Logistique          ", nullptr));
        lblUsername->setText(QCoreApplication::translate("LoginDialog", "Identifiant:", nullptr));
        lblPassword->setText(QCoreApplication::translate("LoginDialog", "Mot de passe:", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Se connecter", nullptr));
        btnCancel->setText(QCoreApplication::translate("LoginDialog", "Annuler", nullptr));
        btnSwitchToSignup->setText(QCoreApplication::translate("LoginDialog", "Cr\303\251er un nouveau compte", nullptr));
        lblVersion->setText(QCoreApplication::translate("LoginDialog", "          Version 1.6 - MADE BY NADHIR.TR       ", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "           Cr\303\251ation de Compte          ", nullptr));
        lblSignupUsername->setText(QCoreApplication::translate("LoginDialog", "Nom d'utilisateur:", nullptr));
        lblSignupPassword->setText(QCoreApplication::translate("LoginDialog", "Mot de passe:", nullptr));
        lblConfirmPassword->setText(QCoreApplication::translate("LoginDialog", "Confirmer mot de passe:", nullptr));
        lblRole->setText(QCoreApplication::translate("LoginDialog", "R\303\264le:", nullptr));
        cbRole->setItemText(0, QCoreApplication::translate("LoginDialog", "Administrateur", nullptr));
        cbRole->setItemText(1, QCoreApplication::translate("LoginDialog", "Gestionnaire", nullptr));
        cbRole->setItemText(2, QCoreApplication::translate("LoginDialog", "Livreur", nullptr));

        btnSignup->setText(QCoreApplication::translate("LoginDialog", "S'inscrire", nullptr));
        btnCancelSignup->setText(QCoreApplication::translate("LoginDialog", "Annuler", nullptr));
        btnSwitchToLogin->setText(QCoreApplication::translate("LoginDialog", "D\303\251j\303\240 un compte? Se connecter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
