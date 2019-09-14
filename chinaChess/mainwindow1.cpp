#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include <QPainter>
#include <QMessageBox>
#include <QPaintEvent>
#include <iostream>
#include "item.h"
#include "tool.h"

int MainWindow1::isLocation1 = 0;
MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    this->setMinimumSize(1280,720);
    this->setMaximumSize(1280,720);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myTimer()));
    init_items(m_items);
    ui->backStep->setEnabled(false);
}

MainWindow1::~MainWindow1()
{
    delete timer;
    delete p;
    delete ui;
}

void MainWindow1::myTimer(){

    ui->gameTime->setText("剩余时间:"+QString::number(gameTime)+"秒");
    if(stepNum%2==0){
        ui->color->setText("红方正在下...");
        if(gameTime<=0){
             QMessageBox::warning(this,"游戏结束","红方超时,黑方获胜",QMessageBox::Ok,QMessageBox::NoButton);
             gameOver(m_items);
        }
    }else if(stepNum%2==1){
        ui->color->setText("黑方正在下...");
        if(gameTime<=0){
             QMessageBox::warning(this,"游戏结束","黑方超时,红方获胜",QMessageBox::Ok,QMessageBox::NoButton);
             gameOver(m_items);
        }
    }
    gameTime--;
}

void MainWindow1::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);//屏蔽未使用变量提示
    p = new QPainter(this);//将指针传入新创建的画板
    drawQiPan();
    drawChessItems();
    p->end();
    delete p;
    p = nullptr;
   // cout<<"paintEvent invoke..."<<endl;
}

