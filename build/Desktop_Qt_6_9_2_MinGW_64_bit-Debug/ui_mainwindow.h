/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabClients;
    QVBoxLayout *vlc;
    QFormLayout *formClient;
    QLabel *label;
    QLineEdit *leNom;
    QLabel *label1;
    QLineEdit *lePrenom;
    QLabel *label2;
    QLineEdit *leTel;
    QLabel *label3;
    QLineEdit *leEmail;
    QLabel *label4;
    QLineEdit *leAdr;
    QLabel *label5;
    QComboBox *cbStatut;
    QHBoxLayout *btnRowClient;
    QPushButton *btnAddClient;
    QPushButton *btnUpdClient;
    QPushButton *btnDelClient;
    QPushButton *btnRefClient;
    QTableWidget *tblClients;
    QWidget *tabOrders;
    QVBoxLayout *vlo;
    QFormLayout *formOrder;
    QLabel *label6;
    QComboBox *cbClient;
    QLabel *label7;
    QComboBox *cbEtat;
    QLabel *label8;
    QDoubleSpinBox *dsMontant;
    QLabel *label9;
    QLineEdit *leAdrLiv;
    QHBoxLayout *btnRowOrder;
    QPushButton *btnAddOrd;
    QPushButton *btnUpdOrd;
    QPushButton *btnDelOrd;
    QPushButton *btnRefOrd;
    QTableWidget *tblOrders;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(615, 474);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabClients = new QWidget();
        tabClients->setObjectName("tabClients");
        vlc = new QVBoxLayout(tabClients);
        vlc->setObjectName("vlc");
        formClient = new QFormLayout();
        formClient->setObjectName("formClient");
        label = new QLabel(tabClients);
        label->setObjectName("label");

        formClient->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        leNom = new QLineEdit(tabClients);
        leNom->setObjectName("leNom");

        formClient->setWidget(0, QFormLayout::ItemRole::FieldRole, leNom);

        label1 = new QLabel(tabClients);
        label1->setObjectName("label1");

        formClient->setWidget(1, QFormLayout::ItemRole::LabelRole, label1);

        lePrenom = new QLineEdit(tabClients);
        lePrenom->setObjectName("lePrenom");

        formClient->setWidget(1, QFormLayout::ItemRole::FieldRole, lePrenom);

        label2 = new QLabel(tabClients);
        label2->setObjectName("label2");

        formClient->setWidget(2, QFormLayout::ItemRole::LabelRole, label2);

        leTel = new QLineEdit(tabClients);
        leTel->setObjectName("leTel");

        formClient->setWidget(2, QFormLayout::ItemRole::FieldRole, leTel);

        label3 = new QLabel(tabClients);
        label3->setObjectName("label3");

        formClient->setWidget(3, QFormLayout::ItemRole::LabelRole, label3);

        leEmail = new QLineEdit(tabClients);
        leEmail->setObjectName("leEmail");

        formClient->setWidget(3, QFormLayout::ItemRole::FieldRole, leEmail);

        label4 = new QLabel(tabClients);
        label4->setObjectName("label4");

        formClient->setWidget(4, QFormLayout::ItemRole::LabelRole, label4);

        leAdr = new QLineEdit(tabClients);
        leAdr->setObjectName("leAdr");

        formClient->setWidget(4, QFormLayout::ItemRole::FieldRole, leAdr);

        label5 = new QLabel(tabClients);
        label5->setObjectName("label5");

        formClient->setWidget(5, QFormLayout::ItemRole::LabelRole, label5);

        cbStatut = new QComboBox(tabClients);
        cbStatut->addItem(QString());
        cbStatut->addItem(QString());
        cbStatut->setObjectName("cbStatut");

        formClient->setWidget(5, QFormLayout::ItemRole::FieldRole, cbStatut);


        vlc->addLayout(formClient);

        btnRowClient = new QHBoxLayout();
        btnRowClient->setObjectName("btnRowClient");
        btnAddClient = new QPushButton(tabClients);
        btnAddClient->setObjectName("btnAddClient");

        btnRowClient->addWidget(btnAddClient);

        btnUpdClient = new QPushButton(tabClients);
        btnUpdClient->setObjectName("btnUpdClient");

        btnRowClient->addWidget(btnUpdClient);

        btnDelClient = new QPushButton(tabClients);
        btnDelClient->setObjectName("btnDelClient");

        btnRowClient->addWidget(btnDelClient);

        btnRefClient = new QPushButton(tabClients);
        btnRefClient->setObjectName("btnRefClient");

        btnRowClient->addWidget(btnRefClient);


        vlc->addLayout(btnRowClient);

        tblClients = new QTableWidget(tabClients);
        tblClients->setObjectName("tblClients");
        tblClients->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tblClients->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        vlc->addWidget(tblClients);

        tabWidget->addTab(tabClients, QString());
        tabOrders = new QWidget();
        tabOrders->setObjectName("tabOrders");
        vlo = new QVBoxLayout(tabOrders);
        vlo->setObjectName("vlo");
        formOrder = new QFormLayout();
        formOrder->setObjectName("formOrder");
        label6 = new QLabel(tabOrders);
        label6->setObjectName("label6");

        formOrder->setWidget(0, QFormLayout::ItemRole::LabelRole, label6);

        cbClient = new QComboBox(tabOrders);
        cbClient->setObjectName("cbClient");

        formOrder->setWidget(0, QFormLayout::ItemRole::FieldRole, cbClient);

        label7 = new QLabel(tabOrders);
        label7->setObjectName("label7");

        formOrder->setWidget(1, QFormLayout::ItemRole::LabelRole, label7);

        cbEtat = new QComboBox(tabOrders);
        cbEtat->addItem(QString());
        cbEtat->addItem(QString());
        cbEtat->addItem(QString());
        cbEtat->addItem(QString());
        cbEtat->setObjectName("cbEtat");

        formOrder->setWidget(1, QFormLayout::ItemRole::FieldRole, cbEtat);

        label8 = new QLabel(tabOrders);
        label8->setObjectName("label8");

        formOrder->setWidget(2, QFormLayout::ItemRole::LabelRole, label8);

        dsMontant = new QDoubleSpinBox(tabOrders);
        dsMontant->setObjectName("dsMontant");
        dsMontant->setDecimals(3);

        formOrder->setWidget(2, QFormLayout::ItemRole::FieldRole, dsMontant);

        label9 = new QLabel(tabOrders);
        label9->setObjectName("label9");

        formOrder->setWidget(3, QFormLayout::ItemRole::LabelRole, label9);

        leAdrLiv = new QLineEdit(tabOrders);
        leAdrLiv->setObjectName("leAdrLiv");

        formOrder->setWidget(3, QFormLayout::ItemRole::FieldRole, leAdrLiv);


        vlo->addLayout(formOrder);

        btnRowOrder = new QHBoxLayout();
        btnRowOrder->setObjectName("btnRowOrder");
        btnAddOrd = new QPushButton(tabOrders);
        btnAddOrd->setObjectName("btnAddOrd");

        btnRowOrder->addWidget(btnAddOrd);

        btnUpdOrd = new QPushButton(tabOrders);
        btnUpdOrd->setObjectName("btnUpdOrd");

        btnRowOrder->addWidget(btnUpdOrd);

        btnDelOrd = new QPushButton(tabOrders);
        btnDelOrd->setObjectName("btnDelOrd");

        btnRowOrder->addWidget(btnDelOrd);

        btnRefOrd = new QPushButton(tabOrders);
        btnRefOrd->setObjectName("btnRefOrd");

        btnRowOrder->addWidget(btnRefOrd);


        vlo->addLayout(btnRowOrder);

        tblOrders = new QTableWidget(tabOrders);
        tblOrders->setObjectName("tblOrders");
        tblOrders->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tblOrders->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        vlo->addWidget(tblOrders);

        tabWidget->addTab(tabOrders, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "projet_logi", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Tel", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "Adr", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        cbStatut->setItemText(0, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        cbStatut->setItemText(1, QCoreApplication::translate("MainWindow", "INACTIVE", nullptr));

        btnAddClient->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdClient->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelClient->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnRefClient->setText(QCoreApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClients), QCoreApplication::translate("MainWindow", "Clients", nullptr));
        label6->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        label7->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));
        cbEtat->setItemText(0, QCoreApplication::translate("MainWindow", "EN_ATTENTE", nullptr));
        cbEtat->setItemText(1, QCoreApplication::translate("MainWindow", "EN_COURS", nullptr));
        cbEtat->setItemText(2, QCoreApplication::translate("MainWindow", "LIVREE", nullptr));
        cbEtat->setItemText(3, QCoreApplication::translate("MainWindow", "ANNULEE", nullptr));

        label8->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        label9->setText(QCoreApplication::translate("MainWindow", "Adr Liv.", nullptr));
        btnAddOrd->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdOrd->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelOrd->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnRefOrd->setText(QCoreApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOrders), QCoreApplication::translate("MainWindow", "Commandes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
