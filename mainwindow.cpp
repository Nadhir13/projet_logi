#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include "db.h"

#include "clientdao.h"
#include "orderdao.h"

#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QVBoxLayout>
#include <QHeaderView>


bool MainWindow::validateClientForm() {
    if (ui->leNom->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom est obligatoire");
        ui->leNom->setFocus();
        return false;
    }
    if (ui->lePrenom->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le prénom est obligatoire");
        ui->lePrenom->setFocus();
        return false;
    }
    if (!ui->leEmail->text().isEmpty() && !ui->leEmail->text().contains('@')) {
        QMessageBox::warning(this, "Validation", "Email invalide");
        ui->leEmail->setFocus();
        return false;
    }
    return true;
}

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
    connect(ui->btnPdfOrd, &QPushButton::clicked, this, &MainWindow::exportOrderPdf);

    // Connect selection changes
    connect(ui->tblClients, &QTableWidget::itemSelectionChanged, this, [this]() {
        auto items = ui->tblClients->selectedItems();
        if (!items.isEmpty()) {
            int row = items.first()->row();
            // Load client data into form
            ui->leNom->setText(ui->tblClients->item(row, 1)->text());
            ui->lePrenom->setText(ui->tblClients->item(row, 2)->text());
            ui->leTel->setText(ui->tblClients->item(row, 3)->text());
            ui->leEmail->setText(ui->tblClients->item(row, 4)->text());
            ui->leAdr->setText(ui->tblClients->item(row, 5)->text());

            QString statut = ui->tblClients->item(row, 6)->text();
            int index = ui->cbStatut->findText(statut);
            if (index >= 0) ui->cbStatut->setCurrentIndex(index);
        }
    });

    connect(ui->tblOrders, &QTableWidget::itemSelectionChanged, this, [this]() {
        auto items = ui->tblOrders->selectedItems();
        if (!items.isEmpty()) {
            int row = items.first()->row();
            // Load order data into form
            int clientId = ui->tblOrders->item(row, 1)->text().toInt();

            // Find client in combo box
            for (int i = 0; i < ui->cbClient->count(); ++i) {
                if (ui->cbClient->itemData(i).toInt() == clientId) {
                    ui->cbClient->setCurrentIndex(i);
                    break;
                }
            }

            QString etat = ui->tblOrders->item(row, 3)->text();
            int index = ui->cbEtat->findText(etat);
            if (index >= 0) ui->cbEtat->setCurrentIndex(index);

            ui->dsMontant->setValue(ui->tblOrders->item(row, 4)->text().toDouble());
            ui->leAdrLiv->setText(ui->tblOrders->item(row, 5)->text());
        }
    });

    // initial load
    loadClientsTable();
    loadClientsCombo();
    loadOrdersTable();

    // setup charts containers
    if (!clientChartView) {
        auto chartView = new QGraphicsView(new QGraphicsScene());
        auto container = this->findChild<QWidget*>("clientChartContainer");
        if (container) {
            auto lay = new QVBoxLayout(container);
            lay->setContentsMargins(0,0,0,0);
            lay->addWidget(chartView);
        }
        clientChartView = chartView;
    }
    if (!orderChartView) {
        auto chartView = new QGraphicsView(new QGraphicsScene());
        auto container = this->findChild<QWidget*>("orderChartContainer");
        if (container) {
            auto lay = new QVBoxLayout(container);
            lay->setContentsMargins(0,0,0,0);
            lay->addWidget(chartView);
        }
        orderChartView = chartView;
    }

    // wire filters
    connect(ui->leSearchClient, &QLineEdit::textChanged, this, &MainWindow::applyClientFilters);
    connect(ui->cbStatutFilter, &QComboBox::currentTextChanged, this, &MainWindow::applyClientFilters);
    connect(ui->cbClientSort, &QComboBox::currentTextChanged, this, &MainWindow::applyClientFilters);
    connect(ui->leSearchOrder, &QLineEdit::textChanged, this, &MainWindow::applyOrderFilters);
    connect(ui->cbEtatFilter, &QComboBox::currentTextChanged, this, &MainWindow::applyOrderFilters);
    connect(ui->cbOrderSort, &QComboBox::currentTextChanged, this, &MainWindow::applyOrderFilters);

    updateClientChart();
    updateOrderChart();
}