void MainWindow1::drawQiPan(){
    QPen pen(Qt::black,2);
    p->setPen(pen);
    //先两条画边线
    QPoint ps(baseX,baseY);
    QPoint pe(baseX,baseY+gridHeight*9);
    p->drawLine(ps,pe);
    QPoint ps2(baseX+gridWidth*8,baseY);
    QPoint pe2(baseX+gridWidth*8,baseY+gridHeight*9);
    p->drawLine(ps2,pe2);
    //再画内棋盘线
    //上半部分竖线
    for(int i = 1; i < 8; i++){
        QPoint ps(baseX+i*gridWidth,baseY);
        QPoint pe(baseX+i*gridHeight,baseY+gridHeight*4);
        p->drawLine(ps,pe);
    }

    //下半部分竖线
    for(int i = 1; i < 8; i++){
        QPoint ps(baseX+i*gridWidth,baseY+gridHeight*5);
        QPoint pe(baseX+i*gridHeight,baseY+gridHeight*9);
        p->drawLine(ps,pe);
    }
    //所有的横线
    for(int i = 0; i < 10; i++){
        QPoint ps(baseX,baseY+i*gridWidth);
        QPoint pe(baseX+gridWidth*8,baseY+i*gridHeight);
        p->drawLine(ps,pe);
    }
    int lineLen = 10;
    QPoint points[10];
    points[0]=QPoint(baseX+1*gridWidth,baseY+2*gridHeight);
    points[1]=QPoint(baseX+7*gridWidth,baseY+2*gridHeight);
    points[2]=QPoint(baseX+2*gridWidth,baseY+3*gridHeight);
    points[3]=QPoint(baseX+4*gridWidth,baseY+3*gridHeight);
    points[4]=QPoint(baseX+6*gridWidth,baseY+3*gridHeight);
    points[5]=QPoint(baseX+2*gridWidth,baseY+6*gridHeight);
    points[6]=QPoint(baseX+4*gridWidth,baseY+6*gridHeight);
    points[7]=QPoint(baseX+6*gridWidth,baseY+6*gridHeight);
    points[8]=QPoint(baseX+1*gridWidth,baseY+7*gridHeight);
    points[9]=QPoint(baseX+7*gridWidth,baseY+7*gridHeight);
    for(int i=0;i<10;i++){
        //左上
        QPoint center = points[i];
        QPoint sLU0(center.x()-3,center.y()-3);
        QPoint eLU0(center.x()-3-lineLen,center.y()-3);
        p->drawLine(sLU0,eLU0);
        QPoint sLU1(center.x()-3,center.y()-3);
        QPoint eLU1(center.x()-3,center.y()-3-lineLen);
        p->drawLine(sLU1,eLU1);
        //左下
        QPoint sLD0(center.x()-3,center.y()+3);
        QPoint eLD0(center.x()-3-lineLen,center.y()+3);
        p->drawLine(sLD0,eLD0);
        QPoint sLD1(center.x()-3,center.y()+3);
        QPoint eLD1(center.x()-3,center.y()+3+lineLen);
        p->drawLine(sLD1,eLD1);

        //右上
        QPoint sRU0(center.x()+3,center.y()-3);
        QPoint eRU0(center.x()+3,center.y()-3-lineLen);
        p->drawLine(sRU0,eRU0);
        QPoint sRU1(center.x()+3,center.y()-3);
        QPoint eRU1(center.x()+3+lineLen,center.y()-3);
        p->drawLine(sRU1,eRU1);
        //右下
        QPoint sRD0(center.x()+3,center.y()+3);
        QPoint eRD0(center.x()+3,center.y()+3+lineLen);
        p->drawLine(sRD0,eRD0);
        QPoint sRD1(center.x()+3,center.y()+3);
        QPoint eRD1(center.x()+3+lineLen,center.y()+3);
        p->drawLine(sRD1,eRD1);
    }

    //左边一兵一卒位置
    QPoint points2[2];
    points2[0]=QPoint(baseX,baseY+3*gridHeight);
    points2[1]=QPoint(baseX,baseY+6*gridHeight);
    for(int i=0;i<2;i++){
        //右上
        QPoint center = points2[i];
        QPoint sRU0(center.x()+3,center.y()-3);
        QPoint eRU0(center.x()+3,center.y()-3-lineLen);
        p->drawLine(sRU0,eRU0);
        QPoint sRU1(center.x()+3,center.y()-3);
        QPoint eRU1(center.x()+3+lineLen,center.y()-3);
        p->drawLine(sRU1,eRU1);
        //右下
        QPoint sRD0(center.x()+3,center.y()+3);
        QPoint eRD0(center.x()+3,center.y()+3+lineLen);
        p->drawLine(sRD0,eRD0);
        QPoint sRD1(center.x()+3,center.y()+3);
        QPoint eRD1(center.x()+3+lineLen,center.y()+3);
        p->drawLine(sRD1,eRD1);
    }

    QPoint points3[4];
    points3[0]=QPoint(baseX+8*gridWidth,baseY+3*gridHeight);
    points3[1]=QPoint(baseX+8*gridWidth,baseY+6*gridHeight);
    for(int i=0;i<2;i++){
        //左上
        QPoint center = points3[i];
        QPoint sLU0(center.x()-3,center.y()-3);
        QPoint eLU0(center.x()-3-lineLen,center.y()-3);
        p->drawLine(sLU0,eLU0);
        QPoint sLU1(center.x()-3,center.y()-3);
        QPoint eLU1(center.x()-3,center.y()-3-lineLen);
        p->drawLine(sLU1,eLU1);
        //左下
        QPoint sLD0(center.x()-3,center.y()+3);
        QPoint eLD0(center.x()-3-lineLen,center.y()+3);
        p->drawLine(sLD0,eLD0);
        QPoint sLD1(center.x()-3,center.y()+3);
        QPoint eLD1(center.x()-3,center.y()+3+lineLen);
        p->drawLine(sLD1,eLD1);
    }
    //画士/仕的斜线
    QPoint ps3(baseX+3*gridWidth,baseY);
    QPoint pe3(baseX+5*gridWidth,baseY+2*gridHeight);
    p->drawLine(ps3,pe3);
    QPoint ps33(baseX+3*gridWidth,baseY+2*gridHeight);
    QPoint pe33(baseX+5*gridWidth,baseY);
    p->drawLine(ps33,pe33);

    QPoint ps4(baseX+3*gridWidth,baseY+9*gridHeight);
    QPoint pe4(baseX+5*gridWidth,baseY+7*gridHeight);
    p->drawLine(ps4,pe4);
    QPoint ps44(baseX+3*gridWidth,baseY+7*gridHeight);
    QPoint pe44(baseX+5*gridWidth,baseY+9*gridHeight);
    p->drawLine(ps44,pe44);

    //p->end();//这个方法的正确用法是每次画完之后释放所有的资源
}

