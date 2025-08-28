#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>

#include "clientdao.h"
#include "orderdao.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // wire buttons
    connect(ui->btnAddClient, &QPushButton::clicked, this, &MainWindow::addClient);
    connect(ui->btnUpdClient, &QPushButton::clicked, this, &MainWindow::updClient);
    connect(ui->btnDelClient, &QPushButton::clicked, this, &MainWindow::delClient);
    connect(ui->btnRefClient, &QPushButton::clicked, this, &MainWindow::refClient);

    connect(ui->btnAddOrd, &QPushButton::clicked, this, &MainWindow::addOrder);
    connect(ui->btnUpdOrd, &QPushButton::clicked, this, &MainWindow::updOrder);
    connect(ui->btnDelOrd, &QPushButton::clicked, this, &MainWindow::delOrder);
    connect(ui->btnRefOrd, &QPushButton::clicked, this, &MainWindow::refOrder);

    // initial load
    loadClientsTable();
    loadClientsCombo();
    loadOrdersTable();
}

MainWindow::~MainWindow() { delete ui; }

// ===== Clients
void MainWindow::addClient() {
    ClientDao dao;
    Client c;
    c.nom = ui->leNom->text();
    c.prenom = ui->lePrenom->text();
    c.tel = ui->leTel->text();
    c.email = ui->leEmail->text();
    c.adr = ui->leAdr->text();
    c.statut = ui->cbStatut->currentText();
    if (!dao.add(c)) QMessageBox::warning(this, "Client", "Insert failed");
    refClient();
}
void MainWindow::updClient() {
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblClients->item(row,0)->text().toInt();

    ClientDao dao;
    Client c;
    c.id = id;
    c.nom = ui->leNom->text();
    c.prenom = ui->lePrenom->text();
    c.tel = ui->leTel->text();
    c.email = ui->leEmail->text();
    c.adr = ui->leAdr->text();
    c.statut = ui->cbStatut->currentText();
    if (!dao.upd(c)) QMessageBox::warning(this, "Client", "Update failed");
    refClient();
}
void MainWindow::delClient() {
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblClients->item(row,0)->text().toInt();

    ClientDao dao;
    if (!dao.del(id)) QMessageBox::warning(this, "Client", "Delete failed");
    refClient();
}
void MainWindow::refClient() {
    loadClientsTable();
    loadClientsCombo();
}

// ===== Orders
void MainWindow::addOrder() {
    OrderDao dao;
    Order o;
    o.clientId = ui->cbClient->currentData().toInt();
    o.etat = ui->cbEtat->currentText();
    o.montant = ui->dsMontant->value();
    o.adrLiv = ui->leAdrLiv->text();
    if (!dao.add(o)) QMessageBox::warning(this, "Order", "Insert failed");
    refOrder();
}
void MainWindow::updOrder() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblOrders->item(row,0)->text().toInt();

    OrderDao dao;
    Order o;
    o.id = id;
    o.clientId = ui->cbClient->currentData().toInt();
    o.etat = ui->cbEtat->currentText();
    o.montant = ui->dsMontant->value();
    o.adrLiv = ui->leAdrLiv->text();
    if (!dao.upd(o)) QMessageBox::warning(this, "Order", "Update failed");
    refOrder();
}
void MainWindow::delOrder() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblOrders->item(row,0)->text().toInt();

    OrderDao dao;
    if (!dao.del(id)) QMessageBox::warning(this, "Order", "Delete failed");
    refOrder();
}
void MainWindow::refOrder() {
    loadOrdersTable();
}

// ===== loads
void MainWindow::loadClientsTable() {
    ClientDao dao;
    auto v = dao.all();
    ui->tblClients->clearContents();
    ui->tblClients->setRowCount(v.size());
    ui->tblClients->setColumnCount(8);
    QStringList headers = {"ID","Nom","Prenom","Tel","Email","Adr","Statut","Cree"};
    ui->tblClients->setHorizontalHeaderLabels(headers);
    for (int i=0;i<v.size();++i) {
        const auto &c = v[i];
        ui->tblClients->setItem(i,0,new QTableWidgetItem(QString::number(c.id)));
        ui->tblClients->setItem(i,1,new QTableWidgetItem(c.nom));
        ui->tblClients->setItem(i,2,new QTableWidgetItem(c.prenom));
        ui->tblClients->setItem(i,3,new QTableWidgetItem(c.tel));
        ui->tblClients->setItem(i,4,new QTableWidgetItem(c.email));
        ui->tblClients->setItem(i,5,new QTableWidgetItem(c.adr));
        ui->tblClients->setItem(i,6,new QTableWidgetItem(c.statut));
        ui->tblClients->setItem(i,7,new QTableWidgetItem(c.created.toString("yyyy-MM-dd")));
    }
}

void MainWindow::loadOrdersTable() {
    OrderDao dao;
    auto v = dao.all();
    ui->tblOrders->clearContents();
    ui->tblOrders->setRowCount(v.size());
    ui->tblOrders->setColumnCount(6);
    QStringList headers = {"ID","Client","Date","Etat","Montant","Adr"};
    ui->tblOrders->setHorizontalHeaderLabels(headers);
    for (int i=0;i<v.size();++i) {
        const auto &o = v[i];
        ui->tblOrders->setItem(i,0,new QTableWidgetItem(QString::number(o.id)));
        ui->tblOrders->setItem(i,1,new QTableWidgetItem(QString::number(o.clientId)));
        ui->tblOrders->setItem(i,2,new QTableWidgetItem(o.date.toString("yyyy-MM-dd")));
        ui->tblOrders->setItem(i,3,new QTableWidgetItem(o.etat));
        ui->tblOrders->setItem(i,4,new QTableWidgetItem(QString::number(o.montant, 'f', 3)));
        ui->tblOrders->setItem(i,5,new QTableWidgetItem(o.adrLiv));
    }
}

void MainWindow::loadClientsCombo() {
    ClientDao dao;
    auto v = dao.all();
    ui->cbClient->clear();
    for (const auto& c: v) {
        ui->cbClient->addItem(QString("%1 %2").arg(c.nom, c.prenom), c.id);
    }
}
