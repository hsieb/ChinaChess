#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string.h>
#include <QMainWindow>
#include <QVector>
#include "item.h"
#include <QTimer>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int user;//P1和P2
    void dropChess(QString );
    void displayP(int);
    void isBackStep();
    void backStepOk();
    void backStepNo();
    bool msgFun(QString);
    void isPeace();
    void isPeaceOk();
    void isPeaceNo();
    void isChangeColor();
    void isChangeCOk();
    void isChangeCNo();


private slots:
    void mySlots_recvUsername(QString);
    void myTimer();
    void on_backStep_clicked();

    void on_ready_clicked();

    void on_sendMsg_clicked();

    void on_peace_clicked();

    void on_changeColor_clicked();

private:
    Ui::MainWindow *ui;
    QPainter *p;
    int selectedQiziIndex;
    int dropIndex = -1;
    int dropIndex_X;
    int dropIndex_Y;
    static int isLocation;
    bool isEatStatus = false;
    int stepNum=0;
    int baseX = 350;
    int baseY = 50;
    int gridWidth = 70;
    int gridHeight = 70;
    bool isSelectQizi = false;
    QVector<ITEM> m_items;//就是局面数组
    QVector<QVector<ITEM>> history;//历史所有局面，悔棋用
    QTimer *timer;
    int gameTime=45;
    bool playStatus = false;
    int readyStatus = 0;

private:
    void paintEvent(QPaintEvent *event);
    void drawQiPan();
    void drawChessItems();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void gameOver(QVector<ITEM> &m_items);
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