MainWindow::~MainWindow() { delete ui; }

// ===== Clients
void MainWindow::addClient() {
    if (!validateClientForm()) return;

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
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Client", "Veuillez sélectionner un client à modifier");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

    ClientDao dao;
    auto clientOpt = dao.byId(id);
    if (!clientOpt.has_value()) {
        QMessageBox::warning(this, "Client", "Client non trouvé");
        return;
    }

    Client c = clientOpt.value();
    c.nom = ui->leNom->text();
    c.prenom = ui->lePrenom->text();
    c.tel = ui->leTel->text();
    c.email = ui->leEmail->text();
    c.adr = ui->leAdr->text();
    c.statut = ui->cbStatut->currentText();

    if (!dao.upd(c)) {
        QMessageBox::warning(this, "Client", "Échec de la modification: " + Db::instance().lastError());
    } else {
        QMessageBox::information(this, "Client", "Client modifié avec succès");
        refClient();
    }
}

void MainWindow::delClient() {
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

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
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Commande", "Veuillez sélectionner une commande à modifier");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();

    OrderDao dao;
    auto orderOpt = dao.byId(id);
    if (!orderOpt.has_value()) {
        QMessageBox::warning(this, "Commande", "Commande non trouvée");
        return;
    }

    Order o = orderOpt.value();
    o.clientId = ui->cbClient->currentData().toInt();
    o.etat = ui->cbEtat->currentText();
    o.montant = ui->dsMontant->value();
    o.adrLiv = ui->leAdrLiv->text();

    if (!dao.upd(o)) {
        QMessageBox::warning(this, "Commande", "Échec de la modification: " + Db::instance().lastError());
    } else {
        QMessageBox::information(this, "Commande", "Commande modifiée avec succès");
        refOrder();
    }
}

void MainWindow::delOrder() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();

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
    ui->tblClients->horizontalHeader()->setStretchLastSection(true);
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
    applyClientFilters();
    updateClientChart();
}

void MainWindow::loadOrdersTable() {
    OrderDao dao;
    auto v = dao.all();
    ui->tblOrders->clearContents();
    ui->tblOrders->setRowCount(v.size());
    ui->tblOrders->setColumnCount(6);
    QStringList headers = {"ID","Client","Date","Etat","Montant","Adr"};
    ui->tblOrders->setHorizontalHeaderLabels(headers);
    ui->tblOrders->horizontalHeader()->setStretchLastSection(true);
    for (int i=0;i<v.size();++i) {
        const auto &o = v[i];
        ui->tblOrders->setItem(i,0,new QTableWidgetItem(QString::number(o.id)));
        ui->tblOrders->setItem(i,1,new QTableWidgetItem(QString::number(o.clientId)));
        ui->tblOrders->setItem(i,2,new QTableWidgetItem(o.date.toString("yyyy-MM-dd")));
        ui->tblOrders->setItem(i,3,new QTableWidgetItem(o.etat));
        ui->tblOrders->setItem(i,4,new QTableWidgetItem(QString::number(o.montant, 'f', 3)));
        ui->tblOrders->setItem(i,5,new QTableWidgetItem(o.adrLiv));
    }
    applyOrderFilters();
    updateOrderChart();
}
void MainWindow::exportOrderPdf() {
    auto items = ui->tblOrders->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "PDF", "Veuillez sélectionner une commande.");
        return;
    }
    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();

    OrderDao dao;
    auto orderOpt = dao.byId(id);
    if (!orderOpt.has_value()) {
        QMessageBox::warning(this, "PDF", "Commande introuvable.");
        return;
    }
    Order o = orderOpt.value();

    QString defaultName = QString("commande_%1.pdf").arg(o.id);
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", defaultName, "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "PDF", "Impossible de créer le PDF.");
        return;
    }

    int x = 500; // left margin
    int y = 500; // top margin
    int line = 400; // line height

    QFont titleFont = painter.font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(x, y, QString("Commande #%1").arg(o.id));
    y += line * 2;

    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);
    painter.setFont(bodyFont);

    painter.drawText(x, y, QString("Date: %1").arg(o.date.toString("yyyy-MM-dd"))); y += line;
    painter.drawText(x, y, QString("Client ID: %1").arg(o.clientId)); y += line;
    painter.drawText(x, y, QString("Etat: %1").arg(o.etat)); y += line;
    painter.drawText(x, y, QString("Montant: %1").arg(QString::number(o.montant, 'f', 3))); y += line;
    painter.drawText(x, y, QString("Adresse de livraison: %1").arg(o.adrLiv)); y += line;

    painter.end();

    QMessageBox::information(this, "PDF", "PDF généré avec succès.");
}

