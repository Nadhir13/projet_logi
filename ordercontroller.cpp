#include "ordercontroller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QInputDialog>
#include <QtCharts>

OrderController::OrderController(MainWindow* mainWindow, QObject* parent)
    : QObject(parent), m_mainWindow(mainWindow)
{}

OrderController::~OrderController() {}

void OrderController::setupUi() {
    Ui::MainWindow* ui = m_mainWindow->getUi();

    // Connect order-related buttons
    connect(ui->btnAddOrd, &QPushButton::clicked, this, &OrderController::addOrder);
    connect(ui->btnUpdOrd, &QPushButton::clicked, this, &OrderController::updateOrder);
    connect(ui->btnDelOrd, &QPushButton::clicked, this, &OrderController::deleteOrder);
    connect(ui->btnRefOrd, &QPushButton::clicked, this, &OrderController::refreshOrders);
    connect(ui->btnPdfOrd, &QPushButton::clicked, this, &OrderController::exportToPdf);
    connect(ui->btnOrderStats, &QPushButton::clicked, this, &OrderController::showStats);
    connect(ui->btnUpdatePriority, &QPushButton::clicked, this, &OrderController::autoUpdatePriorities);

    // Connect filter signals
    connect(ui->leSearchOrder, &QLineEdit::textChanged, this, &OrderController::applyFilters);
    connect(ui->cbClientFilter, &QComboBox::currentTextChanged, this, &OrderController::applyFilters);
    connect(ui->cbEtatFilter, &QComboBox::currentTextChanged, this, &OrderController::applyFilters);
    connect(ui->dsMinAmount, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &OrderController::applyFilters);
    connect(ui->dsMaxAmount, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &OrderController::applyFilters);
    connect(ui->cbOrderSort, &QComboBox::currentTextChanged, this, &OrderController::applyFilters);

    // Connect table selection changed
    connect(ui->tblOrders, &QTableWidget::itemSelectionChanged, this, &OrderController::onOrderTableSelectionChanged);

    // Set tooltips
    ui->leSearchOrder->setToolTip("Recherche par état et adresse");
    ui->dsMinAmount->setToolTip("Montant minimum");
    ui->dsMaxAmount->setToolTip("Montant maximum");
}

void OrderController::onOrderTableSelectionChanged() {
    populateFormWithSelectedOrder();
}

void OrderController::populateFormWithSelectedOrder() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto items = ui->tblOrders->selectedItems();

    if (items.isEmpty()) {
        // Clear form if no selection
        ui->cbClient->setCurrentIndex(0);
        ui->cbEtat->setCurrentIndex(0);
        ui->dsMontant->setValue(0);
        ui->leAdrLiv->clear();
        ui->cbPriority->setCurrentIndex(1); // NORMAL
        m_selectedOrderId = -1;
        return;
    }

    int row = items.first()->row();
    int id = ui->tblOrders->item(row, 0)->text().toInt();
    m_selectedOrderId = id;

    auto orderOpt = m_dao.getById(id);
    if (!orderOpt.has_value()) {
        QMessageBox::warning(m_mainWindow, "Commande", "Commande non trouvée");
        return;
    }

    Order o = orderOpt.value();

    // Set client in combo box
    int clientIndex = ui->cbClient->findData(o.clientId);
    if (clientIndex >= 0) {
        ui->cbClient->setCurrentIndex(clientIndex);
    }

    // Set status in combo box
    int statusIndex = ui->cbEtat->findText(o.etat);
    if (statusIndex >= 0) {
        ui->cbEtat->setCurrentIndex(statusIndex);
    }

    ui->dsMontant->setValue(o.montant);
    ui->leAdrLiv->setText(o.adrLiv);

    // Set priority in combo box
    int priorityIndex = ui->cbPriority->findText(o.priority);
    if (priorityIndex >= 0) {
        ui->cbPriority->setCurrentIndex(priorityIndex);
    }
}

void OrderController::addOrder() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (!validateForm()) return;

    Order o;
    o.clientId = ui->cbClient->currentData().toInt();
    o.etat = ui->cbEtat->currentText();
    o.montant = ui->dsMontant->value();
    o.adrLiv = ui->leAdrLiv->text();
    o.priority = ui->cbPriority->currentText();

    if (!m_dao.add(o)) {
        QMessageBox::warning(m_mainWindow, "Commande", "Échec de l'ajout: " + Db::instance().lastError());
    }
    refreshOrders();
}

