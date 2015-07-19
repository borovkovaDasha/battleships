#include "gamecell.h"
#include <QDebug>
#include <QtGui>
#include "client.h"
extern Client *client;

GameCell::GameCell (QWidget *parent) : QLabel (parent),
        currentState (Undiscovered) {
        setAcceptDrops(true);
        isEnemy=false;
        acceptClicks=false;
        syncBitmap();
}
GameCell::~GameCell(){

}

void GameCell::mousePressEvent(QMouseEvent *ev){

      if(acceptClicks==true){
            if (isEnemy==false){
                        xc=this->x();
                        qDebug() << xc;
                        yc=this->y();
                        int coordx=recoordY();
                        int coordy=recoordX();


             }
            if (isEnemy==true){
              //this->currentState=Hit;

              syncBitmap();
              xc=this->x();
              yc=this->y();
              int coordx=recoordY();
              int coordy=recoordX();
              qDebug() << coordx <<coordy;
              QString answer = "coordinats " + QString::number(coordx,10) + " " + QString::number(coordy,10);
              client->slotSendToServer(answer);
            }
       }

}

int GameCell::recoordX(){

    int testx;
    testx=xc/10;
    for (int i=0; i<37;i+=4){
            if (testx==i){
                realx=i/4;
            }
    }
return realx;
}

int GameCell::recoordY(){
    int testy;
    testy=yc/10;
    for (int i=0; i<37;i+=4){
            if (testy==i){
                realy=i/4;
    }
}
return realy;
}