void MainWindow::loadClientsCombo() {
    ClientDao dao;
    auto v = dao.all();
    ui->cbClient->clear();
    for (const auto& c: v) {
        ui->cbClient->addItem(QString("%1 %2").arg(c.nom, c.prenom), c.id);
    }
}

void MainWindow::applyClientFilters() {
    QString text = ui->leSearchClient ? ui->leSearchClient->text().trimmed() : QString();
    QString statut = ui->cbStatutFilter ? ui->cbStatutFilter->currentText() : QString("Tous");
    QString sortKey = ui->cbClientSort ? ui->cbClientSort->currentText() : QString();

    // show all rows first
    for (int r=0; r<ui->tblClients->rowCount(); ++r) ui->tblClients->setRowHidden(r, false);

    for (int r=0; r<ui->tblClients->rowCount(); ++r) {
        bool match = true;
        if (!text.isEmpty()) {
            QString rowText = ui->tblClients->item(r,1)->text() + " " + ui->tblClients->item(r,2)->text() + " " + ui->tblClients->item(r,4)->text();
            match &= rowText.contains(text, Qt::CaseInsensitive);
        }
        if (statut != "Tous") {
            match &= ui->tblClients->item(r,6)->text() == statut;
        }
        if (!match) ui->tblClients->setRowHidden(r, true);
    }

    // sorting: simple in-place sort by column
    if (sortKey == "Nom") ui->tblClients->sortItems(1);
    else if (sortKey == "Prénom") ui->tblClients->sortItems(2);
    else if (sortKey == "Créé") ui->tblClients->sortItems(7);
}

void MainWindow::applyOrderFilters() {
    QString text = ui->leSearchOrder ? ui->leSearchOrder->text().trimmed() : QString();
    QString etat = ui->cbEtatFilter ? ui->cbEtatFilter->currentText() : QString("Tous");
    QString sortKey = ui->cbOrderSort ? ui->cbOrderSort->currentText() : QString();

    for (int r=0; r<ui->tblOrders->rowCount(); ++r) ui->tblOrders->setRowHidden(r, false);

    for (int r=0; r<ui->tblOrders->rowCount(); ++r) {
        bool match = true;
        if (!text.isEmpty()) {
            QString rowText = ui->tblOrders->item(r,3)->text() + " " + ui->tblOrders->item(r,5)->text();
            match &= rowText.contains(text, Qt::CaseInsensitive);
        }
        if (etat != "Tous") {
            match &= ui->tblOrders->item(r,3)->text() == etat;
        }
        if (!match) ui->tblOrders->setRowHidden(r, true);
    }

    if (sortKey == "Date") ui->tblOrders->sortItems(2);
    else if (sortKey == "Montant") ui->tblOrders->sortItems(4);
    else if (sortKey == "État") ui->tblOrders->sortItems(3);
}

