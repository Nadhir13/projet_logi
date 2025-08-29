#pragma once

#include <QObject>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>

class StyleManager : public QObject
{
    Q_OBJECT

public:
    static StyleManager& instance();
    
    void applyModernStyle();
    void applyDarkStyle();
    void applyLightStyle();
    void applyCustomStyle(const QString& stylePath);
    
    QString getCurrentStyle() const { return m_currentStyle; }
    
private:
    StyleManager(QObject* parent = nullptr);
    ~StyleManager() = default;
    StyleManager(const StyleManager&) = delete;
    StyleManager& operator=(const StyleManager&) = delete;
    
    void loadStyleSheet(const QString& path);
    QString m_currentStyle;
};
