#ifndef CLIENT_H
#define CLIENT_H
#include <QTextEdit>
#include <QLineEdit>
class QAbstractSocket;
#include <QWidget>
#include <QTcpSocket>
#include <QMainWindow>
#include "gamefields.h"
#include "gamecell.h"
#include "gamemap.h"
#include "fourpalubs.h"
#include "threepalubs.h"
#include "twopalubs.h"
#include "onepalub.h"
#include <QMessageBox>
#include <QInputDialog>
namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(const QString& strHost, int nPort, QWidget* parent = 0) ;
    GameFields *field;
    fourPalubs *four;
    threePalubs *three;
    twoPalubs *two;
    OnePalub *one;
    int shipcells[10][10];
    int SurroundShip[12][12];
    //void startGameCicle();
    void syncMapFleet();
    void syncMapTarget();
    int flagPrint;
    QString status;
    void slotSendToServer(QString str);
    void paintig_enemy(QString &str);
    void painting_you(QString &str);
    void CheckIfKilled(QString &str);
    void startNewGame();
    QMessageBox msgBox;
    QMessageBox msgBox2;
    QString ipadress;
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket* m_pTcpSocket;
//    QTextEdit*  m_ptxtInfo;
//    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize; //длина следующего полученного от сокета блока
public slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
    void slotDisconnected();
private slots:
    void on_placeShipBtn_clicked();
    void on_ClearBtn_clicked();
    void on_DoneBtn_clicked();
};

#endif // CLIENT_H
