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
    QLabel *lblNom;
    QLineEdit *leNom;
    QLabel *lblPrenom;
    QLineEdit *lePrenom;
    QLabel *lblTel;
    QLineEdit *leTel;
    QLabel *lblEmail;
    QLineEdit *leEmail;
    QLabel *lblAdr;
    QLineEdit *leAdr;
    QLabel *lblStatut;
    QComboBox *cbStatut;
    QHBoxLayout *filterRowClient;
    QLineEdit *leSearchClient;
    QComboBox *cbStatutFilter;
    QComboBox *cbClientSort;
    QHBoxLayout *btnRowClient;
    QPushButton *btnAddClient;
    QPushButton *btnUpdClient;
    QPushButton *btnDelClient;
    QPushButton *btnRefClient;
    QTableWidget *tblClients;
    QWidget *clientChartContainer;
    QWidget *tabOrders;
    QVBoxLayout *vlo;
    QFormLayout *formOrder;
    QLabel *lblClient;
    QComboBox *cbClient;
    QLabel *lblEtat;
    QComboBox *cbEtat;
    QLabel *lblMontant;
    QDoubleSpinBox *dsMontant;
    QLabel *lblAdrLiv;
    QLineEdit *leAdrLiv;
    QHBoxLayout *filterRowOrder;
    QLineEdit *leSearchOrder;
    QComboBox *cbEtatFilter;
    QComboBox *cbOrderSort;
    QHBoxLayout *btnRowOrder;
    QPushButton *btnAddOrd;
    QPushButton *btnUpdOrd;
    QPushButton *btnDelOrd;
    QPushButton *btnRefOrd;
    QPushButton *btnPdfOrd;
    QTableWidget *tblOrders;
    QWidget *orderChartContainer;

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
        lblNom = new QLabel(tabClients);
        lblNom->setObjectName("lblNom");

        formClient->setWidget(0, QFormLayout::ItemRole::LabelRole, lblNom);

        leNom = new QLineEdit(tabClients);
        leNom->setObjectName("leNom");

        formClient->setWidget(0, QFormLayout::ItemRole::FieldRole, leNom);

        lblPrenom = new QLabel(tabClients);
        lblPrenom->setObjectName("lblPrenom");

        formClient->setWidget(1, QFormLayout::ItemRole::LabelRole, lblPrenom);

        lePrenom = new QLineEdit(tabClients);
        lePrenom->setObjectName("lePrenom");

        formClient->setWidget(1, QFormLayout::ItemRole::FieldRole, lePrenom);

        lblTel = new QLabel(tabClients);
        lblTel->setObjectName("lblTel");

        formClient->setWidget(2, QFormLayout::ItemRole::LabelRole, lblTel);

        leTel = new QLineEdit(tabClients);
        leTel->setObjectName("leTel");

        formClient->setWidget(2, QFormLayout::ItemRole::FieldRole, leTel);

        lblEmail = new QLabel(tabClients);
        lblEmail->setObjectName("lblEmail");

        formClient->setWidget(3, QFormLayout::ItemRole::LabelRole, lblEmail);

        leEmail = new QLineEdit(tabClients);
        leEmail->setObjectName("leEmail");

        formClient->setWidget(3, QFormLayout::ItemRole::FieldRole, leEmail);

        lblAdr = new QLabel(tabClients);
        lblAdr->setObjectName("lblAdr");

        formClient->setWidget(4, QFormLayout::ItemRole::LabelRole, lblAdr);

        leAdr = new QLineEdit(tabClients);
        leAdr->setObjectName("leAdr");

        formClient->setWidget(4, QFormLayout::ItemRole::FieldRole, leAdr);

        lblStatut = new QLabel(tabClients);
        lblStatut->setObjectName("lblStatut");

        formClient->setWidget(5, QFormLayout::ItemRole::LabelRole, lblStatut);

        cbStatut = new QComboBox(tabClients);
        cbStatut->addItem(QString());
        cbStatut->addItem(QString());
        cbStatut->setObjectName("cbStatut");

        formClient->setWidget(5, QFormLayout::ItemRole::FieldRole, cbStatut);


        vlc->addLayout(formClient);

        filterRowClient = new QHBoxLayout();
        filterRowClient->setObjectName("filterRowClient");
        leSearchClient = new QLineEdit(tabClients);
        leSearchClient->setObjectName("leSearchClient");

        filterRowClient->addWidget(leSearchClient);

        cbStatutFilter = new QComboBox(tabClients);
        cbStatutFilter->addItem(QString());
        cbStatutFilter->addItem(QString());
        cbStatutFilter->addItem(QString());
        cbStatutFilter->setObjectName("cbStatutFilter");

        filterRowClient->addWidget(cbStatutFilter);

        cbClientSort = new QComboBox(tabClients);
        cbClientSort->addItem(QString());
        cbClientSort->addItem(QString());
        cbClientSort->addItem(QString());
        cbClientSort->setObjectName("cbClientSort");

        filterRowClient->addWidget(cbClientSort);


        vlc->addLayout(filterRowClient);

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

        clientChartContainer = new QWidget(tabClients);
        clientChartContainer->setObjectName("clientChartContainer");

        vlc->addWidget(clientChartContainer);

        tabWidget->addTab(tabClients, QString());
        tabOrders = new QWidget();
        tabOrders->setObjectName("tabOrders");
        vlo = new QVBoxLayout(tabOrders);
        vlo->setObjectName("vlo");
        formOrder = new QFormLayout();
        formOrder->setObjectName("formOrder");
        lblClient = new QLabel(tabOrders);
        lblClient->setObjectName("lblClient");

        formOrder->setWidget(0, QFormLayout::ItemRole::LabelRole, lblClient);

        cbClient = new QComboBox(tabOrders);
        cbClient->setObjectName("cbClient");

        formOrder->setWidget(0, QFormLayout::ItemRole::FieldRole, cbClient);

        lblEtat = new QLabel(tabOrders);
        lblEtat->setObjectName("lblEtat");

        formOrder->setWidget(1, QFormLayout::ItemRole::LabelRole, lblEtat);

        cbEtat = new QComboBox(tabOrders);
        cbEtat->addItem(QString());
        cbEtat->addItem(QString());
        cbEtat->addItem(QString());
        cbEtat->addItem(QString());
        cbEtat->setObjectName("cbEtat");

        formOrder->setWidget(1, QFormLayout::ItemRole::FieldRole, cbEtat);

        lblMontant = new QLabel(tabOrders);
        lblMontant->setObjectName("lblMontant");

        formOrder->setWidget(2, QFormLayout::ItemRole::LabelRole, lblMontant);

        dsMontant = new QDoubleSpinBox(tabOrders);
        dsMontant->setObjectName("dsMontant");
        dsMontant->setDecimals(3);

        formOrder->setWidget(2, QFormLayout::ItemRole::FieldRole, dsMontant);

        lblAdrLiv = new QLabel(tabOrders);
        lblAdrLiv->setObjectName("lblAdrLiv");

        formOrder->setWidget(3, QFormLayout::ItemRole::LabelRole, lblAdrLiv);

        leAdrLiv = new QLineEdit(tabOrders);
        leAdrLiv->setObjectName("leAdrLiv");

        formOrder->setWidget(3, QFormLayout::ItemRole::FieldRole, leAdrLiv);


        vlo->addLayout(formOrder);

        filterRowOrder = new QHBoxLayout();
        filterRowOrder->setObjectName("filterRowOrder");
        leSearchOrder = new QLineEdit(tabOrders);
        leSearchOrder->setObjectName("leSearchOrder");

        filterRowOrder->addWidget(leSearchOrder);

        cbEtatFilter = new QComboBox(tabOrders);
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->setObjectName("cbEtatFilter");

        filterRowOrder->addWidget(cbEtatFilter);

        cbOrderSort = new QComboBox(tabOrders);
        cbOrderSort->addItem(QString());
        cbOrderSort->addItem(QString());
        cbOrderSort->addItem(QString());
        cbOrderSort->setObjectName("cbOrderSort");

        filterRowOrder->addWidget(cbOrderSort);


        vlo->addLayout(filterRowOrder);

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

        btnPdfOrd = new QPushButton(tabOrders);
        btnPdfOrd->setObjectName("btnPdfOrd");

        btnRowOrder->addWidget(btnPdfOrd);


        vlo->addLayout(btnRowOrder);

        tblOrders = new QTableWidget(tabOrders);
        tblOrders->setObjectName("tblOrders");
        tblOrders->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tblOrders->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        vlo->addWidget(tblOrders);

        orderChartContainer = new QWidget(tabOrders);
        orderChartContainer->setObjectName("orderChartContainer");

        vlo->addWidget(orderChartContainer);

        tabWidget->addTab(tabOrders, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "projet_logi", nullptr));
        lblNom->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        lblPrenom->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        lblTel->setText(QCoreApplication::translate("MainWindow", "Tel", nullptr));
        lblEmail->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        lblAdr->setText(QCoreApplication::translate("MainWindow", "Adr", nullptr));
        lblStatut->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        cbStatut->setItemText(0, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        cbStatut->setItemText(1, QCoreApplication::translate("MainWindow", "INACTIVE", nullptr));

        leSearchClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (nom, pr\303\251nom, email)", nullptr));
        cbStatutFilter->setItemText(0, QCoreApplication::translate("MainWindow", "Tous", nullptr));
        cbStatutFilter->setItemText(1, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        cbStatutFilter->setItemText(2, QCoreApplication::translate("MainWindow", "INACTIVE", nullptr));

        cbClientSort->setItemText(0, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        cbClientSort->setItemText(1, QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        cbClientSort->setItemText(2, QCoreApplication::translate("MainWindow", "Cr\303\251\303\251", nullptr));

        btnAddClient->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdClient->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelClient->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnRefClient->setText(QCoreApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClients), QCoreApplication::translate("MainWindow", "Clients", nullptr));
        lblClient->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        lblEtat->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));
        cbEtat->setItemText(0, QCoreApplication::translate("MainWindow", "EN_ATTENTE", nullptr));
        cbEtat->setItemText(1, QCoreApplication::translate("MainWindow", "EN_COURS", nullptr));
        cbEtat->setItemText(2, QCoreApplication::translate("MainWindow", "LIVREE", nullptr));
        cbEtat->setItemText(3, QCoreApplication::translate("MainWindow", "ANNULEE", nullptr));

        lblMontant->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        lblAdrLiv->setText(QCoreApplication::translate("MainWindow", "Adr Liv.", nullptr));
        leSearchOrder->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (\303\251tat, adr)", nullptr));
        cbEtatFilter->setItemText(0, QCoreApplication::translate("MainWindow", "Tous", nullptr));
        cbEtatFilter->setItemText(1, QCoreApplication::translate("MainWindow", "EN_ATTENTE", nullptr));
        cbEtatFilter->setItemText(2, QCoreApplication::translate("MainWindow", "EN_COURS", nullptr));
        cbEtatFilter->setItemText(3, QCoreApplication::translate("MainWindow", "LIVREE", nullptr));
        cbEtatFilter->setItemText(4, QCoreApplication::translate("MainWindow", "ANNULEE", nullptr));

        cbOrderSort->setItemText(0, QCoreApplication::translate("MainWindow", "Date", nullptr));
        cbOrderSort->setItemText(1, QCoreApplication::translate("MainWindow", "Montant", nullptr));
        cbOrderSort->setItemText(2, QCoreApplication::translate("MainWindow", "\303\211tat", nullptr));

        btnAddOrd->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdOrd->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelOrd->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnRefOrd->setText(QCoreApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
        btnPdfOrd->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOrders), QCoreApplication::translate("MainWindow", "Commandes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