void MainWindow1::drawChessItems(){
    for(int i=0;i<m_items.length();i++){
        if(m_items[i].status==1){
            QPixmap pixmap(m_items[i].path);
            QSize size(60,60);
            pixmap = pixmap.scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            p->drawPixmap(baseX-30+m_items[i].x*gridWidth,baseY-30+m_items[i].y*gridHeight,pixmap);
        }
    }
}

void MainWindow1::gameOver(QVector<ITEM> &m_items){
    playStatus = false;
    ui->play->setText("开始");
    ui->play->setEnabled(true);
   ui->tip2->setText("");
   timer->stop();
   QVector<ITEM> pNullVector;  //局部变量
   m_items.swap(pNullVector);
   init_items(m_items);
   stepNum=0;
   ui->color->setText("未开始！");
   ui->gameTime->setText("剩余时间：");
   ui->backStep->setEnabled(false);
   gameTime = 45;
}

void MainWindow1::mouseDoubleClickEvent(QMouseEvent *event){
    if(playStatus){
        QPoint currPos = event->pos();
        QPoint &refPos = currPos;
        QPoint* stdPos = calcNearestCoor(refPos,baseX,baseY,gridWidth,gridHeight);
        if(!isSelectQizi){
            int w = (baseX+stdPos->x()*gridWidth)-currPos.x();
            int h = (baseY+stdPos->y()*gridHeight)-currPos.y();
            if(w*w+h*h<=(gridWidth/2)*(gridHeight/2)){
                for (int i=0;i<m_items.length();i++) {
                    if(m_items[i].x == stdPos->x() && m_items[i].y == stdPos->y() && m_items[i].status==1){
                        selectedQiziIndex = i;
                        cout<<selectedQiziIndex<<".."<<m_items[selectedQiziIndex].name.toStdString()<<endl;
                        if(m_items[i].color==1 &&stepNum%2==0){
                            isSelectQizi = true;
                            ui->tip->setText("你选中了"+m_items[selectedQiziIndex].name2);
                            timer->start(1000);
                        }else if( m_items[i].color==0 &&stepNum%2==1){
                            isSelectQizi = true;
                            ui->tip->setText("你选中了"+m_items[selectedQiziIndex].name2);
                            timer->start(1000);
                        }
                        break;
                    }
                }
            }else{
                isSelectQizi = false;
            }
            delete stdPos;
        }else{
            for (int i=0;i<m_items.length();i++) {
                if(m_items[i].x == stdPos->x() && m_items[i].y == stdPos->y()){
                    cout<<i<<endl;
                    dropIndex = i;
                    dropIndex_X = m_items[i].x;
                    dropIndex_Y = m_items[i].y;
                    if(m_items[selectedQiziIndex].color == m_items[i].color){
                        MainWindow1::isLocation1 = 1;
                        cout<<"lllll:"<<MainWindow1::isLocation1<<endl;
                        isSelectQizi = false;
                        break;
                    }else{
                        isEatStatus = isEat(i,selectedQiziIndex,m_items);
                        isSelectQizi = false;
                        break;
                    }
                }
            }
            bool chessMove = isCheckMove(stdPos,selectedQiziIndex,m_items);
            if(!history.empty()){
                history.pop_back();
            }
            history.push_back(m_items);
            ui->backStep->setEnabled(true);
            ui->tip2->setText("");

            if(chessMove && !MainWindow1::isLocation1 && !isEatStatus){
                gameTime = 45;
                timer->start(1000);
                m_items[selectedQiziIndex].x = stdPos->x();
                m_items[selectedQiziIndex].y = stdPos->y();
                if(m_items[selectedQiziIndex].color==1){
                    if(isKill(1,m_items)){
                        ui->tip2->setText("将军");
                        //cout<<"kill!!!!!!!!!"<<endl;
                    }
                }else if(m_items[selectedQiziIndex].color==0){
                    if(isKill(2,m_items)){
                        ui->tip2->setText("将军");
                        //cout<<"kill!!!!!!!!!"<<endl;
                    }
                }
                isSelectQizi = false;
                dropIndex = -1;
                ui->tip->setText("");
                stepNum++;
                if(isMeet(m_items)){
                    timer->stop();
                    if(stepNum%2==0){
                        QMessageBox::warning(this,"游戏结束","红方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                    }else{
                        QMessageBox::warning(this,"游戏结束","黑方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                    }
                    cout<<"game over!!!"<<endl;
                    gameOver(m_items);
                    return;
                }
                update();
            }else if(isEatStatus){
                if(m_items[4].status==0 ){
                    timer->stop();
                    QMessageBox::warning(this,"游戏结束","黑方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                    gameOver(m_items);
                    return;
                }else if(m_items[20].status==0 ){
                    timer->stop();
                    QMessageBox::warning(this,"游戏结束","红方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                    gameOver(m_items);
                    return;
                }
                if(isMeet(m_items)){
                    timer->stop();
                    if(stepNum%2==0){

                        QMessageBox::warning(this,"游戏结束","红方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                    }else{

                        QMessageBox::warning(this,"游戏结束","黑方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                    }

                    cout<<"game over!!!"<<endl;
                    gameOver(m_items);
                    return;
                }
                gameTime = 45;
                timer->start(1000);
                cout<<"eat"<<endl;
                m_items[selectedQiziIndex].x = stdPos->x();
                m_items[selectedQiziIndex].y = stdPos->y();
                if(m_items[selectedQiziIndex].color==1){
                    if(isKill(1,m_items)){
                        ui->tip2->setText("将军");
                        //cout<<"kill!!!!!!!!!"<<endl;
                    }
                }else if(m_items[selectedQiziIndex].color==0){
                    if(isKill(2,m_items)){
                        ui->tip2->setText("将军");
                        //cout<<"kill!!!!!!!!!"<<endl;
                    }
                }
                isSelectQizi = false;
                isEatStatus = false;
                MainWindow1::isLocation1 = 0;
                ui->tip->setText("");
                stepNum++;
                update();
            }else{
                ui->tip->setText("位置不合法!");
                ui->backStep->setEnabled(false);
                isSelectQizi = false;
                MainWindow1::isLocation1 = 0;
            }

        }
    }
}

void MainWindow1::on_play_clicked()
{
    ui->play->setText("已开始");
    ui->play->setEnabled(false);
    playStatus = true;
}

void MainWindow1::on_backStep_clicked()
{
    ui->backStep->setEnabled(false);
    cout<<"huiqi!!!"<<endl;
    QVector<ITEM> pNullVector;  //局部变量
    m_items.swap(pNullVector);
    m_items = history[0];
    cout<<"dropIndex::"<<dropIndex<<endl;
    if( dropIndex>0 && !m_items[dropIndex].status ){
        cout<<m_items[dropIndex].status<<m_items[dropIndex].name.toStdString()<<endl;
        cout<<m_items[dropIndex].x<<m_items[dropIndex].y<<endl;
        m_items[dropIndex].status = 1;
        m_items[dropIndex].x = dropIndex_X;
        m_items[dropIndex].y = dropIndex_Y;
        cout<<"huo le"<<endl;
    }
    dropIndex = -1;
    gameTime = 45;
    timer->start(1000);
    stepNum--;
    cout<<"dropIndex::"<<dropIndex<<endl;
    update();
}

void MainWindow1::on_rePlay_clicked()
{

    init_items(m_items);
    update();
    gameOver(m_items);
}
