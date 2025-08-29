#pragma once

#include <QDialog>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    int getUserId() const;
    QString getUsername() const;
    QString getRole() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onSwitchToRegisterClicked();
    void onSwitchToLoginClicked();

private:
    void centerOnScreen();
    void setupAnimations();
    void showLoginForm();
    void showRegisterForm();
    void animateTransition(bool toRegister);

    Ui::LoginDialog *ui;
    int m_userId;
    QString m_username;
    QString m_role;
    QPoint m_dragPosition;
    
    QPropertyAnimation *m_fadeInAnimation;
    QPropertyAnimation *m_fadeOutAnimation;
};
