#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QHostAddress>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QHostInfo>
#include <QNetworkInterface>
#include "common.h"
#include <TTCdsp/Optimize.h>
#include <QTimer>

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
    QByteArray 		dataFlow;
    QTimer *timer;
public slots:
    void slotEnter();
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
    void slotSend();
    void SendStatus();
public:
   void readMsgBody(stFrameHeader *header, char * body, qint32 bodyLength);
};

#endif // TCPCLIENT_H
