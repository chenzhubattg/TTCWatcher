#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include <QTcpSocket>
#include <QObject>
#include"common.h"

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent=0);
    QByteArray 		dataFlow;
signals:
    void updateClients(QString,int);
    void disconnected(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
<<<<<<< HEAD

=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
public:
    void readMsgBody(stFrameHeader &header,char * body,int bodyLength);
};

#endif // TCPCLIENTSOCKET_H
