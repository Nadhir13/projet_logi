#include "clientcontroller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QInputDialog>
#include <QColor>
#include <QtCharts>

ClientController::ClientController(MainWindow* mainWindow, QObject* parent)
    : QObject(parent), m_mainWindow(mainWindow)
{}

void ClientController::setupUi() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    
    // Connect client-related buttons
    connect(ui->btnAddClient, &QPushButton::clicked, this, &ClientController::addClient);
    connect(ui->btnUpdClient, &QPushButton::clicked, this, &ClientController::updateClient);
    connect(ui->btnDelClient, &QPushButton::clicked, this, &ClientController::deleteClient);
    connect(ui->btnRefClient, &QPushButton::clicked, this, &ClientController::refreshClients);
    
    // Connect filter signals
    connect(ui->leSearchClient, &QLineEdit::textChanged, this, &ClientController::applyFilters);
    connect(ui->leEmailFilter, &QLineEdit::textChanged, this, &ClientController::applyFilters);
    connect(ui->cbStatutFilter, &QComboBox::currentTextChanged, this, &ClientController::applyFilters);
    connect(ui->cbClientSort, &QComboBox::currentTextChanged, this, &ClientController::applyFilters);
    
    // Set tooltips
    ui->leSearchClient->setToolTip("Recherche par nom et prénom");
    ui->leEmailFilter->setToolTip("Filtrer par email spécifique");
}

void ClientController::addClient() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (!validateForm()) return;

    Client c;
    c.nom = ui->leNom->text();
    c.prenom = ui->lePrenom->text();
    c.tel = ui->leTel->text();
    c.email = ui->leEmail->text();
    c.adr = ui->leAdr->text();
    c.statut = ui->cbStatut->currentText();
    c.category = "REGULAR";
    if (!m_dao.add(c)) {
        QMessageBox::warning(m_mainWindow, "Client", "Échec de l'ajout: " + Db::instance().lastError());
    }
    refreshClients();
}

void ClientController::updateClient() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Client", "Veuillez sélectionner un client à modifier");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

    auto clientOpt = m_dao.byId(id);
    if (!clientOpt.has_value()) {
        QMessageBox::warning(m_mainWindow, "Client", "Client non trouvé");
        return;
    }

    Client c = clientOpt.value();
    c.nom = ui->leNom->text();
    c.prenom = ui->lePrenom->text();
    c.tel = ui->leTel->text();
    c.email = ui->leEmail->text();
    c.adr = ui->leAdr->text();
    c.statut = ui->cbStatut->currentText();

    if (!m_dao.upd(c)) {
        QMessageBox::warning(m_mainWindow, "Client", "Échec de la modification: " + Db::instance().lastError());
    } else {
        QMessageBox::information(m_mainWindow, "Client", "Client modifié avec succès");
        refreshClients();
    }
}

void ClientController::deleteClient() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

    if (!m_dao.del(id)) {
        QMessageBox::warning(m_mainWindow, "Client", "Échec de la suppression: " + Db::instance().lastError());
    }
    refreshClients();
}

void ClientController::refreshClients() {
    loadClientsTable();
    loadClientsCombo();
    loadClientFilterCombo();
}

void ClientController::loadClientsTable() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto v = m_dao.all();
    ui->tblClients->clearContents();
    ui->tblClients->setRowCount(v.size());
    ui->tblClients->setColumnCount(9);
    QStringList headers = {"ID","Nom","Prénom","Tel","Email","Adresse","Statut","Créé","Catégorie"};
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
        ui->tblClients->setItem(i,8,new QTableWidgetItem(c.category));
        QTableWidgetItem *categoryItem = new QTableWidgetItem(c.category);
        if (c.category == "PLATINUM") {
            categoryItem->setBackground(QColor("#E5E4E2")); // Platinum color
        } else if (c.category == "GOLD") {
            categoryItem->setBackground(QColor("#FFD700")); // Gold color
        } else if (c.category == "SILVER") {
            categoryItem->setBackground(QColor("#C0C0C0")); // Silver color
        }
        ui->tblClients->setItem(i,8,categoryItem);
    }
    applyFilters();
    updateChart();
}

void ClientController::loadClientsCombo() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto v = m_dao.all();
    ui->cbClient->clear();
    for (const auto& c: v) {
        ui->cbClient->addItem(QString("%1 %2").arg(c.nom, c.prenom), c.id);
    }
}

void ClientController::loadClientFilterCombo() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto v = m_dao.all();
    ui->cbClientFilter->clear();
    ui->cbClientFilter->addItem("Tous les clients", -1);
    for (const auto& c: v) {
        ui->cbClientFilter->addItem(QString("%1 %2").arg(c.nom, c.prenom), c.id);
    }
}

