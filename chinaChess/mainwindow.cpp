#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QPaintEvent>
#include <iostream>
#include "item.h"
#include "tool.h"
#include "modechange.h"
using namespace std;


int MainWindow::isLocation = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setMinimumSize(1280,720);
    this->setMaximumSize(1280,720);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myTimer()));
    init_items(m_items);
    ui->backStep->setEnabled(false);
    ui->peace->setEnabled(false);
    ui->changeColor->setEnabled(false);
    ui->changeColor->hide();
}

MainWindow::~MainWindow()
{

    ModeChange::myFree();
    delete timer;
    delete p;
    delete ui;
}

void MainWindow::myTimer(){
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

void MainWindow::mySlots_recvUsername(QString name){

    ui->userName->setText("欢迎"+name+"登入");
}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);//屏蔽未使用变量提示
    p = new QPainter(this);//将指针传入新创建的画板
    drawQiPan();
    drawChessItems();
    p->end();
    delete p;
    p = nullptr;
   // cout<<"paintEvent invoke..."<<endl;
}

void MainWindow::drawQiPan(){
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

void MainWindow::drawChessItems(){

    for(int i=0;i<m_items.length();i++){
        if(m_items[i].status==1){
            QPixmap pixmap(m_items[i].path);
            QSize size(60,60);
            pixmap = pixmap.scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            p->drawPixmap(baseX-30+m_items[i].x*gridWidth,baseY-30+m_items[i].y*gridHeight,pixmap);
        }

    }

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){
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
                        if( user ==1 && m_items[i].color==1 &&stepNum%2==0){
                            isSelectQizi = true;
                            ui->tip->setText("你选中了"+m_items[selectedQiziIndex].name2);
                            timer->start(1000);
                        }else if(user == 2 && m_items[i].color==0 &&stepNum%2==1){
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
            //stdPos = nullptr;
        }else{
            cout<<"move"<<endl;
            for (int i=0;i<m_items.length();i++) {
                if(m_items[i].x == stdPos->x() && m_items[i].y == stdPos->y()){
                    cout<<i<<endl;
                    dropIndex = i;
                    dropIndex_X = m_items[i].x;
                    dropIndex_Y = m_items[i].y;
                    if(m_items[selectedQiziIndex].color == m_items[i].color){
                        MainWindow::isLocation = 1;
                        cout<<"lllll:"<<MainWindow::isLocation<<endl;
                        isSelectQizi = false;
                        break;
                    }else{
                        isEatStatus = isEat(i,selectedQiziIndex,m_items);
                        isSelectQizi = false;
                        break;
                    }
                }
            }
            cout<<"move1"<<endl;
            bool chessMove = isCheckMove(stdPos,selectedQiziIndex,m_items);
            if(!history.empty()){
                history.pop_back();
            }
            history.push_back(m_items);
            ui->backStep->setEnabled(true);
            ui->peace->setEnabled(false);
            ui->changeColor->setEnabled(false);
            ui->tip2->setText("");
            char *ch = (QString::number(stdPos->x())+":"+QString::number(stdPos->y())+":"+QString::number(selectedQiziIndex)).toUtf8().data();
            if(chessMove && !MainWindow::isLocation && !isEatStatus){

                if(m_items[selectedQiziIndex].color==1){
                    ModeChange::playChess(ch);
                }else if(m_items[selectedQiziIndex].color==0){
                    ModeChange::playChess_b(ch);
                }
                gameTime = 45;
                timer->start(1000);
                m_items[selectedQiziIndex].x = stdPos->x();
                m_items[selectedQiziIndex].y = stdPos->y();
                if(isKill(user,m_items)){
                    //ui->tip2->setText("将军");
                    if(user==1 ){
                         ModeChange::chat("killY");
                    }else if(user==2){
                         ModeChange::chat_b("killY");
                    }
                    cout<<"kill!!!!!!!!!"<<endl;
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

                if(m_items[selectedQiziIndex].color==1){
                    ModeChange::playChess(ch);
                }else if(m_items[selectedQiziIndex].color==0){
                    ModeChange::playChess_b(ch);
                }
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
                if(isKill(user,m_items)){
                    //ui->tip2->setText("将军");
                    if(user==1 ){
                         ModeChange::chat("killY");
                    }else if(user==2){
                         ModeChange::chat_b("killY");
                    }
                    cout<<"kill!!!!!!!!!"<<endl;
                }
                isSelectQizi = false;
                isEatStatus = false;
                MainWindow::isLocation = 0;
                ui->tip->setText("");
                stepNum++;
                update();
            }else{
                ui->tip->setText("位置不合法!");
                ui->backStep->setEnabled(false);
                isSelectQizi = false;
                MainWindow::isLocation = 0;
            }

        }
    }
}

void MainWindow::gameOver(QVector<ITEM> &m_items){
   ui->peace->setEnabled(false);
   readyStatus = 0;
   playStatus = false;
   ui->ready->setText("准备");
   ui->ready->setEnabled(true);
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

void MainWindow::on_backStep_clicked()
{
    ui->backStep->setEnabled(false);
    timer->stop();
    if(m_items[selectedQiziIndex].color==1){
         ModeChange::playChess("backstep");
    }else if(m_items[selectedQiziIndex].color==0){
         ModeChange::playChess_b("backstep");
    }

}

void MainWindow::dropChess(QString str){
    if(str=="quit"){
        QMessageBox::warning(this,"对面跑了","你赢了！",QMessageBox::Ok,QMessageBox::NoButton);
        qApp->quit();
        return;
    }else if(str=="restart"){
        readyStatus ++;
        if( ui->ready->text()=="已准备" ){
            if(user==1){
                if(readyStatus!=2){
                    ModeChange::playChess("restart");
                }
            }else if(user==2){
                if(readyStatus!=2){
                    ModeChange::playChess_b("restart");
                }
            }
            timer->start(1000);
            QMessageBox::warning(this,"提示","游戏开始！",QMessageBox::Ok,QMessageBox::NoButton);

            playStatus = true;
            ui->ready->setText("已开始");
            //ui->peace->setEnabled(true);
            ui->changeColor->setEnabled(false);
        }
    }else{
        if(str==""){
            return ;
        }
        bool bb = msgFun(str);
        if(bb){
            ui->backStep->setEnabled(false);
            ui->peace->setEnabled(true);
            if(!history.empty()){
                history.pop_back();
            }
            history.push_back(m_items);
            cout<<"hahha"<<str.toStdString()<<endl;
            QStringList list = str.split(":");
            for (int i=0;i<m_items.length();i++) {
                if(list[0].toInt()==m_items[i].x && list[1].toInt() == m_items[i].y){
                    if(i==list[2].toInt()){
                        continue;
                    }else {
                        isEat(i,list[2].toInt(),m_items);
                    }
                }
            }
            m_items[list[2].toInt()].x = list[0].toInt();
            m_items[list[2].toInt()].y = list[1].toInt();
            if(m_items[4].status==0 ){
                QMessageBox::warning(this,"游戏结束","黑方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                gameOver(m_items);
                return;
            }else if(m_items[20].status==0 ){
                QMessageBox::warning(this,"游戏结束","红方获胜",QMessageBox::Ok,QMessageBox::NoButton);
                gameOver(m_items);
                return;
            }
            if(isMeet(m_items)){
                if(stepNum%2==1){
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
            stepNum++;
            update();
        }
    }
}

void MainWindow::displayP(int a){
    if(a==1){
        ui->userName->setText("你是红方！你先下！");
    }else if (a==2) {
        ui->userName->setText("你是黑方！你后下！");
    }
}

void MainWindow::isBackStep(){
    timer->stop();
    if(QMessageBox::Yes == QMessageBox::question(this,QStringLiteral("对方悔棋"),QStringLiteral("是否同意?"),QMessageBox::Yes | QMessageBox:: No))
    {
        if(stepNum%2==0){
             ModeChange::playChess("yes");
        }else if(stepNum%2==1){
             ModeChange::playChess_b("yes");
        }
        backStepOk();
    }
    else
    {
        if(stepNum%2==0){
             ModeChange::playChess("no");
        }else if(stepNum%2==1){
             ModeChange::playChess_b("no");
        }
        ui->messageBuffer->append("系统:你拒绝了悔棋");
    }
    timer->start();
}

void MainWindow::backStepOk(){
    ui->messageBuffer->append("系统:悔棋成功");
    timer->start();
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

void MainWindow::backStepNo(){
    timer->start();
    //QMessageBox::warning(this,"提示","对方拒绝了你的悔棋",QMessageBox::Ok,QMessageBox::NoButton);
    ui->messageBuffer->append("系统:对方拒绝了你的悔棋");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作
    cout<<"nomal quit"<<endl;
    if(user==1){
         ModeChange::playChess("quit");
    }else if(user==2){
         ModeChange::playChess_b("quit");
    }
}

void MainWindow::on_ready_clicked()
{
    ui->ready->setEnabled(false);
    ui->ready->setText("已准备");
    if(user==1){
         ModeChange::playChess("restart");
    }else if(user==2){
         ModeChange::playChess_b("restart");
    }
    //readyStatus = 2;
}

void MainWindow::on_sendMsg_clicked()
{
    if(user==1){
         ModeChange::chat("chat:对面:"+ui->lineEdit->text());
    }else if(user==2){
         ModeChange::chat_b("chat:对面:"+ui->lineEdit->text());
    }
    ui->messageBuffer->append("你:"+ui->lineEdit->text());
    ui->lineEdit->setText("");
}

bool MainWindow::msgFun(QString str){
    cout<<"msgFUN!!!"<<endl;
    QString list = str.mid(0,5);
    if(list=="chat:"){
        QString msg = str.mid(5);
        cout<<":::"<<msg.toStdString()<<endl;
        ui->messageBuffer->append(msg);
        return false;
    }else if(list == "peace"){
        isPeace();
        return false;
    }else if(list =="yes_p"){
        isPeaceOk();
        return false;
    }else if(list =="no_pe"){
        isPeaceNo();
        return false;
    }else if(list =="chage"){
        isChangeColor();
        return false;
    }else if(list =="yes_c"){
        isChangeCOk();
        return false;
    }else if(list =="no_cc"){
        isChangeCNo();
        return false;
    }else if(list =="killY"){
        ui->tip2->setText("将军！");
        return false;
    }
    return true;
}

void MainWindow::on_peace_clicked()
{
    ui->backStep->setEnabled(false);
    timer->stop();
    if(user==1 ){
         ModeChange::chat("peace");
    }else if(user==2){
         ModeChange::chat_b("peace");
    }
    ui->peace->setEnabled(false);
}

void MainWindow::isPeace(){
    timer->stop();
    if(QMessageBox::Yes == QMessageBox::question(this,QStringLiteral("对方求和"),QStringLiteral("是否同意?"),QMessageBox::Yes | QMessageBox:: No))
    {
        if(user==1){
             ModeChange::playChess("yes_p");
        }else if(user==2){
             ModeChange::playChess_b("yes_p");
        }
        isPeaceOk();
        //ui->peace->setEnabled(true);
    }
    else
    {
        if(user==1){
             ModeChange::playChess("no_pe");
        }else if(user==2){
             ModeChange::playChess_b("no_pe");
        }
        ui->messageBuffer->append("系统:你拒绝了求和");
        timer->start();
    }
    //ui->backStep->setEnabled(true);
   // timer->start();

}

void MainWindow::isPeaceOk(){

     gameOver(m_items);
     gameTime = 45;
     ui->messageBuffer->append("系统:重新开始");
     update();
     // timer->start();
}

void MainWindow::isPeaceNo(){
    timer->start();

    //QMessageBox::warning(this,"提示","对方拒绝了你的和棋",QMessageBox::Ok,QMessageBox::NoButton);
    ui->messageBuffer->append("系统:对方拒绝了你的求和");
}

void MainWindow::on_changeColor_clicked()
{
    ui->changeColor->setEnabled(false);
    ui->backStep->setEnabled(false);
    if(user==1 ){
         ModeChange::chat("chage");
    }else if(user==2){
         ModeChange::chat_b("chage");
    }
    ui->peace->setEnabled(false);
}

void MainWindow::isChangeColor(){
    if(QMessageBox::Yes == QMessageBox::question(this,QStringLiteral("对方想换边"),QStringLiteral("是否同意?"),QMessageBox::Yes | QMessageBox:: No))
    {
        if(user==1){
             ModeChange::playChess("yes_c");
        }else if(user==2){
             ModeChange::playChess_b("yes_c");
        }
        isChangeCOk();
    }
    else
    {
        if(user==1){
             ModeChange::playChess("no_cc");
        }else if(user==2){
             ModeChange::playChess_b("no_cc");
        }
        ui->messageBuffer->append("系统:你拒绝了换边");
    }
}

void MainWindow::isChangeCOk(){
     ui->messageBuffer->append("系统:换边成功");
     if(user==1){
         user=2;
     }else if(user ==2){
         user =1;
     }
     displayP(user);
}

void MainWindow::isChangeCNo(){

    ui->messageBuffer->append("系统:对方拒绝了你的换边");
}
