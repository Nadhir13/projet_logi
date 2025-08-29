#pragma once

#include <QDialog>
#include <QString>
#include "db.h"

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

private:
    Ui::LoginDialog *ui;
    QString m_username;
    QString m_role;
    int m_userId;
    bool authenticateUser(const QString &username, const QString &password);
};
