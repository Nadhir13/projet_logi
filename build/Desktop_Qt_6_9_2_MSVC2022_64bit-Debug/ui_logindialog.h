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
    QLabel *label;
    QLabel *lblImage;
    QFormLayout *formLayout;
    QLabel *lblUsername;
    QLineEdit *leUsername;
    QLabel *lblPassword;
    QLineEdit *lePassword;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnLogin;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblVersion;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 400);
        LoginDialog->setMinimumSize(QSize(400, 400));
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        lblImage = new QLabel(LoginDialog);
        lblImage->setObjectName("lblImage");
        lblImage->setMinimumSize(QSize(0, 150));
        lblImage->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblImage);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        lblUsername = new QLabel(LoginDialog);
        lblUsername->setObjectName("lblUsername");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, lblUsername);

        leUsername = new QLineEdit(LoginDialog);
        leUsername->setObjectName("leUsername");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, leUsername);

        lblPassword = new QLabel(LoginDialog);
        lblPassword->setObjectName("lblPassword");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, lblPassword);

        lePassword = new QLineEdit(LoginDialog);
        lePassword->setObjectName("lePassword");
        lePassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lePassword);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnLogin = new QPushButton(LoginDialog);
        btnLogin->setObjectName("btnLogin");

        horizontalLayout->addWidget(btnLogin);

        btnCancel = new QPushButton(LoginDialog);
        btnCancel->setObjectName("btnCancel");

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        lblVersion = new QLabel(LoginDialog);
        lblVersion->setObjectName("lblVersion");
        lblVersion->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblVersion);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Connexion", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">Syst\303\250me de Gestion Logistique</span></p></body></html>", nullptr));
        lblImage->setText(QCoreApplication::translate("LoginDialog", "IMAGE WILL BE PLACED HERE", nullptr));
        lblUsername->setText(QCoreApplication::translate("LoginDialog", "Identifiant:", nullptr));
        lblPassword->setText(QCoreApplication::translate("LoginDialog", "Mot de passe:", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Se connecter", nullptr));
        btnCancel->setText(QCoreApplication::translate("LoginDialog", "Annuler", nullptr));
        lblVersion->setText(QCoreApplication::translate("LoginDialog", "Version 1.0 - Septembre 2025", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
