#pragma once

#include <QDialog>
#include <QString>
#include <QResizeEvent>
#include <QPixmap>
#include <QPropertyAnimation>

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

    void showLoginForm();
    void showSignupForm();

signals:
    void signupRequested(const QString &username, const QString &password, const QString &role);

private slots:
    void onLoginClicked();
    void onSignupClicked();
    void onCancelClicked();
    void onSwitchToSignupClicked();
    void onSwitchToLoginClicked();

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
    bool registerUser(const QString &username, const QString &password, const QString &role);
    void loadBackgroundImage();
    void applyTransparentStyles();
    void setupAnimations();
    void animateTransition(bool toSignup);
};
