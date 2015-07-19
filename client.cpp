#include "client.h"
#include "ui_client.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QFont>
extern Client *client;
Client::Client(const QString& strHost,
                int            nPort,
                QWidget*       parent /*=0*/
               ) : QMainWindow(parent),m_nNextBlockSize(0),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    m_pTcpSocket = new QTcpSocket(this);
    field=new GameFields(this);
    four = new fourPalubs(this);
    three= new threePalubs(this);
    two = new twoPalubs(this);
    one = new OnePalub(this);

    msgBox.setText("Game is over! ");

       msgBox.setInformativeText("Would you like to play again?");

       msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
       msgBox.setDefaultButton(QMessageBox::Yes);
       msgBox2.setText("Game is over! ");

          msgBox2.setInformativeText("Your partner has disconnected from server! Would you like to play again?");

          msgBox2.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
          msgBox2.setDefaultButton(QMessageBox::Yes);
    setWindowTitle("Battleships");
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );
    connect(ui->SendBtn, SIGNAL(clicked()),
            this,        SLOT(slotSendToServer())
           );


    ui->m_ptxtInfo->setReadOnly(true);
    ui->fieldLayout->addWidget(field);
    ui->shipLayout->addWidget(four);
    ui->shipLayout->addWidget(three);
    ui->shipLayout->addWidget(two);
    ui->shipLayout->addWidget(one);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            shipcells[i][j]=0;
            field->targetMap->cells[i][j]->isEnemy=false;
            field->fleetMap->cells[i][j]->isEnemy=true;

        }
     }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            SurroundShip[i][j]=0;
        }
     }
    ui->placeShipBtn->setEnabled(false);
    ui->DoneBtn->setEnabled(false);
    ui->ClearBtn->setEnabled(false);
    ui->m_ptxtInfo->setEnabled(false);
    ui->m_ptxtInput->setEnabled(false);
    //ui->shipLayout->setEnabled(false);
//slotSendToServer("start");

}

Client::~Client()
{
    delete ui;
    m_pTcpSocket->disconnectFromHost();

}

void Client::slotDisconnected(){
    qDebug() <<"disconnected";
}

