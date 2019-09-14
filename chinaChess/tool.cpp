#include "tool.h"

#include <math.h>

#include <iostream>
using namespace std;

double round(double r)
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

//计算当前鼠标坐标最近的棋盘坐标
QPoint* calcNearestCoor(QPoint& currPos,int baseX,int baseY,int gridWidth,int gridHeight){
    double x = (currPos.x()-baseX)/(double)gridWidth;
    double y = (currPos.y()-baseY)/(double)gridHeight;
    int xx = (int)round(x);
    int yy = (int)round(y);
    //cout<<x<<","<<y<<endl;
    cout<<xx<<","<<yy<<endl;
    QPoint *p = new QPoint(xx,yy);
    return p;
}

bool isCheckMove(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){
    if(((stdPos->x()<0 || stdPos->x()>8) || (stdPos->y()<0 || stdPos->y()>9))){
        return false;
    }
    if(m_items[selectedQiziIndex].name=="che" ||m_items[selectedQiziIndex].name=="pao") {
        return isCheckChe(stdPos,selectedQiziIndex,m_items);
    }else if(m_items[selectedQiziIndex].name=="ma"){
        return isCheckMa(stdPos,selectedQiziIndex,m_items);
    }else if(m_items[selectedQiziIndex].name=="xiang"){
        return isCheckXiang(stdPos,selectedQiziIndex,m_items);
    }else if(m_items[selectedQiziIndex].name=="shi"){
        return isCheckShi(stdPos,selectedQiziIndex,m_items);
    }else if(m_items[selectedQiziIndex].name=="shuai" ||m_items[selectedQiziIndex].name=="jiang"){
        return isCheckShuai(stdPos,selectedQiziIndex,m_items);
    }else if(m_items[selectedQiziIndex].name=="bing"){
        return isCheckBing(stdPos,selectedQiziIndex,m_items);
    }else if(m_items[selectedQiziIndex].name=="zu"){
        return isCheckZu(stdPos,selectedQiziIndex,m_items);
    }
    return true;
}

bool isCheckChe(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){

    if(stdPos->x()-m_items[selectedQiziIndex].x==0 ||stdPos->y()-m_items[selectedQiziIndex].y==0){
        //竖移
        if(stdPos->y()-m_items[selectedQiziIndex].y!=0){
            for (int i=0;i<m_items.length();i++) {
                if(i == selectedQiziIndex){
                    continue;
                }
                if(m_items[i].x==stdPos->x() && ((m_items[i].y<m_items[selectedQiziIndex].y || m_items[i].y>stdPos->y()) && (m_items[i].y>m_items[selectedQiziIndex].y || m_items[i].y<stdPos->y()))){
                    continue;
                }else if(m_items[i].x==stdPos->x()){
                    return false;
                }
            }
        }else if(stdPos->x()-m_items[selectedQiziIndex].x!=0){
            for (int i=0;i<m_items.length();i++) {
                if(i == selectedQiziIndex){
                    continue;
                }
                if(m_items[i].y==stdPos->y() && ((m_items[i].x<m_items[selectedQiziIndex].x || m_items[i].x>stdPos->x()) && (m_items[i].x>m_items[selectedQiziIndex].x || m_items[i].x<stdPos->x()))){
                    continue;
                }else if(m_items[i].y==stdPos->y()){
                    return false;
                }
            }
        }
    }else {
        cout<<"move che error"<<endl;
        return false;
    }
    return true;
}

