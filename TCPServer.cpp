#include "TCPServer.h"
#include <iostream>
#include <QDebug>
using namespace std;
TCPServer::TCPServer(QObject *parent,int port)
    :QTcpServer(parent)
{
<<<<<<< HEAD
    QString strLog;
    if(listen(QHostAddress::Any,port))
    {
         strLog = "GR Server start listening.Port:" + QString::number(port);
        LogFile(glbfileLog,strLog);

    }
    else
    {
        strLog = "Fail to start Listening,Port:" + QString::number(port);
        LogFile(glbfileLog,strLog);
=======
//  connect(,SIGNAL(readyRead()),this,SLOT(dataReceived()));


    if(listen(QHostAddress::Any,port))
    {
        cout << "Watcher start listening" << endl;
    }
    else
    {
        cout << "Listening is failed! " << endl;
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
    }
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    connect(tcpClientSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
<<<<<<< HEAD
    tcpClientSocketList.append(tcpClientSocket);    
    QString strLog = QString("%1(%2) connect MonitorServer.").arg(tcpClientSocket->peerAddress().toString()).arg(tcpClientSocket->peerPort());
    LogFile(glbfileLog, strLog);
=======
   QHostAddress	 add = tcpClientSocket->localAddress();
   quint16 port = tcpClientSocket->localPort();
   qDebug() << add.toString() << " port:"<< port;
    tcpClientSocketList.append(tcpClientSocket);
//    timer = new QTimer(this);
  //    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  //    timer->start(1000);
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
}
void TCPServer::update()
{
    stFrameHeader fh;
    fh.cmd = 0x09;
    fh.DATA_LEN = sizeof(int);

    static int nfre = 100;

    if (nfre == 2000)
            nfre = 100;
      QTcpSocket *item = tcpClientSocketList.at(0);
     // char *pdata="abcde";
    //  item->write(pdata,6);
    QByteArray data((char *)&fh,sizeof(stFrameHeader));
    QByteArray ba((char *)&nfre,sizeof(int));
    //ba.setNum(nfre);
    data = data + ba;
    item->write(data.data(),data.length());


      cout << "send updata cmd" << endl;
      QString str = QString::number(nfre);
 //     item->write(str.toStdString().c_str(),str.length());
      nfre += 100;

}

void TCPServer::updateClients(QString msg,int length)
{
    emit updateServer(msg,length);
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->write(msg.toLatin1(),length)!=length)
        {
            continue;
        }
    }
}


void TCPServer::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}

void TCPServer::dataReceived()
{

}

void TCPServer::Log(QString &strLog,int type = 0,bool display = false)
{

}

<<<<<<< HEAD
int TCPServer::ClientsNum()
{
    return tcpClientSocketList.count();

}

=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
void TCPServer::SendMsg(const char *pdata,int length)
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->write(pdata,length)!=length)
        {
            continue;
        }
    }
}
<<<<<<< HEAD


=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
