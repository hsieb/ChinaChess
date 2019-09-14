#include "item.h"
#include "mainwindow.h"
/*
int x;
int y;
QString name;
int value;
QString path;
int color; 1 红 0黑
int status;1 存活 0死
*/
void init_items(QVector<ITEM> &m_items){
    //红.....
    ITEM itm1 ={0,0,"che","车",10,":/imgs/imgs/ju_r.png",1,1};
    m_items.push_back(itm1);
    ITEM itm2 ={1,0,"ma","马",8,":/imgs/imgs/ma_r.png",1,1};
    m_items.push_back(itm2);
    ITEM itm3 ={2,0,"xiang","相",6,":/imgs/imgs/xiang_r.png",1,1};
    m_items.push_back(itm3);
    ITEM itm4 ={3,0,"shi","士",6,":/imgs/imgs/shi_r.png",1,1};
    m_items.push_back(itm4);
    ITEM itm5 ={4,0,"shuai","帅",99,":/imgs/imgs/shui_r.png",1,1};
    m_items.push_back(itm5);
    ITEM itm9 ={8,0,"che","车",10,":/imgs/imgs/ju_r.png",1,1};
    m_items.push_back(itm9);
    ITEM itm8 ={7,0,"ma","马",8,":/imgs/imgs/ma_r.png",1,1};
    m_items.push_back(itm8);
    ITEM itm7 ={6,0,"xiang","相",6,":/imgs/imgs/xiang_r.png",1,1};
    m_items.push_back(itm7);
    ITEM itm6 ={5,0,"shi","士",6,":/imgs/imgs/shi_r.png",1,1};
    m_items.push_back(itm6);

    ITEM itm10 ={1,2,"pao","炮",8,":/imgs/imgs/pao_r.png",1,1};
    m_items.push_back(itm10);
    ITEM itm11 ={7,2,"pao","炮",8,":/imgs/imgs/pao_r.png",1,1};
    m_items.push_back(itm11);

    for(int i=0;i<5;i++){
        ITEM itm12 ={2*i,3,"bing","兵",1,":/imgs/imgs/bing_r.png",1,1};
        m_items.push_back(itm12);
    }
    //黑....
    ITEM itm1_b ={0,9,"che","車",10,":/imgs/imgs/ju_b.png",0,1};
    m_items.push_back(itm1_b);
    ITEM itm2_b ={1,9,"ma","馬",8,":/imgs/imgs/ma_b.png",0,1};
    m_items.push_back(itm2_b);
    ITEM itm3_b ={2,9,"xiang","象",6,":/imgs/imgs/xiang_b.png",0,1};
    m_items.push_back(itm3_b);
    ITEM itm4_b ={3,9,"shi","仕",6,":/imgs/imgs/shi_b.png",0,1};
    m_items.push_back(itm4_b);
    ITEM itm5_b ={4,9,"jiang","将",99,":/imgs/imgs/jiang_b.png",0,1};
    m_items.push_back(itm5_b);
    ITEM itm9_b ={8,9,"che","車",10,":/imgs/imgs/ju_b.png",0,1};
    m_items.push_back(itm9_b);
    ITEM itm8_b ={7,9,"ma","馬",8,":/imgs/imgs/ma_b.png",0,1};
    m_items.push_back(itm8_b);
    ITEM itm7_b ={6,9,"xiang","象",6,":/imgs/imgs/xiang_b.png",0,1};
    m_items.push_back(itm7_b);
    ITEM itm6_b ={5,9,"shi","仕",6,":/imgs/imgs/shi_b.png",0,1};
    m_items.push_back(itm6_b);

    ITEM itm10_b ={1,7,"pao","炮",8,":/imgs/imgs/pao_b.png",0,1};
    m_items.push_back(itm10_b);
    ITEM itm11_b ={7,7,"pao","炮",8,":/imgs/imgs/pao_b.png",0,1};
    m_items.push_back(itm11_b);

    for(int i=0;i<5;i++){
        ITEM itm12_b ={2*i,6,"zu","卒",1,":/imgs/imgs/zu_b.png",0,1};
        m_items.push_back(itm12_b);
    }
}