bool isCheckMa(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){

    int x = m_items[selectedQiziIndex].x;
    int y = m_items[selectedQiziIndex].y;
    if(stdPos->x() ==x-1 && stdPos->y() == y-2){
        for (int i=0;i<m_items.length();i++) {
            if(x==m_items[i].x && y-1==m_items[i].y){
                return false;
            }
        }
        return true;
    }else if(stdPos->x() ==x-1 && stdPos->y() == y+2){
        for (int i=0;i<m_items.length();i++) {
            if(x==m_items[i].x && y+1==m_items[i].y){
                return false;
            }
        }
        return true;
    }else if(stdPos->x() ==x+1 && stdPos->y() == y-2){
        cout<<"me"<<endl;
        for (int i=0;i<m_items.length();i++) {
            if(x==m_items[i].x && y-1==m_items[i].y){
                cout<<"ok"<<endl;
                return false;
            }
        }
        cout<<"onok"<<endl;
        return true;
    }else if(stdPos->x() ==x+1 && stdPos->y() == y+2){
        for (int i=0;i<m_items.length();i++) {
            if(x==m_items[i].x && y+1==m_items[i].y){
                return false;
            }
        }
        return true;
    }else if(stdPos->x() ==x+2 && stdPos->y() == y+1){
        for (int i=0;i<m_items.length();i++) {
            if(x+1==m_items[i].x && y==m_items[i].y){
                return false;
            }
        }
        return true;
    }else if(stdPos->x() ==x-2 && stdPos->y() == y+1){
        for (int i=0;i<m_items.length();i++) {
            if(x-1==m_items[i].x && y==m_items[i].y){
                return false;
            }
        }
        return true;
    }else if(stdPos->x() ==x+2 && stdPos->y() == y-1){
        for (int i=0;i<m_items.length();i++) {
            if(x+1==m_items[i].x && y==m_items[i].y){
                return false;
            }
        }
        return true;
    }else if(stdPos->x() ==x-2 && stdPos->y() == y-1){
        for (int i=0;i<m_items.length();i++) {
            if(x-1==m_items[i].x && y==m_items[i].y){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isCheckXiang(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){

    int x = m_items[selectedQiziIndex].x;
    int y = m_items[selectedQiziIndex].y;
    if(m_items[selectedQiziIndex].color==1){  //红
        if(stdPos->y()>4){
            return false;
        }
    }else if(m_items[selectedQiziIndex].color==0){//黑
        if(stdPos->y()<4){
            return false;
        }
    }
    if(stdPos->x()==x-2 && stdPos->y()==y-2){
        for(int i=0;i<m_items.length();i++){
            if(m_items[i].x==x-1 && m_items[i].y==y-1){
                return false;
            }
        }
        return true;
    }else if(stdPos->x()==x-2 && stdPos->y()==y+2){
        for(int i=0;i<m_items.length();i++){
            if(m_items[i].x==x-1 && m_items[i].y==y+1){
                return false;
            }
        }
        return true;
    }else if(stdPos->x()==x+2 && stdPos->y()==y-2){
        for(int i=0;i<m_items.length();i++){
            if(m_items[i].x==x+1 && m_items[i].y==y-1){
                return false;
            }
        }
        return true;
    }else if(stdPos->x()==x+2 && stdPos->y()==y+2){
        for(int i=0;i<m_items.length();i++){
            if(m_items[i].x==x+1 && m_items[i].y==y+1){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isCheckShi(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){

    int x = m_items[selectedQiziIndex].x;
    int y = m_items[selectedQiziIndex].y;
    if(m_items[selectedQiziIndex].color==1){  //红
        if(stdPos->y()>2 ||stdPos->x()<3||stdPos->x()>5){
            return false;
        }
    }else if(m_items[selectedQiziIndex].color==0){//黑
        if(stdPos->y()<7 ||stdPos->x()<3||stdPos->x()>5){
            return false;
        }
    }
    if(stdPos->x()==x-1 && stdPos->y()==y-1){
        return true;
    }else if(stdPos->x()==x-1 && stdPos->y()==y+1){
        return true;
    }else if(stdPos->x()==x+1 && stdPos->y()==y-1){
        return true;
    }else if(stdPos->x()==x+1 && stdPos->y()==y+1){
        return true;
    }
    return false;
}

bool isCheckShuai(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){

    int x = m_items[selectedQiziIndex].x;
    int y = m_items[selectedQiziIndex].y;

    if(m_items[selectedQiziIndex].color==1){

        if(stdPos->x()<3||stdPos->x()>5||stdPos->y()>2){
            return false;
        }
    }else if(m_items[selectedQiziIndex].color==0){//黑

        if(stdPos->y()<7 ||stdPos->x()<3||stdPos->x()>5){
            return false;
        }
    }
    if(stdPos->x()==x-1 && stdPos->y()==y){
        return true;
    }else if(stdPos->x()==x+1 && stdPos->y()==y){
        return true;
    }else if(stdPos->x()==x && stdPos->y()==y-1){
        return true;
    }else if(stdPos->x()==x && stdPos->y()==y+1){
        return true;
    }
    return false;
}

bool isCheckBing(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){

    int x = m_items[selectedQiziIndex].x;
    int y = m_items[selectedQiziIndex].y;
    if(y<5){
        if(stdPos->x()==x && stdPos->y()==y+1){
                return true;
            }
    }else{
        if(stdPos->x()==x-1 && stdPos->y()==y){
            return true;
        }else if(stdPos->x()==x+1 && stdPos->y()==y){
            return true;
        }else if(stdPos->x()==x && stdPos->y()==y+1){
            return true;
        }
    }
    return false;
}

bool isCheckZu(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items){

    int x = m_items[selectedQiziIndex].x;
    int y = m_items[selectedQiziIndex].y;
    if(y>4){
        if(stdPos->x()==x && stdPos->y()==y-1){
                return true;
            }
    }else{
        if(stdPos->x()==x-1 && stdPos->y()==y){
            return true;
        }else if(stdPos->x()==x+1 && stdPos->y()==y){
            return true;
        }else if(stdPos->x()==x && stdPos->y()==y-1){
            return true;
        }
    }
    return false;
}

bool isEat(int i ,int selectedQiziIndex,QVector<ITEM>& m_items){
    cout<<m_items[i].name.toStdString()<<endl;
    QPoint *stdPos = new QPoint(m_items[i].x,m_items[i].y);
    bool bl = isCheckMove(stdPos,selectedQiziIndex,m_items);
    if(bl){
        m_items[i].status = 0;
        m_items[i].x=-1;
        m_items[i].y=-1;
        return true;
    }
    //m_items[i] 终点坐标
    if(m_items[selectedQiziIndex].name=="che"){
        if(m_items[selectedQiziIndex].y!=m_items[i].y && m_items[selectedQiziIndex].x!=m_items[i].x){
             cout<<"can move1"<<endl;
            return false;
        }
        for (int j=0;j<m_items.length();j++) {

            if(m_items[j].y==m_items[i].y && ((m_items[j].x>m_items[selectedQiziIndex].x && m_items[j].x<m_items[i].x) || (m_items[j].x>m_items[i].x && m_items[j].x<m_items[selectedQiziIndex].x))){
                cout<<"can move2"<<endl;
                return false;
            }
            if(m_items[j].x==m_items[i].x && ((m_items[j].y>m_items[selectedQiziIndex].y && m_items[j].y<m_items[i].y) || (m_items[j].y>m_items[i].y && m_items[j].y<m_items[selectedQiziIndex].y))){
                cout<<"can move"<<endl;
                return false;
            }
        }
            m_items[i].status = 0;
            m_items[i].x=-1;
            m_items[i].y=-1;
            return true;
    }else if(m_items[selectedQiziIndex].name=="pao"){
        int numy=0;
        int numx=0;
        if(m_items[selectedQiziIndex].y!=m_items[i].y && m_items[selectedQiziIndex].x!=m_items[i].x){
             cout<<"can move1"<<endl;
            return false;
        }
        for (int j=0;j<m_items.length();j++) {

            if(m_items[j].y==m_items[i].y && ((m_items[j].x>m_items[selectedQiziIndex].x && m_items[j].x<m_items[i].x) || (m_items[j].x>m_items[i].x && m_items[j].x<m_items[selectedQiziIndex].x))){
                cout<<"can move2"<<endl;
                numy++;

            }
            if(m_items[j].x==m_items[i].x && ((m_items[j].y>m_items[selectedQiziIndex].y && m_items[j].y<m_items[i].y) || (m_items[j].y>m_items[i].y && m_items[j].y<m_items[selectedQiziIndex  ].y))){
                cout<<"can move"<<endl;
                numx++;
            }
        }
        if(numy!=1 && m_items[selectedQiziIndex].y==m_items[i].y){
            return false;
        }
        if(numx!=1 && m_items[selectedQiziIndex].x==m_items[i].x){
            return false;
        }
        m_items[i].status = 0;
        m_items[i].x=-1;
        m_items[i].y=-1;
        return true;
    }
    delete stdPos;
    return false;
}


bool isMeet(QVector<ITEM>& m_items){
    if(m_items[4].x==m_items[20].x){
        for (int i=0;i<m_items.length();i++) {
            if(i==4 || i==20){
                continue;
            }
            if(m_items[i].y>m_items[4].y&&m_items[i].y<m_items[20].y &&m_items[i].x==m_items[4].x){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isKill(int selectedQiziIndex ,QVector<ITEM>& m_items){
    //4 20;
    if(selectedQiziIndex==1){
        for (int i=0;i<16;i++) {
            if(m_items[i].status==1){
                QPoint *stdPos = new QPoint(m_items[20].x,m_items[20].y);
                cout<<"can kill?????"<<endl;
                if(isCheckMove(stdPos,i,m_items)){
                    cout<<"can kill"<<endl;
                    return true;
                }
                if(m_items[i].name=="che"){
                    if(m_items[i].y!=m_items[20].y && m_items[i].x!=m_items[20].x){

                         continue;
                    }
                    for (int j=0;j<m_items.length();j++) {

                        if(m_items[j].y==m_items[20].y && ((m_items[j].x>m_items[i].x && m_items[j].x<m_items[20].x) || (m_items[j].x>m_items[20].x && m_items[j].x<m_items[i].x))){

                            continue;
                        }
                        if(m_items[j].x==m_items[20].x && ((m_items[j].y>m_items[i].y && m_items[j].y<m_items[20].y) || (m_items[j].y>m_items[20].y && m_items[j].y<m_items[i].y))){

                            continue;
                        }
                    }
                    return true;
                }else if(m_items[i].name=="pao"){
                    int numy=0;
                    int numx=0;
                    if(m_items[i].y!=m_items[20].y && m_items[i].x!=m_items[20].x){

                        continue;
                    }
                    for (int j=0;j<m_items.length();j++) {
                        if(m_items[j].y==m_items[20].y && ((m_items[j].x>m_items[i].x && m_items[j].x<m_items[20].x) || (m_items[j].x>m_items[20].x && m_items[j].x<m_items[i].x))){
                            numy++;
                        }
                        if(m_items[j].x==m_items[20].x && ((m_items[j].y>m_items[i].y && m_items[j].y<m_items[20].y) || (m_items[j].y>m_items[20].y && m_items[j].y<m_items[i].y))){
                            numx++;
                        }
                    }
                    if(numy!=1 && m_items[i].y==m_items[20].y){
                        continue;
                    }
                    if(numx!=1 && m_items[i].x==m_items[20].x){
                        continue;
                    }
                    return true;
                }
            }
        }
    }else if(selectedQiziIndex==2){
        for (int i=16;i<m_items.length();i++) {
            if(m_items[i].status==1){
                QPoint *stdPos = new QPoint(m_items[4].x,m_items[4].y);
                if(isCheckMove(stdPos,i,m_items)){
                    return true;
                }
                if(m_items[i].name=="che"){
                    if(m_items[i].y!=m_items[4].y && m_items[i].x!=m_items[4].x){

                        continue;
                    }
                    for (int j=0;j<m_items.length();j++) {

                        if(m_items[j].y==m_items[4].y && ((m_items[j].x>m_items[i].x && m_items[j].x<m_items[4].x) || (m_items[j].x>m_items[4].x && m_items[j].x<m_items[i].x))){

                            continue;
                        }
                        if(m_items[j].x==m_items[4].x && ((m_items[j].y>m_items[i].y && m_items[j].y<m_items[4].y) || (m_items[j].y>m_items[4].y && m_items[j].y<m_items[i].y))){

                            continue;
                        }
                    }
                    return true;
                }else if(m_items[i].name=="pao"){
                    int numy=0;
                    int numx=0;
                    if(m_items[i].y!=m_items[4].y && m_items[i].x!=m_items[4].x){

                        continue;
                    }
                    for (int j=0;j<m_items.length();j++) {

                        if(m_items[j].y==m_items[4].y && ((m_items[j].x>m_items[i].x && m_items[j].x<m_items[4].x) || (m_items[j].x>m_items[4].x && m_items[j].x<m_items[i].x))){

                            numy++;
                        }
                        if(m_items[j].x==m_items[4].x && ((m_items[j].y>m_items[i].y && m_items[j].y<m_items[4].y) || (m_items[j].y>m_items[4].y && m_items[j].y<m_items[i].y))){

                            numx++;
                        }
                    }
                    if(numy!=1 && m_items[i].y==m_items[4].y){
                        continue;
                    }
                    if(numx!=1 && m_items[i].x==m_items[4].x){
                        continue;
                    }
                    return true;
                }

            }
        }
    }
    return false;
}