void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;
        qDebug() << str;
        if (str.contains("message", Qt::CaseInsensitive))
        {
            qDebug() << "message is here";
            str.remove(0,7);
            ui->m_ptxtInfo->append(time.toString() + " " + str);
            m_nNextBlockSize = 0;
        }
        else if (str.contains("disconnect", Qt::CaseInsensitive)){
          ui->m_ptxtInfo->append("Your partner has been disconnected from server. You win!!!");
          int ret=msgBox2.exec();
          m_nNextBlockSize = 0;
          if(ret==QMessageBox::Yes){
              //slotSendToServer();
              //startNewGame();
              startNewGame();
              this->m_pTcpSocket->connectToHost(ipadress, 2323);
              qDebug() <<"starting new game";
}
          else
             exit(0);


        }
        else if (str.contains("refused", Qt::CaseInsensitive)){
            QMessageBox msg3;
            msg3.setText("Connection is failed! ");
            msg3.setInformativeText("Your connection is refused. May be there are no free places on server. Would you like to try again?");

            msg3.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg3.setDefaultButton(QMessageBox::Yes);
            int ret=msg3.exec();
            m_nNextBlockSize = 0;
            if(ret==QMessageBox::Yes){
                //slotSendToServer();
                //startNewGame();
                startNewGame();
                this->m_pTcpSocket->connectToHost(ipadress, 2323);
                qDebug() <<"starting new game";
  }
            else
               exit(0);



        }
        else if(str.contains("connected", Qt::CaseInsensitive))
        {
            status = "connected";
            ui->m_ptxtInfo->setTextColor(QColor(0,100,0));
            ui->m_ptxtInfo->append("* * * * * * * * * * Conected to server  * * * * * * * * * * ");
            ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
            m_nNextBlockSize = 0;
        }
        else if(str.contains("arrangement", Qt::CaseInsensitive))
        {
            ui->m_ptxtInfo->setEnabled(false);
            ui->m_ptxtInput->setEnabled(false);
            status = "arrangment";

            ui->m_ptxtInfo->setTextColor(QColor(0,100,0));
            ui->m_ptxtInfo->append("* * * * * * * * * *Set your ships!  * * * * * * * * * * ");
            ui->m_ptxtInfo->append("for each ships drag it with a left mouse for horizontal placement and with right button for vertical");
            ui->m_ptxtInfo->setTextColor(QColor(0,0,0));

            ui->placeShipBtn->setEnabled(true);
            ui->DoneBtn->setEnabled(true);
            ui->ClearBtn->setEnabled(true);
            ui->m_ptxtInfo->setEnabled(true);
            ui->m_ptxtInput->setEnabled(true);
            m_nNextBlockSize = 0;
        }
        else if(str.contains("play", Qt::CaseInsensitive))
        {
            status = "play";
             ui->m_ptxtInfo->setTextColor(QColor(0,100,0));
            ui->m_ptxtInfo->append("*** Your turn! ***");//разрешить стрелять
            ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
            field->fleetMap->setEnabled(true);
            ui->ClearBtn->setEnabled(false);
            ui->DoneBtn->setEnabled(false);
            ui->placeShipBtn->setEnabled(false);

            m_nNextBlockSize = 0;
        }
        else if(str.contains("waiting", Qt::CaseInsensitive))
        {
            status = "waiting";
            ui->m_ptxtInfo->setTextColor(QColor(0,100,0));
            ui->m_ptxtInfo->append("*** Enemy's turn. Waiting!***");//всё заблокировать
            ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
            field->fleetMap->setEnabled(false);
            m_nNextBlockSize = 0;
        }
        else if(str.contains("results", Qt::CaseInsensitive))
        {
            qDebug()<< "1"<< str;
            status = "waiting";
            //ui->m_ptxtInfo->append("results");//отрисовать клетку на поле, в которую ты ударил
            painting_you(str);
            m_nNextBlockSize = 0;
        }
        else if(str.contains("enemy", Qt::CaseInsensitive))
        {
            qDebug()<<"2"<<str;
            status = "waiting";
            //ui->m_ptxtInfo->append("enemy_results");//отрисовать клетку на поле, в которую враг ударил
            paintig_enemy(str);
            m_nNextBlockSize = 0;
        }
        else if(str.contains("win", Qt::CaseInsensitive))
        {
            status = "Win";
            ui->m_ptxtInfo->setFontWeight( QFont::DemiBold );
            ui->m_ptxtInfo->setTextColor(QColor(255,0,0));
            ui->m_ptxtInfo->append("WIN!!");//победа
            ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
            ui->m_ptxtInfo->setFontWeight(QFont::Normal);
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    field->fleetMap->cells[i][j]->acceptClicks=false;
                 }
            }
            m_nNextBlockSize = 0;
            int ret = msgBox.exec();
            if(ret==QMessageBox::Yes){
                //slotSendToServer();
                //startNewGame();
                startNewGame();
                this->m_pTcpSocket->connectToHost(ipadress, 2323);
                qDebug() <<"starting new game";
}
            else
               exit(0);
        }
        else if(str.contains("lose", Qt::CaseInsensitive))
        {
            status = "lose";
            ui->m_ptxtInfo->setTextColor(QColor(255,0,0));
            ui->m_ptxtInfo->append("LOSER!!!");//проиграл
            ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
            m_nNextBlockSize = 0;
            int ret = msgBox.exec();
            if(ret==QMessageBox::Yes){
                startNewGame();
                this->m_pTcpSocket->connectToHost(ipadress, 2323);
                qDebug() <<"starting new game";

            }
            else
               exit(0);

        }
        else if(str.contains("kill1", Qt::CaseInsensitive)){
            //qDebug() << "u killed him!";
            flagPrint=1;
            CheckIfKilled(str);

            m_nNextBlockSize = 0;
        }
        else if(str.contains("kill2", Qt::CaseInsensitive)){
            //qDebug() << "u killed him!";
            flagPrint=0;
            CheckIfKilled(str);

            m_nNextBlockSize = 0;
        }
    }
}
void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    ui->m_ptxtInfo->append(strError);
}
void Client::slotSendToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    QString str = "message " + ui->m_ptxtInput->text();
    out << quint16(0) <<QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    ui->m_ptxtInfo->append("you: " + ui->m_ptxtInput->text());
    m_pTcpSocket->write(arrBlock);
    ui->m_ptxtInput->setText("");
}
void Client::slotSendToServer(QString str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    qDebug()<<str;
    //m_ptxtInfo->append(m_ptxtInput->text());
    m_pTcpSocket->write(arrBlock);
    //m_ptxtInput->setText("");
}
void Client::slotConnected()
{
    ui->m_ptxtInfo->setTextColor(QColor(0,100,0));
    ui->m_ptxtInfo->append("Received the connected() signal");
    ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
}

