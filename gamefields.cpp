#include "gamefields.h"
/*here we make widget with 2 maps*/
GameFields::GameFields(QWidget *parent) :
   QDialog(parent)
{

            targetMap = new GameMap (this);
            fleetMap = new GameMap (this);
            verticalSeparator = new QFrame (this);
            verticalSeparator->setFrameShape(QFrame::VLine);
            verticalSeparator->setFrameShadow(QFrame::Sunken);
            layout = new QHBoxLayout (this);
            layout->addWidget(targetMap);
            layout->addWidget(verticalSeparator);
            layout->addWidget(fleetMap);

            targetMap->setEnabled(false);
            fleetMap->setEnabled(false);
            layout->SetFixedSize;
            setLayout(layout);


           // setWindowTitle(tr("Battleship"));
}
GameFields::~GameFields() {

}
