#ifndef TOOL_H
#define TOOL_H
#include <QPoint>
#include <QVector>
#include "item.h"
extern QPoint* calcNearestCoor(QPoint& currPos,int baseX,int baseY,int gridWidth,int gridHeight);

extern bool isCheckMove(QPoint *stdPos,int selectedQiziIndex,QVector<ITEM>&);
extern bool isEat(int i,int selectedQiziIndex ,QVector<ITEM>& m_items);
extern bool isMeet(QVector<ITEM>& m_items);
extern bool isKill(int selectedQiziIndex,QVector<ITEM>&);


bool isCheckChe(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items);
bool isCheckMa(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items);
bool isCheckXiang(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items);
bool isCheckShi(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items);
bool isCheckShuai(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items);
bool isCheckBing(QPoint *stdPos,int selectedQiziIndex ,QVector<ITEM>& m_items);
bool isCheckZu(QPoint *stdPos,int i ,QVector<ITEM>& m_items);



#endif // TOOL_H
