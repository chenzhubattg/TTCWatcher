#include "TCPClient.h"
#include <QHostInfo>
#include <iostream>
#include <QTest>
#include "common.h"
#include <QFile>
#include "TCPServer.h"

extern TCPServer *pserver;
using namespace std;
TCPClient::TCPClient(QString  serverIpAdress,int serverPort)
 {

     strServerAddress = serverIpAdress; //QString::fromStdString(string(serverIpAdress));       //("%1").arg(s = serverIpAdress;
     nServerPort = serverPort;

    status = false;



    serverIP =new QHostAddress();
    serverIP->setAddress(strServerAddress);
    tcpSocket = new QTcpSocket();
    QString strInfo;
    strInfo = QString("Try to connect TTCServer(%1:%2)").arg(strServerAddress).arg(nServerPort);
    cout << strInfo.toStdString().c_str() << endl;
    while (1)
    {
        tcpSocket->connectToHost(*serverIP,nServerPort);
        if (tcpSocket->waitForConnected(2000))
        {
            cout << "Connected TTCServer successuflly." << endl;
            break;
        }
        else
        {
            QTest::qWait(1000);
            cout << "Try again." << endl;
        }
       }
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
}

TCPClient::~TCPClient()
{
}

void TCPClient::slotEnter()
{
}

void TCPClient::slotConnected()
{
}

void TCPClient::slotSend()
{
}

void TCPClient::slotDisconnected()
{
    cout <<  "disconnected server." << endl;
}

void TCPClient::dataReceived()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        dataFlow.append(tcpSocket->readAll());
        char *p=dataFlow.data();
        char *q=p+dataFlow.size();
        while(true){
            if(q-p<sizeof(stFrameHeader))break ;	//帧头不完整包，退出
            stFrameHeader header;
            memcpy(&header, p, sizeof(stFrameHeader));
            if(header.FLAG[0]!='M' || header.FLAG[1]!='M' || header.FLAG[2]!='X' || header.FLAG[3]!='H'){
                p=q;		//Header不对，丢弃当前所有缓存
                break ;
            }
            //2.读BODY,并移动流指针
            if(q-p<sizeof(stFrameHeader)+header.DATA_LEN)
                break ;//内容不完整包，退出
            readMsgBody(&header, p+sizeof(stFrameHeader),header.DATA_LEN);
            p+=sizeof(stFrameHeader)+header.DATA_LEN;
        }
        dataFlow=dataFlow.right( q - p);
    }
}


void TCPClient::readMsgBody(stFrameHeader *header,char * body,int bodyLength)
{
    qint16 cmd = header->cmd;
    QString strLog;
    switch(cmd)
    {
    case CMD_LOAD:                                //  Load *.grc and *.xml of flow graph
    {
  //      if (glbWatcherStatus != Idle)
 //       {
  //          strLog = "System is running,LOAD_CMD is rejected.";
   //         LogFile(glbfileLog,strLog);
    //    }
        LogFile(glbfileLog,"Receive CMD_LOAD cmd.");
        char FileName[56];
        memcpy(FileName,body,56);
        QString GrcFileName(FileName);
        GrcFileName = glbstrWorkDir + "/" + GrcFileName;
        QFile GrcFile(GrcFileName);
        if (!GrcFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
             strLog = "Can't open" + GrcFileName +"file." ;
            LogFile(glbfileLog,strLog);
            return ;
        }
        int fileLen = *(int *)(body + 56);
        char *pdata = body + 56 + sizeof(int);
        if (fileLen != GrcFile.write(pdata,fileLen))
        {
            strLog = "Save GRC file failed" ;
           LogFile(glbfileLog,strLog);
            GrcFile.close();
            return;
        }
        else
        {
            strLog = "Save GRC file successuflly!!!" ;
           LogFile(glbfileLog,strLog);
        }
        GrcFile.close();
        //Save XML file
        pdata = pdata + fileLen;
        memcpy(FileName,pdata,56);
        QString XMLFileName(FileName);
        XMLFileName = glbstrWorkDir + "/" + XMLFileName;
        QFile XMLFile(XMLFileName);
        if (!XMLFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
             strLog = "Can't open" + XMLFileName +"file!" ;
            LogFile(glbfileLog,strLog);
            return ;
        }
        fileLen = *(int *)(pdata + 56);
        pdata = pdata + 56 + sizeof(int);
        if (fileLen!= XMLFile.write(pdata,fileLen))
        {
            strLog = "Write XML failed" ;
           LogFile(glbfileLog,strLog);
            XMLFile.close();
            return;
        }
        else
        {
            strLog = "Save GRC file successuflly!!!" ;
           LogFile(glbfileLog,strLog);
        }
        XMLFile.close();
        //WatcherServer *pWserver = (WatcherServer *) m_pWatcherServer;
       // pWserver->updateClients((char *)header,sizeof(stFrameHeader));
      //  pWserver->updateClients(body,bodyLength);
        break;
    }
    case CMD_START:                              //  Running signal processing program in each nodes.
        break;
    case  CMD_KILL:                                  //  Kill signal processing thread in each nodes.
        break;
    case  CMD_SETPARAM:                      //   Set system param by relaying *.xml
        break;
    case  CMD_GETSTATUS:                     //   Get system status by relaying *.xml
        break;
    }

 /*   qint16 cmd = header.cmd;
    switch (cmd) {
    case CMD_LOAD:
    {
        cout << "Info:Receive CMD_LOAD cmd!!!" << endl;
        QString sStartCmd = "python " + glbExeName + " &";
        system(sStartCmd.toStdString().c_str());
        cout << "Info:" << sStartCmd.toStdString().c_str() << endl;
        QTest::qWait(2000);
        break;
    }
    case CMD_KILL:
    {
        cout << "Info:Receive CMD_KILL cmd!!!" << endl;
        if (!KillProcess(glbExeName))
        {
            cout << "Error: Fail to kill process!!!" << endl;
        }
        else
        {
            cout << "Info: Kill process!!!" << endl;
        }
        break;
    }
    case CMD_START:
    {

     //   pserver->SendMsg();
        break;
    }
    case CMD_STOP:
        break;
    case CMD_SET:
    {
        cout << "Info:Receive CMD_SET cmd!!!" << endl;
        char FileName[56];
        memcpy(FileName,body,56);
        QString XMLFileName(FileName);
        QFile paraFile(XMLFileName);
        QString strlog;
        if (!paraFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            strlog = "Error:Can't open" + XMLFileName +"file!!!" ;
            cout << strlog.toStdString().c_str() << endl;
            return ;
        }
        char *pdata = body + 56;
        if ((bodyLength - 56) != paraFile.write(pdata,bodyLength - 56))
        {
            cout <<  "Error:Write param info failed!!!" << endl;
            paraFile.close();
            return;
        }
        else
        {
            cout << "Info:Write para info to para file successuflly!!!" << endl;
        }

        stFrameHeader fh;
        fh.cmd = 0x04;
        fh.DATA_LEN = 0;
         // char *pdata="abcde";
        //  item->write(pdata,6);
        QByteArray data((char *)&fh,sizeof(stFrameHeader));
  //      QByteArray ba((char *)&nfre,sizeof(int));
        //ba.setNum(nfre);
   //     data = data + ba;
        pserver->SendMsg(data.data(),data.length());
       // stFrameHeader  da;
       // da.cmd = CMD_SET;
        //da.DATA_LEN = 0;
        //pserver->SendMsg((char *)&da,sizeof(stFrameHeader));
        //cout << "Info:send Set Param cmd to radio!!!" << endl;
        break;
    }
    default:
        break;
    }*/

}
