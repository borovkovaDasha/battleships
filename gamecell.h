#pragma once
#ifndef GAMECELL_H
#define GAMECELL_H
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDebug>
//#include "client.h"

/*here we create one cell of the field and make method to change states*/
class GameCell : public QLabel
{
    Q_OBJECT

public:
    enum State { Undiscovered, Hit, Miss,Ship }; //sostoyania yacheiki
    State currentState;
   QPixmap pix;
    GameCell (QWidget *parent = 0);
    ~GameCell();
    int xc;
    int yc;
    int realx;
    int realy;
    int recoordX();
    int recoordY();
    bool acceptClicks;
    bool isEnemy;
    //Client *client;

    void syncBitmap() {

        switch (currentState) {
        case Undiscovered: setPixmap(QPixmap("images/undiscovered.png")); break;
        case Hit: setPixmap(QPixmap("images/hitship.png")); break;
        case Miss: setPixmap(QPixmap("images/missed.png")); break;
        case Ship: setPixmap(QPixmap("images/ship1p.png")); break;

        }
    }

    void mousePressEvent(QMouseEvent *ev);
    void coordinates();


};
#endif
