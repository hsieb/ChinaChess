#include "modechange.h"
#include "ui_modechange.h"
#include "mainwindow.h"
#include "mainwindow1.h"
#include <QtNetwork>
#include <iostream>
using namespace std;

QTcpSocket* ModeChange::tcpSocket =new QTcpSocket ;
QTcpSocket* ModeChange::tcpSendSocket =new QTcpSocket ;
QTcpServer* ModeChange::tcpServer = new QTcpServer;

ModeChange::ModeChange(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModeChange)
{
    ui->setupUi(this);
    mw = new MainWindow;
    mw1 = new MainWindow1;
    udpSocket = new QUdpSocket();
    udpSocket_b = new QUdpSocket();
    udpSocket_b->bind(8888,QUdpSocket::ShareAddress);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage_b()));
    connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));
    connect(udpSocket_b, SIGNAL(readyRead()),
                this, SLOT(dataReceived()));

    if(!tcpServer->listen(QHostAddress::Any,8888))//QHostAddress::LocalHost
        {
            qDebug() << tcpServer->errorString();
            close();
    }
}


ModeChange::~ModeChange()
{
    myFree();
    udpSocket->close();
    udpSocket_b->close();
    delete udpSocket_b;
    delete udpSocket;
    delete mw;
    delete mw1;
    delete ui;
}

void ModeChange::on_selectPlay_clicked()
{

    cout<<QNetworkInterface().allAddresses().at(1).toString().toStdString()<<endl;
    if(ui->hostLineEdit->text()==""){
        return;
    }else if(QNetworkInterface().allAddresses().at(1).toString()==ui->hostLineEdit->text()){
        ui->hostLineEdit->setText("不能连自己");
        return ;
    }
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->hostLineEdit->text(),// ip
                             8888); //端口

}

void ModeChange::readMessage() //服务器读取
{

    QByteArray byteArray = this->tcpSendSocket->readAll();
    if(byteArray == "play"){
        mw->user = 2;
        mw->displayP(mw->user);
        mw->show();
        this->hide();
    }else if(byteArray == "backstep"){
        mw->isBackStep();
    }else if(byteArray == "yes"){
        mw->backStepOk();
    }else if(byteArray == "no"){
        mw->backStepNo();
    }else{
        mw->dropChess(byteArray);
    }
    blockSize = 0;
}

void ModeChange::readMessage_b()
{
    QByteArray byteArray = this->tcpSocket->readAll();
    cout<<"rb!!"<<endl;
    cout<<byteArray.toStdString()<<endl;    
    if(byteArray == "play"){
        mw->user = 2;
        mw->displayP(mw->user);
        mw->show();
        this->hide();
    }else if(byteArray == "backstep"){
        mw->isBackStep();
    }else if(byteArray == "yes"){
        mw->backStepOk();
    }else if(byteArray == "no"){
        mw->backStepNo();
    }else{
        mw->dropChess(byteArray);
    }
    blockSize = 0;

}


void ModeChange::on_makePlay_clicked()
{
    ui->makePlay->setText("已创建");
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
    udpSocket->writeDatagram("hehe",QHostAddress::Broadcast,8888);
    ui->makePlay->setEnabled(false);
    ui->selectPlay->setEnabled(false);
}

void ModeChange::sendMessage()
{
    blockSize =0;
    tcpSendSocket = tcpServer->nextPendingConnection();
    connect(tcpSendSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSendSocket,SIGNAL(disconnected()),tcpSendSocket,SLOT(deleteLater()));
    playChess("play");
    mw->user = 1;
    mw->displayP(mw->user);
    mw->show();
    this->hide();
}

void ModeChange::playChess(char *str){
    cout<<"aaaaaaaa"<<endl;
    cout<<str<<endl;
//    QByteArray block;
//    QDataStream out(&block,QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_6);
//    out<<(quint16) 0;
//    out<<tr(str);
//    cout<<str<<endl;
//    out.device()->seek(0);
//    out<<(quint16)(block.size() - sizeof(quint16));
//    tcpSendSocket->write(block);
    tcpSendSocket->flush();
    tcpSendSocket->write(str);
    cout<<"send _ok"<<endl;
    //tcpSendSocket->disconnectFromHost();
}

void ModeChange::playChess_b(char *str){
    tcpSocket->flush();
    tcpSocket->write(str);
    cout<<"send _ok"<<endl;
}

void ModeChange::myFree(){
    tcpSocket->disconnectFromHost();
    tcpSendSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSendSocket->close();
    tcpServer->close();
    delete tcpSocket;
    delete tcpSendSocket;
    delete tcpServer;
    tcpSocket = nullptr;
    tcpSendSocket = nullptr;
    tcpServer = nullptr;
}

void ModeChange::chat(QString str){
    tcpSendSocket->flush();
    tcpSendSocket->write(str.toUtf8().data());
}

void ModeChange::chat_b(QString str){
    tcpSocket->flush();
    tcpSocket->write(str.toUtf8().data());
}

void ModeChange::dataReceived(){
    QHostAddress targetaddr;
    quint16 targetport;
    while(udpSocket_b->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket_b->pendingDatagramSize());
            udpSocket_b->readDatagram(datagram.data(), datagram.size(),&targetaddr,&targetport);


            QStringList list = (targetaddr.toString()).split(":");
            if(datagram.toStdString()=="1"){
                if(ui->makePlay->text()=="已创建"){
                   udpSocket->writeDatagram("hehe",QHostAddress::Broadcast,8888);
                }
            }else{
                ui->textBrowser->append(list[3]);
            }

    }
}

void ModeChange::on_flash_clicked()
{
    ui->textBrowser->clear();
    udpSocket->writeDatagram("1",QHostAddress::Broadcast,8888);
}

void ModeChange::on_pvp_clicked()
{
    mw1->show();
    this->hide();
}
