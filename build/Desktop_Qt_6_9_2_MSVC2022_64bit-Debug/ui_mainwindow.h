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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
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
    QLineEdit *leEmailFilter;
    QComboBox *cbStatutFilter;
    QComboBox *cbClientSort;
    QHBoxLayout *btnRowClient;
    QPushButton *btnAddClient;
    QPushButton *btnUpdClient;
    QPushButton *btnDelClient;
    QPushButton *btnRefClient;
    QPushButton *btnClientStats;
    QPushButton *btnExportExcel;
    QPushButton *btnUpdateCategory;
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
    QLabel *lblPriority;
    QComboBox *cbPriority;
    QHBoxLayout *filterRowOrder;
    QLineEdit *leSearchOrder;
    QComboBox *cbClientFilter;
    QComboBox *cbEtatFilter;
    QHBoxLayout *amountFilterLayout;
    QLabel *lblMinAmount;
    QDoubleSpinBox *dsMinAmount;
    QLabel *lblMaxAmount;
    QDoubleSpinBox *dsMaxAmount;
    QComboBox *cbOrderSort;
    QHBoxLayout *btnRowOrder;
    QPushButton *btnAddOrd;
    QPushButton *btnUpdOrd;
    QPushButton *btnDelOrd;
    QPushButton *btnRefOrd;
    QPushButton *btnPdfOrd;
    QPushButton *btnOrderStats;
    QPushButton *btnUpdatePriority;
    QTableWidget *tblOrders;
    QWidget *orderChartContainer;
    QWidget *tabUsers;
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *stackedUser;
    QWidget *pageUserView;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *leSearchUser;
    QComboBox *cbUserRoleFilter;
    QComboBox *cbUserStatusFilter;
    QComboBox *cbUserSort;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnAddUser;
    QPushButton *btnRefUser;
    QPushButton *btnChangePassword;
    QTableWidget *tblUsers;
    QWidget *userChartContainer;
    QWidget *pageUserEdit;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout_3;
    QLabel *lblUserUsername;
    QLineEdit *leUserUsername;
    QLabel *lblUserPassword;
    QLineEdit *leUserPassword;
    QLabel *lblUserRole;
    QComboBox *cbUserRole;
    QLabel *lblUserStatus;
    QComboBox *cbUserStatus;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnUpdUser;
    QPushButton *btnDelUser;
    QPushButton *btnCancelUser;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
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

        leEmailFilter = new QLineEdit(tabClients);
        leEmailFilter->setObjectName("leEmailFilter");

        filterRowClient->addWidget(leEmailFilter);

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

        btnClientStats = new QPushButton(tabClients);
        btnClientStats->setObjectName("btnClientStats");

        btnRowClient->addWidget(btnClientStats);

        btnExportExcel = new QPushButton(tabClients);
        btnExportExcel->setObjectName("btnExportExcel");

        btnRowClient->addWidget(btnExportExcel);

        btnUpdateCategory = new QPushButton(tabClients);
        btnUpdateCategory->setObjectName("btnUpdateCategory");

        btnRowClient->addWidget(btnUpdateCategory);


        vlc->addLayout(btnRowClient);

        tblClients = new QTableWidget(tabClients);
        if (tblClients->columnCount() < 8)
            tblClients->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tblClients->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tblClients->setObjectName("tblClients");
        tblClients->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tblClients->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tblClients->setColumnCount(8);
        tblClients->horizontalHeader()->setVisible(true);
        tblClients->verticalHeader()->setVisible(true);

        vlc->addWidget(tblClients);

        clientChartContainer = new QWidget(tabClients);
        clientChartContainer->setObjectName("clientChartContainer");
        clientChartContainer->setMinimumSize(QSize(0, 200));

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
        dsMontant->setMaximum(1000000.000000000000000);

        formOrder->setWidget(2, QFormLayout::ItemRole::FieldRole, dsMontant);

        lblAdrLiv = new QLabel(tabOrders);
        lblAdrLiv->setObjectName("lblAdrLiv");

        formOrder->setWidget(3, QFormLayout::ItemRole::LabelRole, lblAdrLiv);

        leAdrLiv = new QLineEdit(tabOrders);
        leAdrLiv->setObjectName("leAdrLiv");

        formOrder->setWidget(3, QFormLayout::ItemRole::FieldRole, leAdrLiv);

        lblPriority = new QLabel(tabOrders);
        lblPriority->setObjectName("lblPriority");

        formOrder->setWidget(4, QFormLayout::ItemRole::LabelRole, lblPriority);

        cbPriority = new QComboBox(tabOrders);
        cbPriority->addItem(QString());
        cbPriority->addItem(QString());
        cbPriority->addItem(QString());
        cbPriority->addItem(QString());
        cbPriority->setObjectName("cbPriority");

        formOrder->setWidget(4, QFormLayout::ItemRole::FieldRole, cbPriority);


        vlo->addLayout(formOrder);

        filterRowOrder = new QHBoxLayout();
        filterRowOrder->setObjectName("filterRowOrder");
        leSearchOrder = new QLineEdit(tabOrders);
        leSearchOrder->setObjectName("leSearchOrder");

        filterRowOrder->addWidget(leSearchOrder);

        cbClientFilter = new QComboBox(tabOrders);
        cbClientFilter->addItem(QString());
        cbClientFilter->setObjectName("cbClientFilter");

        filterRowOrder->addWidget(cbClientFilter);

        cbEtatFilter = new QComboBox(tabOrders);
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->addItem(QString());
        cbEtatFilter->setObjectName("cbEtatFilter");

        filterRowOrder->addWidget(cbEtatFilter);

        amountFilterLayout = new QHBoxLayout();
        amountFilterLayout->setObjectName("amountFilterLayout");
        lblMinAmount = new QLabel(tabOrders);
        lblMinAmount->setObjectName("lblMinAmount");

        amountFilterLayout->addWidget(lblMinAmount);

        dsMinAmount = new QDoubleSpinBox(tabOrders);
        dsMinAmount->setObjectName("dsMinAmount");
        dsMinAmount->setDecimals(3);
        dsMinAmount->setMaximum(1000000.000000000000000);

        amountFilterLayout->addWidget(dsMinAmount);

        lblMaxAmount = new QLabel(tabOrders);
        lblMaxAmount->setObjectName("lblMaxAmount");

        amountFilterLayout->addWidget(lblMaxAmount);

        dsMaxAmount = new QDoubleSpinBox(tabOrders);
        dsMaxAmount->setObjectName("dsMaxAmount");
        dsMaxAmount->setDecimals(3);
        dsMaxAmount->setMaximum(1000000.000000000000000);

        amountFilterLayout->addWidget(dsMaxAmount);


        filterRowOrder->addLayout(amountFilterLayout);

        cbOrderSort = new QComboBox(tabOrders);
        cbOrderSort->addItem(QString());
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

        btnOrderStats = new QPushButton(tabOrders);
        btnOrderStats->setObjectName("btnOrderStats");

        btnRowOrder->addWidget(btnOrderStats);

        btnUpdatePriority = new QPushButton(tabOrders);
        btnUpdatePriority->setObjectName("btnUpdatePriority");

        btnRowOrder->addWidget(btnUpdatePriority);


        vlo->addLayout(btnRowOrder);

        tblOrders = new QTableWidget(tabOrders);
        if (tblOrders->columnCount() < 7)
            tblOrders->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(6, __qtablewidgetitem14);
        tblOrders->setObjectName("tblOrders");
        tblOrders->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tblOrders->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tblOrders->setColumnCount(7);
        tblOrders->horizontalHeader()->setVisible(true);
        tblOrders->verticalHeader()->setVisible(true);

        vlo->addWidget(tblOrders);

        orderChartContainer = new QWidget(tabOrders);
        orderChartContainer->setObjectName("orderChartContainer");
        orderChartContainer->setMinimumSize(QSize(0, 200));

        vlo->addWidget(orderChartContainer);

        tabWidget->addTab(tabOrders, QString());
        tabUsers = new QWidget();
        tabUsers->setObjectName("tabUsers");
        verticalLayout_4 = new QVBoxLayout(tabUsers);
        verticalLayout_4->setObjectName("verticalLayout_4");
        stackedUser = new QStackedWidget(tabUsers);
        stackedUser->setObjectName("stackedUser");
        pageUserView = new QWidget();
        pageUserView->setObjectName("pageUserView");
        verticalLayout_5 = new QVBoxLayout(pageUserView);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        leSearchUser = new QLineEdit(pageUserView);
        leSearchUser->setObjectName("leSearchUser");

        horizontalLayout_5->addWidget(leSearchUser);

        cbUserRoleFilter = new QComboBox(pageUserView);
        cbUserRoleFilter->addItem(QString());
        cbUserRoleFilter->addItem(QString());
        cbUserRoleFilter->addItem(QString());
        cbUserRoleFilter->addItem(QString());
        cbUserRoleFilter->setObjectName("cbUserRoleFilter");

        horizontalLayout_5->addWidget(cbUserRoleFilter);

        cbUserStatusFilter = new QComboBox(pageUserView);
        cbUserStatusFilter->addItem(QString());
        cbUserStatusFilter->addItem(QString());
        cbUserStatusFilter->addItem(QString());
        cbUserStatusFilter->setObjectName("cbUserStatusFilter");

        horizontalLayout_5->addWidget(cbUserStatusFilter);

        cbUserSort = new QComboBox(pageUserView);
        cbUserSort->addItem(QString());
        cbUserSort->addItem(QString());
        cbUserSort->addItem(QString());
        cbUserSort->addItem(QString());
        cbUserSort->addItem(QString());
        cbUserSort->setObjectName("cbUserSort");

        horizontalLayout_5->addWidget(cbUserSort);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        btnAddUser = new QPushButton(pageUserView);
        btnAddUser->setObjectName("btnAddUser");

        horizontalLayout_6->addWidget(btnAddUser);

        btnRefUser = new QPushButton(pageUserView);
        btnRefUser->setObjectName("btnRefUser");

        horizontalLayout_6->addWidget(btnRefUser);

        btnChangePassword = new QPushButton(pageUserView);
        btnChangePassword->setObjectName("btnChangePassword");

        horizontalLayout_6->addWidget(btnChangePassword);


        verticalLayout_5->addLayout(horizontalLayout_6);

        tblUsers = new QTableWidget(pageUserView);
        if (tblUsers->columnCount() < 5)
            tblUsers->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tblUsers->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tblUsers->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tblUsers->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tblUsers->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tblUsers->setHorizontalHeaderItem(4, __qtablewidgetitem19);
        tblUsers->setObjectName("tblUsers");
        tblUsers->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tblUsers->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tblUsers->setColumnCount(5);
        tblUsers->horizontalHeader()->setVisible(true);
        tblUsers->verticalHeader()->setVisible(true);

        verticalLayout_5->addWidget(tblUsers);

        userChartContainer = new QWidget(pageUserView);
        userChartContainer->setObjectName("userChartContainer");
        userChartContainer->setMinimumSize(QSize(0, 200));

        verticalLayout_5->addWidget(userChartContainer);

        stackedUser->addWidget(pageUserView);
        pageUserEdit = new QWidget();
        pageUserEdit->setObjectName("pageUserEdit");
        verticalLayout_6 = new QVBoxLayout(pageUserEdit);
        verticalLayout_6->setObjectName("verticalLayout_6");
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName("formLayout_3");
        lblUserUsername = new QLabel(pageUserEdit);
        lblUserUsername->setObjectName("lblUserUsername");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, lblUserUsername);

        leUserUsername = new QLineEdit(pageUserEdit);
        leUserUsername->setObjectName("leUserUsername");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, leUserUsername);

        lblUserPassword = new QLabel(pageUserEdit);
        lblUserPassword->setObjectName("lblUserPassword");

        formLayout_3->setWidget(1, QFormLayout::ItemRole::LabelRole, lblUserPassword);

        leUserPassword = new QLineEdit(pageUserEdit);
        leUserPassword->setObjectName("leUserPassword");
        leUserPassword->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout_3->setWidget(1, QFormLayout::ItemRole::FieldRole, leUserPassword);

        lblUserRole = new QLabel(pageUserEdit);
        lblUserRole->setObjectName("lblUserRole");

        formLayout_3->setWidget(2, QFormLayout::ItemRole::LabelRole, lblUserRole);

        cbUserRole = new QComboBox(pageUserEdit);
        cbUserRole->addItem(QString());
        cbUserRole->addItem(QString());
        cbUserRole->addItem(QString());
        cbUserRole->setObjectName("cbUserRole");

        formLayout_3->setWidget(2, QFormLayout::ItemRole::FieldRole, cbUserRole);

        lblUserStatus = new QLabel(pageUserEdit);
        lblUserStatus->setObjectName("lblUserStatus");

        formLayout_3->setWidget(3, QFormLayout::ItemRole::LabelRole, lblUserStatus);

        cbUserStatus = new QComboBox(pageUserEdit);
        cbUserStatus->addItem(QString());
        cbUserStatus->addItem(QString());
        cbUserStatus->setObjectName("cbUserStatus");

        formLayout_3->setWidget(3, QFormLayout::ItemRole::FieldRole, cbUserStatus);


        verticalLayout_6->addLayout(formLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        btnUpdUser = new QPushButton(pageUserEdit);
        btnUpdUser->setObjectName("btnUpdUser");

        horizontalLayout_7->addWidget(btnUpdUser);

        btnDelUser = new QPushButton(pageUserEdit);
        btnDelUser->setObjectName("btnDelUser");

        horizontalLayout_7->addWidget(btnDelUser);

        btnCancelUser = new QPushButton(pageUserEdit);
        btnCancelUser->setObjectName("btnCancelUser");

        horizontalLayout_7->addWidget(btnCancelUser);


        verticalLayout_6->addLayout(horizontalLayout_7);

        stackedUser->addWidget(pageUserEdit);

        verticalLayout_4->addWidget(stackedUser);

        tabWidget->addTab(tabUsers, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        stackedUser->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Syst\303\250me de Gestion Logistique", nullptr));
        lblNom->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        lblPrenom->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        lblTel->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        lblEmail->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        lblAdr->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        lblStatut->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        cbStatut->setItemText(0, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        cbStatut->setItemText(1, QCoreApplication::translate("MainWindow", "INACTIVE", nullptr));

        leSearchClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (nom, pr\303\251nom, email)", nullptr));
        leEmailFilter->setPlaceholderText(QCoreApplication::translate("MainWindow", "Filtrer par email", nullptr));
        cbStatutFilter->setItemText(0, QCoreApplication::translate("MainWindow", "Tous", nullptr));
        cbStatutFilter->setItemText(1, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        cbStatutFilter->setItemText(2, QCoreApplication::translate("MainWindow", "INACTIVE", nullptr));

        cbClientSort->setItemText(0, QCoreApplication::translate("MainWindow", "Trier par", nullptr));
        cbClientSort->setItemText(1, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        cbClientSort->setItemText(2, QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        cbClientSort->setItemText(3, QCoreApplication::translate("MainWindow", "Cr\303\251\303\251", nullptr));

        btnAddClient->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdClient->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelClient->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnRefClient->setText(QCoreApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
        btnClientStats->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        btnExportExcel->setText(QCoreApplication::translate("MainWindow", "Exporter Excel", nullptr));
        btnUpdateCategory->setText(QCoreApplication::translate("MainWindow", "Auto Cat\303\251goriser", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblClients->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblClients->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblClients->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblClients->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblClients->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tblClients->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tblClients->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tblClients->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Cr\303\251\303\251 le", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClients), QCoreApplication::translate("MainWindow", "Clients", nullptr));
        lblClient->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        lblEtat->setText(QCoreApplication::translate("MainWindow", "\303\211tat", nullptr));
        cbEtat->setItemText(0, QCoreApplication::translate("MainWindow", "EN_ATTENTE", nullptr));
        cbEtat->setItemText(1, QCoreApplication::translate("MainWindow", "EN_COURS", nullptr));
        cbEtat->setItemText(2, QCoreApplication::translate("MainWindow", "LIVREE", nullptr));
        cbEtat->setItemText(3, QCoreApplication::translate("MainWindow", "ANNULEE", nullptr));

        lblMontant->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        lblAdrLiv->setText(QCoreApplication::translate("MainWindow", "Adresse Livraison", nullptr));
        lblPriority->setText(QCoreApplication::translate("MainWindow", "Priorit\303\251", nullptr));
        cbPriority->setItemText(0, QCoreApplication::translate("MainWindow", "LOW", nullptr));
        cbPriority->setItemText(1, QCoreApplication::translate("MainWindow", "NORMAL", nullptr));
        cbPriority->setItemText(2, QCoreApplication::translate("MainWindow", "HIGH", nullptr));
        cbPriority->setItemText(3, QCoreApplication::translate("MainWindow", "URGENT", nullptr));

        leSearchOrder->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (\303\251tat, adresse)", nullptr));
        cbClientFilter->setItemText(0, QCoreApplication::translate("MainWindow", "Tous les clients", nullptr));

        cbEtatFilter->setItemText(0, QCoreApplication::translate("MainWindow", "Tous", nullptr));
        cbEtatFilter->setItemText(1, QCoreApplication::translate("MainWindow", "EN_ATTENTE", nullptr));
        cbEtatFilter->setItemText(2, QCoreApplication::translate("MainWindow", "EN_COURS", nullptr));
        cbEtatFilter->setItemText(3, QCoreApplication::translate("MainWindow", "LIVREE", nullptr));
        cbEtatFilter->setItemText(4, QCoreApplication::translate("MainWindow", "ANNULEE", nullptr));

        lblMinAmount->setText(QCoreApplication::translate("MainWindow", "Min:", nullptr));
        lblMaxAmount->setText(QCoreApplication::translate("MainWindow", "Max:", nullptr));
        cbOrderSort->setItemText(0, QCoreApplication::translate("MainWindow", "Trier par", nullptr));
        cbOrderSort->setItemText(1, QCoreApplication::translate("MainWindow", "Date", nullptr));
        cbOrderSort->setItemText(2, QCoreApplication::translate("MainWindow", "Montant", nullptr));
        cbOrderSort->setItemText(3, QCoreApplication::translate("MainWindow", "\303\211tat", nullptr));

        btnAddOrd->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdOrd->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelOrd->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnRefOrd->setText(QCoreApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
        btnPdfOrd->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnOrderStats->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        btnUpdatePriority->setText(QCoreApplication::translate("MainWindow", "Modifier Priorit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tblOrders->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tblOrders->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tblOrders->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tblOrders->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\303\211tat", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tblOrders->horizontalHeaderItem(4);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tblOrders->horizontalHeaderItem(5);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Adresse Livraison", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tblOrders->horizontalHeaderItem(6);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Priorit\303\251", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOrders), QCoreApplication::translate("MainWindow", "Commandes", nullptr));
        leSearchUser->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par nom d'utilisateur", nullptr));
        cbUserRoleFilter->setItemText(0, QCoreApplication::translate("MainWindow", "Tous les r\303\264les", nullptr));
        cbUserRoleFilter->setItemText(1, QCoreApplication::translate("MainWindow", "ADMIN", nullptr));
        cbUserRoleFilter->setItemText(2, QCoreApplication::translate("MainWindow", "MANAGER", nullptr));
        cbUserRoleFilter->setItemText(3, QCoreApplication::translate("MainWindow", "DELIVERY", nullptr));

        cbUserStatusFilter->setItemText(0, QCoreApplication::translate("MainWindow", "Tous les statuts", nullptr));
        cbUserStatusFilter->setItemText(1, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        cbUserStatusFilter->setItemText(2, QCoreApplication::translate("MainWindow", "SUSPENDED", nullptr));

        cbUserSort->setItemText(0, QCoreApplication::translate("MainWindow", "Trier par", nullptr));
        cbUserSort->setItemText(1, QCoreApplication::translate("MainWindow", "Nom d'utilisateur", nullptr));
        cbUserSort->setItemText(2, QCoreApplication::translate("MainWindow", "R\303\264le", nullptr));
        cbUserSort->setItemText(3, QCoreApplication::translate("MainWindow", "Statut", nullptr));
        cbUserSort->setItemText(4, QCoreApplication::translate("MainWindow", "Date cr\303\251ation", nullptr));

        btnAddUser->setText(QCoreApplication::translate("MainWindow", "Nouvel Utilisateur", nullptr));
        btnRefUser->setText(QCoreApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
        btnChangePassword->setText(QCoreApplication::translate("MainWindow", "Changer Mot de Passe", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tblUsers->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tblUsers->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Nom d'utilisateur", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tblUsers->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "R\303\264le", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tblUsers->horizontalHeaderItem(3);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tblUsers->horizontalHeaderItem(4);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Date cr\303\251ation", nullptr));
        lblUserUsername->setText(QCoreApplication::translate("MainWindow", "Nom d'utilisateur:", nullptr));
        lblUserPassword->setText(QCoreApplication::translate("MainWindow", "Mot de passe:", nullptr));
        lblUserRole->setText(QCoreApplication::translate("MainWindow", "R\303\264le:", nullptr));
        cbUserRole->setItemText(0, QCoreApplication::translate("MainWindow", "ADMIN", nullptr));
        cbUserRole->setItemText(1, QCoreApplication::translate("MainWindow", "MANAGER", nullptr));
        cbUserRole->setItemText(2, QCoreApplication::translate("MainWindow", "DELIVERY", nullptr));

        lblUserStatus->setText(QCoreApplication::translate("MainWindow", "Statut:", nullptr));
        cbUserStatus->setItemText(0, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        cbUserStatus->setItemText(1, QCoreApplication::translate("MainWindow", "SUSPENDED", nullptr));

        btnUpdUser->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelUser->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnCancelUser->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabUsers), QCoreApplication::translate("MainWindow", "Utilisateurs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
