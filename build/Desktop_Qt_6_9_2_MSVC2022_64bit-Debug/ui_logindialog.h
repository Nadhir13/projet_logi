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
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacerTop;
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
    QSpacerItem *verticalSpacerBottom;
    QLabel *lblVersion;
    QLabel *lblBackground;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(800, 600);
        LoginDialog->setMinimumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacerTop = new QSpacerItem(20, 80, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacerTop);

        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacerMiddle1 = new QSpacerItem(20, 50, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacerMiddle1);

        horizontalLayoutCenter = new QHBoxLayout();
        horizontalLayoutCenter->setSpacing(20);
        horizontalLayoutCenter->setObjectName("horizontalLayoutCenter");
        horizontalSpacerLeft = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCenter->addItem(horizontalSpacerLeft);

        formLayout = new QFormLayout();
        formLayout->setSpacing(12);
        formLayout->setObjectName("formLayout");
        lblUsername = new QLabel(LoginDialog);
        lblUsername->setObjectName("lblUsername");
        lblUsername->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, lblUsername);

        leUsername = new QLineEdit(LoginDialog);
        leUsername->setObjectName("leUsername");
        leUsername->setMinimumSize(QSize(200, 35));
        leUsername->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, leUsername);

        lblPassword = new QLabel(LoginDialog);
        lblPassword->setObjectName("lblPassword");
        lblPassword->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, lblPassword);

        lePassword = new QLineEdit(LoginDialog);
        lePassword->setObjectName("lePassword");
        lePassword->setEchoMode(QLineEdit::Password);
        lePassword->setMinimumSize(QSize(200, 35));
        lePassword->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lePassword);


        horizontalLayoutCenter->addLayout(formLayout);

        horizontalSpacerRight = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCenter->addItem(horizontalSpacerRight);


        verticalLayout->addLayout(horizontalLayoutCenter);

        verticalSpacerMiddle2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacerMiddle2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnLogin = new QPushButton(LoginDialog);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(btnLogin);

        btnCancel = new QPushButton(LoginDialog);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacerBottom = new QSpacerItem(20, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacerBottom);

        lblVersion = new QLabel(LoginDialog);
        lblVersion->setObjectName("lblVersion");
        lblVersion->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblVersion);

        lblBackground = new QLabel(LoginDialog);
        lblBackground->setObjectName("lblBackground");
        lblBackground->setVisible(false);

        verticalLayout->addWidget(lblBackground);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Connexion", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Syst\303\250me de Gestion Logistique", nullptr));
        lblUsername->setText(QCoreApplication::translate("LoginDialog", "Identifiant:", nullptr));
        lblPassword->setText(QCoreApplication::translate("LoginDialog", "Mot de passe:", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Se connecter", nullptr));
        btnCancel->setText(QCoreApplication::translate("LoginDialog", "Annuler", nullptr));
        lblVersion->setText(QCoreApplication::translate("LoginDialog", "Version 1.0 - Septembre 2025", nullptr));
        lblBackground->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
