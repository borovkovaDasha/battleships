#ifndef TWOPALUBS_H
#define TWOPALUBS_H
#include <QLabel>

class QDragEnterEvent;
class QDropEvent;
class twoPalubs :public QLabel
{
public:
    twoPalubs(QWidget *parent=0);
     void dragMoveEvent(QDragMoveEvent *event);
     void mousePressEvent(QMouseEvent *event);
    QLabel *pix;

};

#endif // DRAGITEMS_H
