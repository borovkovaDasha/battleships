#ifndef THREEPALUBS_H
#define THREEPALUBS_H
#include <QLabel>

class QDragEnterEvent;
class QDropEvent;
class threePalubs :public QLabel
{
public:
    threePalubs(QWidget *parent=0);
   void dragMoveEvent(QDragMoveEvent *event);
   void mousePressEvent(QMouseEvent *event);
    QLabel *pix;
};

#endif // DRAGITEMS_H
