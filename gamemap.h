#pragma once
#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <QPoint>
#include "gamecell.h"
#include <QHBoxLayout>
#include <QWidget>
/* here we create a field of GameCell objects*/
class QDragEnterEvent;
class QDropEvent;
class GameCell;


class GameMap : public QWidget {
    Q_OBJECT

public:

    static const int Rows = 10;
    static const int Columns = 10;
    GameMap (QWidget* parent = 0);
    int cordx;
    int cordy;
    bool isVertical;
     GameCell * cells[Columns][Rows];
     int ships[12][12];

    ~GameMap();
void dropEvent(QDropEvent *event);
void dragEnterEvent(QDragEnterEvent *event);
int recoordX();
int recoordY();
int Realx;
int Realy;

int fourCount, threeCount, twoCount, oneCount;
private:

    QGridLayout* layout;

};
#endif
