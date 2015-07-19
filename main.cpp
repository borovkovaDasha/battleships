#include "client.h"
#include <QApplication>
Client *client;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool bOk;
    QString str = QInputDialog::getText( 0,
                                         "Battleships",
                                         "input IP:",
                                         QLineEdit::Normal,
                                         "localhost",
                                         &bOk
                                        );
    if (!bOk) {
        exit(0);
    }
    client = new Client(str,2323);
    client->ipadress=str;
    client->setFixedSize(1100,800);
    client->setObjectName("widget");
    client->setStyleSheet("QWidget#widget { border-image: url(images/bg1.jpg) 0 0 0 0 stretch stretch; } ");

    client->show();

    return a.exec();
}
