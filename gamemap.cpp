#include "gamemap.h"
#include <QDebug>
#include <QMouseEvent>
#include <QtGui>

    GameMap::GameMap (QWidget* parent ) :
        QWidget (parent){

        QRect r(0,0,100,100);
        layout = new QGridLayout (this);
        layout->setOriginCorner(Qt::TopLeftCorner);
        layout->setSpacing(0);
        setAcceptDrops(true);
        fourCount=1;
        threeCount=2;
        twoCount=3;
        oneCount=4;
        for (int column = 0; column < Columns; column++) {
            for (int row = 0; row < Rows; row++) {
                 GameCell* cell = new GameCell (this);
                 cells[row][column] = cell;
                 layout->addWidget(cell, row, column);
             }
        }
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
        ships[i][j]=0;
             }
         }

    }


GameMap::~GameMap(){

}



void GameMap::dropEvent(QDropEvent *event){
if(event->mimeData()->hasFormat("application/x-4sV")){
    if (fourCount!=0){
        cordx = event->pos().x();
        cordy=event->pos().y();
        int y=recoordX();
        int x=recoordY();
        if (x<=6){
            for (int j=0; j<4; j++){
                if (ships[x+j+1][y+1]!=0){
                    qDebug() << "wrong!!!1";
                    return;
                 }
        }
             for (int i=0;i<4;i++){
                cells[x+i][y]->currentState=GameCell::Ship;
                cells[x+i][y]->syncBitmap();
                ships[x+i+1][y+1]=4;
              }


              ships[x][y+2]=ships[x+1][y+2]=ships[x+2][y+2]=ships[x+3][y+2]=ships[x+4][y+2]=
              ships[x+5][y+2]=ships[x][y+1]=
              ships[x+5][y+1]=ships[x][y]=ships[x+1][y]=ships[x+2][y]=ships[x+3][y]=ships[x+4][y]=ships[x+5][y]=-1;
              fourCount--;
       }
   else qDebug() << "wrong position";
    }
else qDebug()<< "u cant place 4 palubs ship here";
}

if (event->mimeData()->hasFormat("application/x-4sH")){
    if (fourCount!=0){
            cordx = event->pos().x();
            cordy=event->pos().y();
            int y=recoordX();
            int x=recoordY();
                if (y<=6){
                    for (int j=0; j<4; j++){
                        if (ships[x+1][y+1+j]!=0){
                            qDebug() << "wrong!!!1";
                            return;
                         }
                     }
                  for (int i=0;i<4;i++){
                  cells[x][y+i]->currentState=GameCell::Ship;
                  cells[x][y+i]->syncBitmap();
                  ships[x+1][y+1+i]=4;
                   }
                               ships[x][y]=ships[x][y+1]=ships[x][y+2]=ships[x][y+3]=ships[x][y+4]=ships[x][y+5]=
                               ships[x+1][y]=ships[x+1][y+5]=
                               ships[x+2][y]=ships[x+2][y+1]=ships[x+2][y+2]=ships[x+2][y+3]=ships[x+2][y+4]=ships[x+2][y+5]=-1;
                                    fourCount--;
                }
    }
    else qDebug() << "u cant place 4 palubs ship here";

}
  if(event->mimeData()->hasFormat("application/x-3sH")){
      if (threeCount!=0){
        cordx = event->pos().x();
        cordy=event->pos().y();
        int y=recoordX();
        int x=recoordY();
            if (y<=7){
                for (int j=0; j<3; j++){
                    if (ships[x+1][y+1+j]!=0){
                         qDebug() << "wrong!!!1";
                         return;
                     }
                    }
             for (int i=0;i<3;i++){
                 cells[x][y+i]->currentState=GameCell::Ship;
                 cells[x][y+i]->syncBitmap();
                    ships[x+1][y+i+1]=3;
             }

             ships[x][y]=ships[x][y+1]=ships[x][y+2]=ships[x][y+3]=ships[x][y+4]=
             ships[x+1][y]=ships[x+1][y+4]=
             ships[x+2][y]=ships[x+2][y+1]=ships[x+2][y+2]=ships[x+2][y+3]=ships[x+2][y+4]=-1;
              threeCount--;
            }
      }
  }
  if (event->mimeData()->hasFormat("application/x-3sV")){
      if (threeCount!=0){
      cordx = event->pos().x();
      cordy=event->pos().y();
      int y=recoordX();
      int x=recoordY();
             if (x<=7){
                for (int j=0; j<3; j++){
                     if (ships[x+1+j][y+1]!=0){
                        qDebug() << "wrong!!!1";
                        return;
                      }
                 }
             for (int i=0;i<3;i++){
                  cells[x+i][y]->currentState=GameCell::Ship;
                  cells[x+i][y]->syncBitmap();
                  ships[x+1+i][y+1]=3;
              }

             ships[x][y+2]=ships[x+1][y+2]=ships[x+2][y+2]=ships[x+3][y+2]=ships[x+4][y+2]=
             ships[x][y+1]=ships[x+4][y+1]=
             ships[x][y]=ships[x+1][y]=ships[x+2][y]=ships[x+3][y]=ships[x+4][y]=-1;
              threeCount--;
            }
      }
  }
  if(event->mimeData()->hasFormat("application/x-2sH")){
      if (twoCount!=0){
        cordx = event->pos().x();
        cordy=event->pos().y();
        int y=recoordX();
        int x=recoordY();
        if (y<=8){
                 for (int j=0; j<2; j++){
                    if (ships[x+1][y+1+j]!=0){
                    qDebug() << "wrong!!!1";
                    return;
                    }
                  }
        for (int i=0;i<2;i++){
             cells[x][y+i]->currentState=GameCell::Ship;
             cells[x][y+i]->syncBitmap();
             ships[x+1][y+i+1]=2;
        }
        ships[x][y]=ships[x][y+1]=ships[x][y+2]=ships[x][y+3]=
        ships[x+1][y]=ships[x+1][y+3]=
        ships[x+2][y]=ships[x+2][y+1]=ships[x+2][y+2]=ships[x+2][y+3]=-1;
        twoCount--;
        }
      }
  }
  if (event->mimeData()->hasFormat("application/x-2sV")){
      if (twoCount!=0){
         cordx = event->pos().x();
         cordy=event->pos().y();
         int y=recoordX();
         int x=recoordY();
         if (x<=8){
             for (int j=0; j<2; j++){
                if (ships[x+1+j][y+1]!=0){
                    qDebug() << "wrong!!!1";
                    return;
                }
              }
        for (int i=0;i<2;i++){
        cells[x+i][y]->currentState=GameCell::Ship;
        cells[x+i][y]->syncBitmap();
         ships[x+1+i][y+1]=2;
         }
        ships[x][y+2]=ships[x+1][y+2]=ships[x+2][y+2]=ships[x+3][y+2]=
        ships[x][y+1]=ships[x+3][y+1]=
        ships[x][y]=ships[x+1][y]=ships[x+2][y]=ships[x+3][y]=-1;
        twoCount--;
         }
      }
  }
  if (event->mimeData()->hasFormat("application/x-1s")){
      if (oneCount!=0){
            cordx = event->pos().x();
            cordy=event->pos().y();
            int y=recoordX();
            int x=recoordY();
            if(ships[x+1][y+1]!=0){
                qDebug() << "u cant place ship here";
                return;
            }
            cells[x][y]->currentState=GameCell::Ship;
            cells[x][y]->syncBitmap();
            ships[x+1][y+1]=1;
            ships[x][y]=ships[x+1][y]=ships[x+2][y]=
            ships[x][y+1]=ships[x+2][y+1]=
            ships[x][y+2]=ships[x+1][y+2]=ships[x+2][y+2]=-1;
             oneCount--;
      }\
 else qDebug() << "Wrong!";
 }
}
void GameMap::dragEnterEvent(QDragEnterEvent *event){
    if (((event->mimeData()->hasFormat("application/x-4sH"))||
         (event->mimeData()->hasFormat("application/x-4sV")) ||
         (event->mimeData()->hasFormat("application/x-3sV")) ||
         (event->mimeData()->hasFormat("application/x-3sH")) ||
         (event->mimeData()->hasFormat("application/x-2sV"))
         || (event->mimeData()->hasFormat("application/x-2sH"))
|| (event->mimeData()->hasFormat("application/x-1s")))) {
             if (event->source() == this) {
                 event->setDropAction(Qt::MoveAction);
                 event->accept();
              }
             else {
                 event->acceptProposedAction();
              }
    }
    else {
        event->ignore();
    }

}

int GameMap::recoordX() {
    int testx;
    testx=cordx/40;
    for (int i=0; i<10;i++){
        if (testx==i){
           Realx=testx;
        }
     }
    return Realx;
}
int GameMap::recoordY(){
    int testy;
    testy=cordy/40;
    for (int i=0; i<10;i++){
            if (testy==i){
              Realy=testy;
            }
     }
    return Realy;
}
