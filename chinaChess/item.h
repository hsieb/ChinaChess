#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <QString>
#include <QVector>
using namespace std;

typedef struct item{
    int x;
    int y;
    QString name;
    QString name2;
    int value;
    QString path;
    int color;
    int status;

}ITEM;

extern void init_items(QVector<ITEM>&);


#endif // ITEM_H
