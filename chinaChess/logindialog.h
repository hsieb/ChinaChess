#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void sendUsername(QString);

private slots:
    void on_pushButtonLogin_clicked();

    void on_pushButtonReset_clicked();

private:
    Ui::LoginDialog *ui;
    MainWindow *mw;

};

#endif // LOGINDIALOG_H
