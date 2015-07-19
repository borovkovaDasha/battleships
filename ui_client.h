/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *shipLayout;
    QTextEdit *m_ptxtInfo;
    QLineEdit *m_ptxtInput;
    QPushButton *SendBtn;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *fieldLayout;
    QPushButton *placeShipBtn;
    QPushButton *ClearBtn;
    QPushButton *DoneBtn;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(1116, 714);
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(870, 190, 201, 211));
        shipLayout = new QVBoxLayout(verticalLayoutWidget_3);
        shipLayout->setSpacing(6);
        shipLayout->setContentsMargins(11, 11, 11, 11);
        shipLayout->setObjectName(QStringLiteral("shipLayout"));
        shipLayout->setContentsMargins(0, 0, 0, 0);
        m_ptxtInfo = new QTextEdit(centralWidget);
        m_ptxtInfo->setObjectName(QStringLiteral("m_ptxtInfo"));
        m_ptxtInfo->setGeometry(QRect(30, 440, 831, 171));
        m_ptxtInput = new QLineEdit(centralWidget);
        m_ptxtInput->setObjectName(QStringLiteral("m_ptxtInput"));
        m_ptxtInput->setGeometry(QRect(30, 610, 831, 20));
        SendBtn = new QPushButton(centralWidget);
        SendBtn->setObjectName(QStringLiteral("SendBtn"));
        SendBtn->setGeometry(QRect(30, 630, 831, 23));
        SendBtn->setAutoFillBackground(true);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 851, 341));
        fieldLayout = new QVBoxLayout(verticalLayoutWidget);
        fieldLayout->setSpacing(0);
        fieldLayout->setContentsMargins(11, 11, 11, 11);
        fieldLayout->setObjectName(QStringLiteral("fieldLayout"));
        fieldLayout->setSizeConstraint(QLayout::SetFixedSize);
        fieldLayout->setContentsMargins(0, 0, 0, 0);
        placeShipBtn = new QPushButton(centralWidget);
        placeShipBtn->setObjectName(QStringLiteral("placeShipBtn"));
        placeShipBtn->setGeometry(QRect(880, 20, 185, 52));
        placeShipBtn->setStyleSheet(QLatin1String("QPushButton {\n"
"border: none;\n"
"    background-image: url(images/btn1.png);\n"
"}\n"
"\n"
"QPushButton:Pressed {\n"
"border:none;\n"
"background-image: url(images/btn1hover.png);\n"
"}"));
        ClearBtn = new QPushButton(centralWidget);
        ClearBtn->setObjectName(QStringLiteral("ClearBtn"));
        ClearBtn->setGeometry(QRect(880, 80, 185, 40));
        ClearBtn->setStyleSheet(QLatin1String("QPushButton {\n"
"border: none;\n"
"    background-image: url(images/clearbtn.png);\n"
"}\n"
"\n"
"QPushButton:Pressed{\n"
"border:none;\n"
"background-image: url(images/clearbtnhover.png);\n"
"}"));
        DoneBtn = new QPushButton(centralWidget);
        DoneBtn->setObjectName(QStringLiteral("DoneBtn"));
        DoneBtn->setGeometry(QRect(880, 130, 185, 40));
        DoneBtn->setStyleSheet(QLatin1String("QPushButton {\n"
"border: none;\n"
"    background-image: url(images/donebtn.png);\n"
"}\n"
"\n"
"QPushButton:Pressed {\n"
"border:none;\n"
"background-image: url(images/donebtnhover.png);\n"
"}"));
        Client->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Client);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Client->setStatusBar(statusBar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", 0));
        SendBtn->setText(QApplication::translate("Client", "Send", 0));
        placeShipBtn->setText(QString());
        ClearBtn->setText(QString());
        DoneBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
