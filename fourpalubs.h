#ifndef FOURPALUBS_H
#define FOURPALUBS_H
#include <QLabel>
/*four palubs ship*/
class QDragEnterEvent;
class QDropEvent;
class fourPalubs :public QLabel
{
public:
    fourPalubs(QWidget *parent=0);
    void dragMoveEvent(QDragMoveEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QLabel *pix;
    QPoint position;
};

#endif // DRAGITEMS_H
