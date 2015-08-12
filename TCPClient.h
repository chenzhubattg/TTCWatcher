#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QHostAddress>
#include <QTcpSocket>
<<<<<<< HEAD
#include <QHostAddress>
#include <QAbstractSocket>
#include <QHostInfo>
#include <QNetworkInterface>
#include "common.h"
#include <TTCdsp/Optimize.h>
#include <QTimer>

=======
#include "common.h"
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
class TCPClient:QObject
{
    Q_OBJECT
    
public:
    TCPClient(QString  serverIpAdress,int serverPort);
    ~TCPClient();
public:
    bool status;
    QString strServerAddress;
    int     nServerPort;
    QHostAddress *serverIP;
    QString userName;
    QTcpSocket *tcpSocket;
<<<<<<< HEAD
    QByteArray 		dataFlow;
    QTimer *timer;
=======
     QByteArray 		dataFlow;
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
public slots:
    void slotEnter();
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
    void slotSend();
<<<<<<< HEAD
    void SendStatus();
public:
   void readMsgBody(stFrameHeader *header, char * body, qint32 bodyLength);
=======
public:
   void readMsgBody(stFrameHeader *header,char * body,int bodyLength);
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
};

#endif // TCPCLIENT_H
