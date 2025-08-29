#pragma once

#include <QDialog>
#include <QString>
#include <QResizeEvent>
#include <QPixmap>

// Forward declaration to avoid circular dependencies
class Db;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    QString getUsername() const;
    QString getRole() const;
    int getUserId() const;

private slots:
    void onLoginClicked();
    void onCancelClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::LoginDialog *ui;
    QString m_username;
    QString m_role;
    int m_userId;
    QPixmap m_background;
    bool m_backgroundLoaded;

    bool authenticateUser(const QString &username, const QString &password);
    void loadBackgroundImage();
    void applyTransparentStyles();
};
