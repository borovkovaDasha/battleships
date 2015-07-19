#include "threepalubs.h"
#include <QtGui>
threePalubs::threePalubs(QWidget *parent)
     : QLabel(parent){
      pix = new QLabel(this);
      pix->setPixmap(QPixmap("images/ship3p.png"));
      pix->move(10,10);
      pix->show();
      setFixedSize(200,60);

}

void threePalubs::mousePressEvent(QMouseEvent *event){

    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;
    QString isVertical;
    if (event->button()==Qt::RightButton) {
        isVertical="application/x-3sV";
        QPixmap verticalpix= QPixmap("images/ship3pvert.png");
        QPixmap pixmap = *child->pixmap();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << QPoint(event->pos() - child->pos());
        QMimeData *mimeData = new QMimeData;
        mimeData->setData(isVertical, itemData);
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(verticalpix);
        drag->setHotSpot(event->pos() - child->pos());

            if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction){
                child->close();

            }
            else {
                child->show();
                child->setPixmap(pixmap);
            }
    }

    else if (event->button()==Qt::LeftButton){
            isVertical="application/x-3sH";
            QPixmap verticalpix= *child->pixmap();
            QPixmap pixmap = *child->pixmap();
            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << pixmap << QPoint(event->pos() - child->pos());

            QMimeData *mimeData = new QMimeData;
            mimeData->setData(isVertical, itemData);
            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setPixmap(verticalpix);
            drag->setHotSpot(event->pos() - child->pos());


             if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction){
                 child->close();

              }
             else {
                child->show();
                child->setPixmap(pixmap);

               }
  //qDebug() << CountNumberOfShips;
    }
}


void threePalubs::dragMoveEvent(QDragMoveEvent *event){

    if (event->mimeData()->hasFormat("image/png")) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
    }
    else
             event->ignore();

}