void OrderController::updateOrder() {
    if (m_selectedOrderId == -1) {
        QMessageBox::warning(m_mainWindow, "Commande", "Veuillez sélectionner une commande à modifier");
        return;
    }

    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (!validateForm()) return;

    auto orderOpt = m_dao.getById(m_selectedOrderId);
    if (!orderOpt.has_value()) {
        QMessageBox::warning(m_mainWindow, "Commande", "Commande non trouvée");
        return;
    }

    Order o = orderOpt.value();
    o.clientId = ui->cbClient->currentData().toInt();
    o.etat = ui->cbEtat->currentText();
    o.montant = ui->dsMontant->value();
    o.adrLiv = ui->leAdrLiv->text();
    o.priority = ui->cbPriority->currentText();

    if (!m_dao.update(o)) {
        QMessageBox::warning(m_mainWindow, "Commande", "Échec de la modification: " + Db::instance().lastError());
    } else {
        QMessageBox::information(m_mainWindow, "Commande", "Commande modifiée avec succès");
        refreshOrders();
    }
}

void OrderController::deleteOrder() {
    if (m_selectedOrderId == -1) {
        QMessageBox::warning(m_mainWindow, "Commande", "Veuillez sélectionner une commande à supprimer");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(m_mainWindow, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette commande?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (!m_dao.remove(m_selectedOrderId)) {
            QMessageBox::warning(m_mainWindow, "Commande", "Échec de la suppression: " + Db::instance().lastError());
        }
        refreshOrders();
    }
}

void OrderController::refreshOrders() {
    loadOrdersTable();
}

void OrderController::loadOrdersTable() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    auto orders = m_dao.getAll();

    ui->tblOrders->clearContents();
    ui->tblOrders->setRowCount(orders.size());
    ui->tblOrders->setColumnCount(8);

    QStringList headers = {"ID", "Client ID", "Date", "État", "Montant", "Adresse Livraison", "Priorité", "Livraison Estimée"};
    ui->tblOrders->setHorizontalHeaderLabels(headers);
    ui->tblOrders->horizontalHeader()->setStretchLastSection(true);

    for (int i = 0; i < orders.size(); ++i) {
        const auto &o = orders[i];

        ui->tblOrders->setItem(i, 0, new QTableWidgetItem(QString::number(o.id)));
        ui->tblOrders->setItem(i, 1, new QTableWidgetItem(QString::number(o.clientId)));
        ui->tblOrders->setItem(i, 2, new QTableWidgetItem(o.date.toString("yyyy-MM-dd")));
        ui->tblOrders->setItem(i, 3, new QTableWidgetItem(o.statusText()));
        ui->tblOrders->setItem(i, 4, new QTableWidgetItem(QString::number(o.montant, 'f', 3)));
        ui->tblOrders->setItem(i, 5, new QTableWidgetItem(o.adrLiv));
        ui->tblOrders->setItem(i, 6, new QTableWidgetItem(o.priority));

        QTableWidgetItem* deliveryItem = new QTableWidgetItem();
        if (o.estimatedDelivery.isValid()) {
            deliveryItem->setText(o.estimatedDelivery.toString("yyyy-MM-dd"));
        }
        ui->tblOrders->setItem(i, 7, deliveryItem);
    }

    applyFilters();
    updateChart();
}

void OrderController::applyFilters() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    QString text = ui->leSearchOrder->text().trimmed();
    int clientId = ui->cbClientFilter->currentData().toInt();
    QString etat = ui->cbEtatFilter->currentText();
    double minAmount = ui->dsMinAmount->value();
    double maxAmount = ui->dsMaxAmount->value();
    QString sortKey = ui->cbOrderSort->currentText();

    for (int r = 0; r < ui->tblOrders->rowCount(); ++r) {
        ui->tblOrders->setRowHidden(r, false);
    }

    for (int r = 0; r < ui->tblOrders->rowCount(); ++r) {
        bool match = true;

        // Text search (état, adresse)
        if (!text.isEmpty()) {
            QString rowText = ui->tblOrders->item(r, 3)->text() + " " + ui->tblOrders->item(r, 5)->text();
            match &= rowText.contains(text, Qt::CaseInsensitive);
        }

        // Client filter
        if (clientId > 0) {
            int rowClientId = ui->tblOrders->item(r, 1)->text().toInt();
            match &= (rowClientId == clientId);
        }

        // Status filter
        if (etat != "Tous") {
            match &= ui->tblOrders->item(r, 3)->text() == etat;
        }

        // Amount range filter
        double amount = ui->tblOrders->item(r, 4)->text().toDouble();
        if (minAmount > 0) match &= (amount >= minAmount);
        if (maxAmount > 0) match &= (amount <= maxAmount);

        if (!match) {
            ui->tblOrders->setRowHidden(r, true);
        }
    }

    if (sortKey == "Date") {
        ui->tblOrders->sortItems(2);
    } else if (sortKey == "Montant") {
        ui->tblOrders->sortItems(4);
    } else if (sortKey == "État") {
        ui->tblOrders->sortItems(3);
    }
}