void Client::painting_you(QString &str)
{
    int x, y, res;
    str.remove(0,7);
    QString symbol = str.section(' ', 1, 1);
    x = symbol.toInt();
    str.remove(0,2);
    symbol = str.section(' ', 1, 1);
    y = symbol.toInt();
    str.remove(0,2);
    symbol = str.section(' ', 1, 1);
    res = symbol.toInt();
    qDebug()<<"x1 = "<<x<<"y1 = "<<y<<"res1 = "<<res;//отрисовка
    if(res==1){
       field->fleetMap->cells[x][y]->currentState=GameCell::Hit;
       field->fleetMap->cells[x][y]->syncBitmap();
       field->fleetMap->cells[x][y]->acceptClicks=false;
    }
    else if (res==0){
        field->fleetMap->cells[x][y]->currentState=GameCell::Miss;
        field->fleetMap->cells[x][y]->syncBitmap();
        field->fleetMap->cells[x][y]->acceptClicks=false;
    }
}

void Client::paintig_enemy(QString &str)
{
    int x, y, res;
    str.remove(0,5);
    QString symbol = str.section(' ', 1, 1);
    x = symbol.toInt();
    str.remove(0,2);
    symbol = str.section(' ', 1, 1);
    y = symbol.toInt();
    str.remove(0,2);
    symbol = str.section(' ', 1, 1);
    res = symbol.toInt();
    qDebug()<<"x2 = "<<x<<"y2 = "<<y<<"res2 = "<<res;//отрисовка
    if(res==1){
       field->targetMap->cells[x][y]->currentState=GameCell::Hit;
       field->targetMap->cells[x][y]->syncBitmap();
    }
    else if (res==0){
        field->targetMap->cells[x][y]->currentState=GameCell::Miss;
        field->targetMap->cells[x][y]->syncBitmap();
    }
}


void Client::on_placeShipBtn_clicked()
{
    field->targetMap->setEnabled(true);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
               field->targetMap->cells[i][j]->setEnabled(true);
               field->targetMap->cells[i][j]->acceptClicks=true;
            }
        }
}

void Client::on_ClearBtn_clicked()
{
    ui->m_ptxtInfo->setTextColor(QColor(0,100,0));
    ui->m_ptxtInfo->append("*** The field is cleared. Reset your ships ***");
    ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
    field->targetMap->fourCount=1;
    field->targetMap->threeCount=2;
    field->targetMap->twoCount=3;
    field->targetMap->oneCount=4;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
           // dialog->targetMap->cells[i][j]->setEnabled(true);
             field->targetMap->cells[i][j]->currentState=GameCell::Undiscovered;
             field->targetMap->cells[i][j]->syncBitmap();
             field->targetMap->ships[i+1][j+1]=0;
         }
    }
}



