#include "stylemanager.h"
#include <QDebug>

StyleManager::StyleManager(QObject* parent)
    : QObject(parent), m_currentStyle("default")
{
}

StyleManager& StyleManager::instance()
{
    static StyleManager instance;
    return instance;
}

void StyleManager::applyModernStyle()
{
    loadStyleSheet(":/styles/modern.qss");
    m_currentStyle = "modern";
}

void StyleManager::applyDarkStyle()
{
    QString darkStyle = R"(
        /* Dark Theme */
        QMainWindow, QDialog {
            background: #2d3748;
            color: #e2e8f0;
        }
        
        QTabWidget::pane {
            border: 2px solid #4a5568;
            background: #2d3748;
        }
        
        QTabBar::tab {
            background: #4a5568;
            color: #e2e8f0;
            border: 1px solid #4a5568;
            padding: 12px 20px;
        }
        
        QTabBar::tab:selected {
            background: #3182ce;
            color: white;
        }
        
        QPushButton {
            background: #3182ce;
            border: none;
            border-radius: 6px;
            color: white;
            padding: 10px 20px;
            font-weight: 600;
        }
        
        QPushButton:hover {
            background: #2c5aa0;
        }
        
        QLineEdit, QTextEdit, QPlainTextEdit {
            border: 2px solid #4a5568;
            border-radius: 6px;
            padding: 8px 12px;
            background: #4a5568;
            color: #e2e8f0;
        }
        
        QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus {
            border-color: #3182ce;
        }
        
        QComboBox {
            border: 2px solid #4a5568;
            border-radius: 6px;
            padding: 8px 12px;
            background: #4a5568;
            color: #e2e8f0;
        }
        
        QTableWidget {
            background: #4a5568;
            alternate-background-color: #2d3748;
            color: #e2e8f0;
            gridline-color: #4a5568;
            border: 2px solid #4a5568;
        }
        
        QHeaderView::section {
            background: #2d3748;
            color: #e2e8f0;
            border: 1px solid #4a5568;
            padding: 12px 8px;
        }
        
        QMenuBar {
            background: #2d3748;
            color: #e2e8f0;
            border-bottom: 1px solid #4a5568;
        }
        
        QMenu {
            background: #4a5568;
            color: #e2e8f0;
            border: 2px solid #4a5568;
        }
        
        QMenu::item:selected {
            background: #3182ce;
        }
    )";
    
    qApp->setStyleSheet(darkStyle);
    m_currentStyle = "dark";
}

void StyleManager::applyLightStyle()
{
    QString lightStyle = R"(
        /* Light Theme */
        QMainWindow, QDialog {
            background: #ffffff;
            color: #2d3748;
        }
        
        QTabWidget::pane {
            border: 2px solid #e2e8f0;
            background: #ffffff;
        }
        
        QTabBar::tab {
            background: #f7fafc;
            color: #4a5568;
            border: 1px solid #e2e8f0;
            padding: 12px 20px;
        }
        
        QTabBar::tab:selected {
            background: #3182ce;
            color: white;
        }
        
        QPushButton {
            background: #3182ce;
            border: none;
            border-radius: 6px;
            color: white;
            padding: 10px 20px;
            font-weight: 600;
        }
        
        QPushButton:hover {
            background: #2c5aa0;
        }
        
        QLineEdit, QTextEdit, QPlainTextEdit {
            border: 2px solid #e2e8f0;
            border-radius: 6px;
            padding: 8px 12px;
            background: #ffffff;
            color: #2d3748;
        }
        
        QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus {
            border-color: #3182ce;
        }
        
        QComboBox {
            border: 2px solid #e2e8f0;
            border-radius: 6px;
            padding: 8px 12px;
            background: #ffffff;
            color: #2d3748;
        }
        
        QTableWidget {
            background: #ffffff;
            alternate-background-color: #f7fafc;
            color: #2d3748;
            gridline-color: #e2e8f0;
            border: 2px solid #e2e8f0;
        }
        
        QHeaderView::section {
            background: #f7fafc;
            color: #4a5568;
            border: 1px solid #e2e8f0;
            padding: 12px 8px;
        }
        
        QMenuBar {
            background: #f7fafc;
            color: #4a5568;
            border-bottom: 1px solid #e2e8f0;
        }
        
        QMenu {
            background: #ffffff;
            color: #2d3748;
            border: 2px solid #e2e8f0;
        }
        
        QMenu::item:selected {
            background: #3182ce;
            color: white;
        }
    )";
    
    qApp->setStyleSheet(lightStyle);
    m_currentStyle = "light";
}

void StyleManager::applyCustomStyle(const QString& stylePath)
{
    loadStyleSheet(stylePath);
    m_currentStyle = "custom";
}

void StyleManager::loadStyleSheet(const QString& path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        qApp->setStyleSheet(styleSheet);
        file.close();
        qDebug() << "Style sheet loaded from:" << path;
    } else {
        qWarning() << "Failed to load style sheet from:" << path;
        qWarning() << "Error:" << file.errorString();
    }
}