void MainWindow::updateClientChart() {
    if (!clientChartView) return;
    auto view = static_cast<QGraphicsView*>(clientChartView);
    QGraphicsScene* scene = view->scene();
    scene->clear();

    QMap<QString,int> counts; counts["ACTIVE"]=0; counts["INACTIVE"]=0;
    for (int r=0; r<ui->tblClients->rowCount(); ++r) {
        if (ui->tblClients->isRowHidden(r)) continue;
        counts[ ui->tblClients->item(r,6)->text() ]++;
    }
    int total = 0; for (auto v : counts) total += v;
    if (total == 0) { scene->addText("Aucune donnée"); return; }

    QRectF pieRect(10, 10, 220, 220);
    int startAngle16 = 0;
    QList<QColor> colors { QColor("#4caf50"), QColor("#f44336"), QColor("#2196f3"), QColor("#ff9800") };
    int colorIdx = 0;
    int legendY = 10;
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        if (it.value() == 0) continue;
        int span16 = int(5760.0 * (double(it.value()) / double(total)) + 0.5);
        QColor color = colors[colorIdx++ % colors.size()];
        auto slice = scene->addEllipse(pieRect, QPen(Qt::NoPen), QBrush(color));
        slice->setStartAngle(startAngle16);
        slice->setSpanAngle(span16);
        // legend
        auto rect = scene->addRect(250, legendY, 12, 12, QPen(Qt::black), QBrush(color));
        Q_UNUSED(rect);
        scene->addText(QString("%1 (%2)").arg(it.key()).arg(it.value()))->setPos(270, legendY-2);
        legendY += 18;
        startAngle16 += span16;
    }
    scene->addText("Clients par statut (filtrés)")->setPos(10, 240);
}

void MainWindow::updateOrderChart() {
    if (!orderChartView) return;
    auto view = static_cast<QGraphicsView*>(orderChartView);
    QGraphicsScene* scene = view->scene();
    scene->clear();

    QMap<QString,double> sums; sums["EN_ATTENTE"]=0; sums["EN_COURS"]=0; sums["LIVREE"]=0; sums["ANNULEE"]=0;
    for (int r=0; r<ui->tblOrders->rowCount(); ++r) {
        if (ui->tblOrders->isRowHidden(r)) continue;
        QString e = ui->tblOrders->item(r,3)->text();
        double m = ui->tblOrders->item(r,4)->text().toDouble();
        sums[e] += m;
    }
    QStringList cats; cats << "EN_ATTENTE" << "EN_COURS" << "LIVREE" << "ANNULEE";
    double maxVal = 0; for (const auto& c : cats) maxVal = std::max(maxVal, sums.value(c,0));
    if (maxVal <= 0) { scene->addText("Aucune donnée"); return; }

    int left = 40, top = 20, width = 360, height = 220;
    scene->addRect(left, top, width, height, QPen(Qt::black));
    int barWidth = 50; int gap = 30; int x = left + 20;
    QList<QColor> colors { QColor("#3f51b5"), QColor("#009688"), QColor("#ff5722"), QColor("#9c27b0") };
    int idx = 0;
    for (const auto& c : cats) {
        double val = sums.value(c,0);
        int barH = int((val / maxVal) * (height - 20));
        int y = top + height - barH;
        QColor color = colors[idx++ % colors.size()];
        scene->addRect(x, y, barWidth, barH, QPen(Qt::black), QBrush(color));
        auto txt = scene->addText(c);
        txt->setPos(x, top + height + 5);
        auto valTxt = scene->addText(QString::number(val, 'f', 2));
        valTxt->setPos(x, y - 18);
        x += barWidth + gap;
    }
    scene->addText("Somme des commandes par état (filtrées)")->setPos(left, top + height + 40);
}