void Client::on_DoneBtn_clicked()
{
//    if (field->targetMap->fourCount==0 &&field->targetMap->threeCount==0 && field->targetMap->twoCount==0
//           && field->targetMap->oneCount==0){
    QString answer = "field ";
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    shipcells[i][j]=field->targetMap->ships[i+1][j+1];
                    printf("%d ",shipcells[i][j]);
                   field->targetMap->cells[i][j]->acceptClicks=false;
                   answer.append(QString::number(shipcells[i][j]));
                   answer.append(" ");
                 }
                printf("\n");
            }

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    field->fleetMap->cells[i][j]->acceptClicks=true;
                 }
            }
    four->setVisible(false);
    four->setEnabled(false);
    three->setVisible(false);
    three->setEnabled(false);
    two->setVisible(false);
   two->setEnabled(false);
   one->setVisible(false);
   one->setEnabled(false);
   ui->placeShipBtn->setEnabled(false);
   ui->DoneBtn->setEnabled(false);
   ui->ClearBtn->setEnabled(false);
   //startGameCicle();
   slotSendToServer(answer);


   // }
//   ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
//   ui->m_ptxtInfo->append("*** Place all of your ships! ***");
//   ui->m_ptxtInfo->setTextColor(QColor(0,0,0));
}

//void Client::startGameCicle(){
//    ui->ClearBtn->setEnabled(false);
//    ui->DoneBtn->setEnabled(false);
//    ui->placeShipBtn->setEnabled(false);
//    qDebug() <<" game is started!";
///* some magic check who's 1st turn is it"*/
////case (turn==1):
//    field->fleetMap->setEnabled(true);
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//             field->fleetMap->cells[i][j]->acceptClicks=true;
//         }
//    }
//}
void Client::CheckIfKilled(QString &str){
    int x, y, res;
    str.remove(0,5);
    QString symbol = str.section(' ', 1, 1);
    x = symbol.toInt();
    str.remove(0,2);
    symbol = str.section(' ', 1, 1);
    y = symbol.toInt();
    str.remove(0,2);
    symbol = str.section(' ', 1, 1);
    res = symbol.toInt();
    qDebug() << res;
   switch (res){
    case -8:
        qDebug() << "i killed 4 palubs hor";
        SurroundShip[x][y]=SurroundShip[x][y+1]=SurroundShip[x][y+2]=SurroundShip[x][y+3]=SurroundShip[x][y+4]=SurroundShip[x][y+5]=
        SurroundShip[x+1][y]=SurroundShip[x+1][y+5]=
        SurroundShip[x+2][y]=SurroundShip[x+2][y+1]=SurroundShip[x+2][y+2]=SurroundShip[x+2][y+3]=SurroundShip[x+2][y+4]=SurroundShip[x+2][y+5]=-1;
        if(flagPrint==1)
            syncMapFleet();
        else syncMapTarget();
        break;
    case -7:
       qDebug() << "i killed 3 palubs hor";
       SurroundShip[x][y]=SurroundShip[x][y+1]=SurroundShip[x][y+2]=SurroundShip[x][y+3]=SurroundShip[x][y+4]=
       SurroundShip[x+1][y]=SurroundShip[x+1][y+4]=
       SurroundShip[x+2][y]=SurroundShip[x+2][y+1]=SurroundShip[x+2][y+2]=SurroundShip[x+2][y+3]=SurroundShip[x+2][y+4]=-1;
       if(flagPrint==1)
           syncMapFleet();
       else syncMapTarget();
       break;
    case -6:
       SurroundShip[x][y]=SurroundShip[x][y+1]=SurroundShip[x][y+2]=SurroundShip[x][y+3]=
       SurroundShip[x+1][y]=SurroundShip[x+1][y+3]=
       SurroundShip[x+2][y]=SurroundShip[x+2][y+1]=SurroundShip[x+2][y+2]=SurroundShip[x+2][y+3]=-1;
       if(flagPrint==1)
           syncMapFleet();
       else syncMapTarget();
       break;
    case -5:
       SurroundShip[x][y]=SurroundShip[x][y+1]=SurroundShip[x][y+2]=
       SurroundShip[x+1][y]=SurroundShip[x+1][y+2]=
       SurroundShip[x+2][y]=SurroundShip[x+2][y+1]=SurroundShip[x+2][y+2]=-1;
       if(flagPrint==1)
           syncMapFleet();
       else syncMapTarget();
       break;
    case -4:
       SurroundShip[x][y+2]=SurroundShip[x+1][y+2]=SurroundShip[x+2][y+2]=SurroundShip[x+3][y+2]=SurroundShip[x+4][y+2]=SurroundShip[x+5][y+2]=
       SurroundShip[x][y+1]=SurroundShip[x+5][y+1]=
       SurroundShip[x][y]=SurroundShip[x+1][y]=SurroundShip[x+2][y]=SurroundShip[x+3][y]=SurroundShip[x+4][y]=SurroundShip[x+5][y]=-1;
       if(flagPrint==1)
           syncMapFleet();
       else syncMapTarget();
       break;
    case -3:
       SurroundShip[x][y+2]=SurroundShip[x+1][y+2]=SurroundShip[x+2][y+2]=SurroundShip[x+3][y+2]=SurroundShip[x+4][y+2]=
       SurroundShip[x][y+1]=SurroundShip[x+4][y+1]=
       SurroundShip[x][y]=SurroundShip[x+1][y]=SurroundShip[x+2][y]=SurroundShip[x+3][y]=SurroundShip[x+4][y]=-1;
       if(flagPrint==1)
           syncMapFleet();
       else syncMapTarget();
       break;
    case -2:
       SurroundShip[x][y+2]=SurroundShip[x+1][y+2]=SurroundShip[x+2][y+2]=SurroundShip[x+3][y+2]=
       SurroundShip[x][y+1]=SurroundShip[x+3][y+1]=
       SurroundShip[x][y]=SurroundShip[x+1][y]=SurroundShip[x+2][y]=SurroundShip[x+3][y]=-1;
       if(flagPrint==1)
           syncMapFleet();
       else syncMapTarget();
       break;
    }
}
void Client::syncMapFleet(){
    qDebug()<< "synchro this map";
    for (int i=0; i<10; i++){
        for (int j=0;j<10;j++){
            if(SurroundShip[i+1][j+1]==-1){
                qDebug() << "placing the cells";
            field->fleetMap->cells[i][j]->acceptClicks=false;
            field->fleetMap->cells[i][j]->currentState=GameCell::Miss;
            field->fleetMap->cells[i][j]->syncBitmap();
            SurroundShip[i+1][j+1]=0;
            }
        }
    }
}

