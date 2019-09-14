#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H
#include <string.h>
#include <QMainWindow>
#include <QVector>
#include "item.h"
#include <QTimer>
#include <QCloseEvent>

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();

private slots:

    void myTimer();
    void on_play_clicked();

    void on_backStep_clicked();

    void on_rePlay_clicked();

private:
    Ui::MainWindow1 *ui;
    QPainter *p;
    int selectedQiziIndex;
    int dropIndex = -1;
    int dropIndex_X;
    int dropIndex_Y;
    static int isLocation1;
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

private:
    void paintEvent(QPaintEvent *event);
    void drawQiPan();
    void drawChessItems();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void gameOver(QVector<ITEM> &m_items);
};

#endif // MAINWINDOW1_H
