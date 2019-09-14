#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    mw = new MainWindow;
    connect(this,SIGNAL(sendUsername(QString)),mw,SLOT(mySlots_recvUsername(QString)));
    this->setMinimumSize(431,318);
    this->setMaximumSize(431,318);
}

LoginDialog::~LoginDialog()
{
    delete mw;
    delete ui;
}

void LoginDialog::on_pushButtonLogin_clicked()
{
    QString name = ui->userName->text();
    QString pwd  = ui->userPwd->text();

    if(name == "hsieb" && pwd == "123456"){
        emit sendUsername(name);
        mw->show();
        this->hide();
    }else {
        QMessageBox::warning(this,"登入失败","用户名或密码错误",QMessageBox::Ok,QMessageBox::Cancel);

    }
}

void LoginDialog::on_pushButtonReset_clicked()
{
    ui->userName->setText("");
    ui->userPwd->setText("");
}

