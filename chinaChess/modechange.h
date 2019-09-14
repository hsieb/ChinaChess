#ifndef MODECHANGE_H
#define MODECHANGE_H

#include <QMainWindow>
#include <QtNetwork>
#include "mainwindow.h"
#include "mainwindow1.h"
namespace Ui {
class ModeChange;
}

class ModeChange : public QMainWindow
{
    Q_OBJECT

private:
    //udp
    QUdpSocket *udpSocket;
    QUdpSocket *udpSocket_b;
    //client
    static QTcpSocket *tcpSocket;
    static QTcpSocket *tcpSendSocket;
    QString message;
    quint16 blockSize;
    //server
    static QTcpServer *tcpServer;

public:
    explicit ModeChange(QWidget *parent = nullptr);
    ~ModeChange();
    static void playChess(char *str);
    static void playChess_b(char *str);
    static void chat(QString);
    static void chat_b(QString);
    static void myFree();

private slots:
    void on_selectPlay_clicked();

    void on_makePlay_clicked();
    void sendMessage();
    void readMessage();
    void readMessage_b();
    void dataReceived();

    void on_flash_clicked();

    void on_pvp_clicked();

private:
    Ui::ModeChange *ui;
    MainWindow *mw;
    MainWindow1 *mw1;

};


#endif // MODECHANGE_H