void Client::syncMapTarget(){
    qDebug()<< "synchro this map";
    for (int i=0; i<10; i++){
        for (int j=0;j<10;j++){
            if(SurroundShip[i+1][j+1]==-1){
                qDebug() << "placing the cells";
            field->targetMap->cells[i][j]->acceptClicks=false;
            field->targetMap->cells[i][j]->currentState=GameCell::Miss;
            field->targetMap->cells[i][j]->syncBitmap();
            SurroundShip[i+1][j+1]=0;
            }
        }
    }
}

void Client::startNewGame(){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            shipcells[i][j]=0;
            field->targetMap->cells[i][j]->isEnemy=false;
            field->fleetMap->cells[i][j]->isEnemy=true;
            field->targetMap->cells[i][j]->currentState=GameCell::Undiscovered;
            field->fleetMap->cells[i][j]->currentState=GameCell::Undiscovered;
            field->targetMap->cells[i][j]->syncBitmap();
            field->fleetMap->cells[i][j]->syncBitmap();
        }
     }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            SurroundShip[i][j]=0;
            field->fleetMap->ships[i][j]=0;
            field->targetMap->ships[i][j]=0;
        }
     }
    ui->placeShipBtn->setEnabled(false);
    ui->DoneBtn->setEnabled(false);
    ui->ClearBtn->setEnabled(false);
    ui->m_ptxtInfo->setEnabled(false);
    ui->m_ptxtInput->setEnabled(false);
     ui->shipLayout->setEnabled(true);
     four->setVisible(true);
     four->setEnabled(true);
     three->setVisible(true);
     three->setEnabled(true);
     two->setVisible(true);
    two->setEnabled(true);
    one->setVisible(true);
    one->setEnabled(true);
    field->targetMap->setEnabled(false);
    field->fleetMap->setEnabled(false);
    field->targetMap->fourCount=1;
    field->targetMap->threeCount=2;
    field->targetMap->twoCount=3;
    field->targetMap->oneCount=4;

}
