#ifndef ONEPALUB_H
#define ONEPALUB_H

#include <QLabel>

class QDragEnterEvent;
class QDropEvent;
class OnePalub :public QLabel
{
public:
    OnePalub(QWidget *parent=0);
   void dragMoveEvent(QDragMoveEvent *event);
   void mousePressEvent(QMouseEvent *event);
    QLabel *pix;
};

#endif // ONEPALUB_H
