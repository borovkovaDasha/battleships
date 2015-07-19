#ifndef GAMEFIELDS_H
#define GAMEFIELDS_H

#include <QDialog>
#include "gamecell.h"
#include "gamemap.h"
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>

class GameFields : public QDialog
{
    Q_OBJECT

public:
    GameFields (QWidget *parent = 0);
    ~GameFields();
    bool start;
    GameMap  *targetMap;
    GameCell *cell;
    QFrame* verticalSeparator;
    GameMap * fleetMap;
    QHBoxLayout* layout;


};
#endif // DIALOG_H