void ClientController::applyFilters() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    QString text = ui->leSearchClient->text().trimmed();
    QString emailFilter = ui->leEmailFilter->text().trimmed();
    QString statut = ui->cbStatutFilter->currentText();
    QString sortKey = ui->cbClientSort->currentText();

    for (int r=0; r<ui->tblClients->rowCount(); ++r) ui->tblClients->setRowHidden(r, false);

    for (int r=0; r<ui->tblClients->rowCount(); ++r) {
        bool match = true;

        // Name search (nom, prénom)
        if (!text.isEmpty()) {
            QString rowText = ui->tblClients->item(r,1)->text() + " " + ui->tblClients->item(r,2)->text();
            match &= rowText.contains(text, Qt::CaseInsensitive);
        }

        // Email filter
        if (!emailFilter.isEmpty()) {
            QString email = ui->tblClients->item(r,4)->text();
            match &= email.contains(emailFilter, Qt::CaseInsensitive);
        }

        // Status filter
        if (statut != "Tous") {
            match &= ui->tblClients->item(r,6)->text() == statut;
        }

        if (!match) ui->tblClients->setRowHidden(r, true);
    }

    if (sortKey == "Nom") ui->tblClients->sortItems(1);
    else if (sortKey == "Prénom") ui->tblClients->sortItems(2);
    else if (sortKey == "Créé") ui->tblClients->sortItems(7);
}

void ClientController::updateChart() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    // Access the chart view through the main window's member variable
    QChartView* clientChartView = m_mainWindow->clientChartView;
    if (!clientChartView) return;

    auto clients = m_dao.all();

    QMap<QString, int> counts;
    counts["ACTIVE"] = 0;
    counts["INACTIVE"] = 0;

    for (const auto &client : clients) {
        counts[client.statut]++;
    }

    QPieSeries *series = new QPieSeries();
    if (counts["ACTIVE"] > 0) series->append("Actif", counts["ACTIVE"]);
    if (counts["INACTIVE"] > 0) series->append("Inactif", counts["INACTIVE"]);

    if (series->slices().count() > 0) {
        series->slices().at(0)->setColor(QColor("#4caf50"));
        if (series->slices().count() > 1) {
            series->slices().at(1)->setColor(QColor("#f44336"));
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par statut");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    clientChartView->setChart(chart);
}

void ClientController::showStats() {
    auto topClients = m_dao.getTopClients(5);

    QString message = "Statistiques clients:\n\n";
    message += "Top 5 clients par nombre de commandes:\n";

    for (const auto &client : topClients) {
        message += QString("%1 %2: %3 commandes\n")
        .arg(client.nom)
            .arg(client.prenom)
            .arg(client.totalOrders);
    }

    QMessageBox::information(m_mainWindow, "Statistiques Clients", message);
}

void ClientController::exportToExcel() {
    QString fileName = QFileDialog::getSaveFileName(m_mainWindow, "Exporter clients", "clients.csv", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(m_mainWindow, "Export", "Impossible de créer le fichier");
        return;
    }

    QTextStream stream(&file);
    stream << "ID,Nom,Prénom,Téléphone,Email,Adresse,Statut,Date création,Catégorie\n";

    auto clients = m_dao.all();

    for (const auto &client : clients) {
        stream << client.id << ","
               << client.nom << ","
               << client.prenom << ","
               << client.tel << ","
               << client.email << ","
               << client.adr << ","
               << client.statut << ","
               << client.created.toString("yyyy-MM-dd") << ","
               << client.category << "\n";
    }

    file.close();
    QMessageBox::information(m_mainWindow, "Export", "Clients exportés avec succès");
}

void ClientController::updateClientCategory() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblClients->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Catégorie", "Veuillez sélectionner un client");
        return;
    }

    int row = items.first()->row();
    int id = ui->tblClients->item(row, 0)->text().toInt();

    QStringList categories = {"REGULAR", "SILVER", "GOLD", "PLATINUM"};
    QString category = QInputDialog::getItem(m_mainWindow, "Catégorie client",
                                             "Sélectionnez la catégorie:", categories, 0, false);

    if (category.isEmpty()) return;

    if (m_dao.updateClientCategory(id, category)) {
        QMessageBox::information(m_mainWindow, "Catégorie", "Catégorie mise à jour avec succès");
        refreshClients();
    } else {
        QMessageBox::warning(m_mainWindow, "Catégorie", "Échec de la mise à jour");
    }
}

void ClientController::autoCategorizeClients() {
    if (m_dao.autoCategorizeClients()) {
        QMessageBox::information(m_mainWindow, "Catégorisation", "Clients catégorisés automatiquement avec succès");
        refreshClients();
    } else {
        QMessageBox::warning(m_mainWindow, "Catégorisation", "Échec de la catégorisation automatique");
    }
}

bool ClientController::validateForm() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (ui->leNom->text().isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le nom est obligatoire");
        ui->leNom->setFocus();
        return false;
    }
    if (ui->lePrenom->text().isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le prénom est obligatoire");
        ui->lePrenom->setFocus();
        return false;
    }
    if (!ui->leEmail->text().isEmpty() && !ui->leEmail->text().contains('@')) {
        QMessageBox::warning(m_mainWindow, "Validation", "Email invalide");
        ui->leEmail->setFocus();
        return false;
    }
    return true;
}