void OrderController::updateChart() {
    QChartView* orderChartView = m_mainWindow->orderChartView;
    if (!orderChartView) return;

    auto statusCounts = m_dao.getOrdersByStatus();

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Commandes");

    QStringList categories;
    for (const auto &pair : statusCounts) {
        *set << pair.second;
        categories << pair.first;
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Commandes par état");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    orderChartView->setChart(chart);
}

void OrderController::exportToPdf() {
    if (m_selectedOrderId == -1) {
        QMessageBox::warning(m_mainWindow, "PDF", "Veuillez sélectionner une commande.");
        return;
    }

    auto orderOpt = m_dao.getById(m_selectedOrderId);
    if (!orderOpt.has_value()) {
        QMessageBox::warning(m_mainWindow, "PDF", "Commande introuvable.");
        return;
    }

    Order o = orderOpt.value();

    QString defaultName = QString("commande_%1.pdf").arg(o.id);
    QString filePath = QFileDialog::getSaveFileName(m_mainWindow, "Enregistrer le PDF", defaultName, "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    QPainter painter(&writer);

    if (!painter.isActive()) {
        QMessageBox::warning(m_mainWindow, "PDF", "Impossible de créer le PDF.");
        return;
    }

    int x = 500;
    int y = 500;
    int line = 400;

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
    painter.drawText(x, y, QString("État: %1").arg(o.statusText())); y += line;
    painter.drawText(x, y, QString("Montant: %1 DT").arg(QString::number(o.montant, 'f', 3))); y += line;
    painter.drawText(x, y, QString("Adresse de livraison: %1").arg(o.adrLiv)); y += line;
    painter.drawText(x, y, QString("Priorité: %1").arg(o.priority)); y += line;

    if (o.estimatedDelivery.isValid()) {
        painter.drawText(x, y, QString("Livraison estimée: %1").arg(o.estimatedDelivery.toString("yyyy-MM-dd"))); y += line;
    }

    painter.end();
    QMessageBox::information(m_mainWindow, "PDF", "PDF généré avec succès.");
}

void OrderController::showStats() {
    double totalRevenue = m_dao.getTotalRevenue();
    auto statusCounts = m_dao.getOrdersByStatus();

    QString message = "Statistiques commandes:\n\n";
    message += QString("Revenu total: %1 DT\n").arg(totalRevenue, 0, 'f', 3);
    message += "Commandes par état:\n";

    for (const auto &pair : statusCounts) {
        message += QString("%1: %2 commandes\n").arg(pair.first).arg(pair.second);
    }

    QMessageBox::information(m_mainWindow, "Statistiques Commandes", message);
}

void OrderController::updateOrderPriority() {
    if (m_selectedOrderId == -1) {
        QMessageBox::warning(m_mainWindow, "Priorité", "Veuillez sélectionner une commande");
        return;
    }

    QStringList priorities = {"LOW", "NORMAL", "HIGH", "URGENT"};
    QString priority = QInputDialog::getItem(m_mainWindow, "Priorité commande",
                                             "Sélectionnez la priorité:", priorities, 1, false);

    if (priority.isEmpty()) return;

    if (m_dao.updatePriority(m_selectedOrderId, priority)) {
        QMessageBox::information(m_mainWindow, "Priorité", "Priorité mise à jour avec succès");
        refreshOrders();
    } else {
        QMessageBox::warning(m_mainWindow, "Priorité", "Échec de la mise à jour");
    }
}

void OrderController::autoUpdatePriorities() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(m_mainWindow, "Mise à jour automatique des priorités",
                                  "Êtes-vous sûr de vouloir mettre à jour automatiquement les priorités de toutes les commandes?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_dao.autoUpdatePriorities()) {
            QMessageBox::information(m_mainWindow, "Priorités", "Priorités mises à jour automatiquement avec succès");
            refreshOrders();
        } else {
            QMessageBox::warning(m_mainWindow, "Priorités", "Échec de la mise à jour automatique");
        }
    }
}

bool OrderController::validateForm() {
    Ui::MainWindow* ui = m_mainWindow->getUi();
    if (ui->cbClient->currentData().toInt() <= 0) {
        QMessageBox::warning(m_mainWindow, "Validation", "Veuillez sélectionner un client");
        ui->cbClient->setFocus();
        return false;
    }
    if (ui->dsMontant->value() <= 0) {
        QMessageBox::warning(m_mainWindow, "Validation", "Le montant doit être positif");
        ui->dsMontant->setFocus();
        return false;
    }
    if (ui->leAdrLiv->text().isEmpty()) {
        QMessageBox::warning(m_mainWindow, "Validation", "L'adresse de livraison est obligatoire");
        ui->leAdrLiv->setFocus();
        return false;
    }
    return true;
}
