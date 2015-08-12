#include "TCPClient.h"
#include <QHostInfo>
#include <iostream>
#include <QTest>
#include "common.h"
#include <QFile>
#include "TCPServer.h"
<<<<<<< HEAD
#include <TTCdsp/Optimize.h>
=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1

extern TCPServer *pserver;
using namespace std;
TCPClient::TCPClient(QString  serverIpAdress,int serverPort)
<<<<<<< HEAD
{

    strServerAddress = serverIpAdress; //QString::fromStdString(string(serverIpAdress));       //("%1").arg(s = serverIpAdress;
    nServerPort = serverPort;
    status = false;
    serverIP = new QHostAddress();
    serverIP->setAddress(strServerAddress);
    tcpSocket = new QTcpSocket();
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    QString strInfo;
    strInfo = QString("Try to connect TTCServer(%1:%2)").arg(strServerAddress).arg(nServerPort);
    LogFile(glbfileLog,strInfo);
    // cout << strInfo.toStdString().c_str() << endl;
    while (1)
    {
        tcpSocket->connectToHost(*serverIP,(quint16)nServerPort);
        if (tcpSocket->waitForConnected(2000))
        {
            LogFile(glbfileLog,"Connected TTCServer successuflly." );
=======
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
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
            break;
        }
        else
        {
            QTest::qWait(1000);
<<<<<<< HEAD
            LogFile(glbfileLog,strInfo);

        }
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(SendStatus()));

=======
            cout << "Try again." << endl;
        }
       }
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
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

<<<<<<< HEAD
void TCPClient::SendStatus()
{
//    if (XMLStatusFileName.length() == 0)
//        return;
    if(temp != true)
        return;

    QFile file(XMLStatusFileName);
    QString strLog;// = "Disconnected Server";
    if(!file.open(QIODevice::ReadOnly))
    {
        strLog = "Can't open status file.";
        LogFile(glbfileLog,strLog);
        return;
    }
    if (file.size() == 0)
    {
        strLog = "The size of status file is wrong.";
        LogFile(glbfileLog,strLog);
        return;
    }
    char name[56];
    QString purFileName = XMLStatusFileName.right(XMLStatusFileName.length() - XMLStatusFileName.lastIndexOf("/")  - 1);
    memset(name, 0, 56);
    QByteArray arb = purFileName.toLatin1();
    memcpy(name, arb.data(), purFileName.length());
    QByteArray dataName;
    dataName.append(name, 56);

    stFrameHeader FH;
    FH.cmd = CMD_GETSTATUS;
    QByteArray data = file.readAll();
    qint32 nLen = data.length();
    data = dataName + QByteArray((char *)&nLen  ,sizeof(qint32)) + data;
    FH.DATA_LEN = data.length();
    QByteArray header((char *)&FH, sizeof(stFrameHeader));
    data = header + data;
    tcpSocket->write(data);
    file.close();

}

void TCPClient::slotDisconnected()
{
    QString strLog = "Disconnected Server";
    LogFile(glbfileLog,strLog);
=======
void TCPClient::slotDisconnected()
{
    cout <<  "disconnected server." << endl;
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
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
<<<<<<< HEAD
            qDebug() << dataFlow.size();
=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
            if(q-p<sizeof(stFrameHeader)+header.DATA_LEN)
                break ;//内容不完整包，退出
            readMsgBody(&header, p+sizeof(stFrameHeader),header.DATA_LEN);
            p+=sizeof(stFrameHeader)+header.DATA_LEN;
        }
        dataFlow=dataFlow.right( q - p);
    }
}


<<<<<<< HEAD
void TCPClient::readMsgBody(stFrameHeader *header,char * body,qint32 bodyLength)
=======
void TCPClient::readMsgBody(stFrameHeader *header,char * body,int bodyLength)
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
{
    qint16 cmd = header->cmd;
    QString strLog;
    switch(cmd)
    {
    case CMD_LOAD:                                //  Load *.grc and *.xml of flow graph
    {
<<<<<<< HEAD
        LogFile(glbfileLog,"Receive CMD_LOAD cmd.");
        //QDir dirWork;
        //glbstrWorkDir = QString("%1/WatcherWork").arg(QDir::currentPath());
       // dirWork.mkdir(glbstrWorkDir);
      //  system("cp ./Support/tcpclient.py ./WatcherWork/");
        QFile copyfile;
        QString tcpclientpy = glbstrWorkDir + "/tcpclient.py";
        QString tcpsourcepy = glbstrWorkDir.left(glbstrWorkDir.lastIndexOf("/"))  + "/Support/tcpclient.py";
        copyfile.copy(tcpsourcepy,tcpclientpy);


=======
  //      if (glbWatcherStatus != Idle)
 //       {
  //          strLog = "System is running,LOAD_CMD is rejected.";
   //         LogFile(glbfileLog,strLog);
    //    }
        LogFile(glbfileLog,"Receive CMD_LOAD cmd.");
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
        char FileName[56];
        memcpy(FileName,body,56);
        QString GrcFileName(FileName);
        GrcFileName = glbstrWorkDir + "/" + GrcFileName;
        QFile GrcFile(GrcFileName);
        if (!GrcFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
<<<<<<< HEAD
            strLog = "Can't open" + GrcFileName +"file." ;
            LogFile(glbfileLog,strLog);
            return ;
        }
        qint32 fileLen = *(qint32 *)(body + 56);
        char *pdata = body + 56 + sizeof(qint32);
        if (fileLen != GrcFile.write(pdata,fileLen))
        {
            strLog = "Save GRC file failed" ;
            LogFile(glbfileLog,strLog);
=======
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
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
            GrcFile.close();
            return;
        }
        else
        {
            strLog = "Save GRC file successuflly!!!" ;
<<<<<<< HEAD
            LogFile(glbfileLog,strLog);
=======
           LogFile(glbfileLog,strLog);
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
        }
        GrcFile.close();
        //Save XML file
        pdata = pdata + fileLen;
        memcpy(FileName,pdata,56);
        QString XMLFileName(FileName);
<<<<<<< HEAD
        QString XMLPureFileName = XMLFileName;
        XMLFileName = glbstrWorkDir + "/" + XMLPureFileName;
        QFile XMLFile(XMLFileName);
        if (!XMLFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            strLog = "Can't open" + XMLFileName +"file!" ;
            LogFile(glbfileLog,strLog);
            return ;
        }
        fileLen = *(qint32 *)(pdata + 56);
        pdata = pdata + 56 + sizeof(qint32);
        if (fileLen!= XMLFile.write(pdata,fileLen))
        {
            strLog = "Write XML failed" ;
            LogFile(glbfileLog,strLog);
=======
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
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
            XMLFile.close();
            return;
        }
        else
        {
<<<<<<< HEAD
            strLog = "Save XML file successuflly!!!" ;
            LogFile(glbfileLog,strLog);
        }
        XMLFile.close();
        XMLStatusFileName = glbstrWorkDir + "/" + "Status_" + XMLPureFileName;
        if (QFile::exists(XMLStatusFileName))
        {
            if(!QFile::remove(XMLStatusFileName))
            {
                strLog = "Delete old status XML unsuccessfully!" ;
                LogFile(glbfileLog,strLog);
            }
            else
            {
                strLog = "Delete old status XML successfully!" ;
                LogFile(glbfileLog,strLog);
            }
        }
        if (!QFile::copy(XMLFileName,XMLStatusFileName))
        {
            strLog = "Copy status XML file unsuccessfully!" ;
            LogFile(glbfileLog,strLog);
        }
        //Generate serval grc files named by IP address
        OPT_Gen_Ipgrc(GrcFileName.toStdString().c_str() ,  (glbstrWorkDir +"/").toStdString().c_str());
        //        QString localIp = QNetworkInterface::allInterfaces().at(1).addressEntries().at(0).ip().toString();
        QString localIp;
        QString strLocalGrcFilePath;
        QList<QHostAddress> IpList = QNetworkInterface::allAddresses();
        bool fdit = false;
        for(int i=0; i< IpList.size(); i++)
        {
            localIp = IpList.at(i).toString();
            strLocalGrcFilePath = glbstrWorkDir + "/"  + localIp + ".grc";
            if (!FileExists(strLocalGrcFilePath,3000))
            {
                strLog = "The file" + strLocalGrcFilePath + " didn't existed.";
                LogFile(glbfileLog,strLog);
                continue;
            }
            else
            {
                strLog = "The file" + strLocalGrcFilePath + "is generated succefully.";
                LogFile(glbfileLog,strLog);
                fdit = true;
                break;
            }
        }

        if(fdit == false)
        {
            strLog = "The file" + strLocalGrcFilePath + "didn't existed";
            LogFile(glbfileLog,strLog);
            return;
        }

        //Set Graph ID value, the pyton file name will be generated according this value.
        QFile fileGrc(strLocalGrcFilePath);
        if (!fileGrc.open(QIODevice::ReadWrite))
        {
            strLog = "Cann't open " + strLocalGrcFilePath;
            LogFile(glbfileLog,strLog);
            return;
        }
        QTextStream in(&fileGrc);
        QString strGrcFile = in.readAll();
        int nStartNum = strGrcFile.indexOf("<value>",strGrcFile.indexOf("options"));
        int nEndNum = strGrcFile.indexOf("</value>",strGrcFile.indexOf("options"));
        strGrcFile = strGrcFile.replace(nStartNum + 7,nEndNum - nStartNum -7, glbLocalGRIDName);
        fileGrc.resize(0);
        fileGrc.write(strGrcFile.toLatin1());
        fileGrc.close();
        //Generate python file according to Local IP address
        QString sStartCmd = "gnuradio-companion " +  glbstrWorkDir + "/"  + localIp + ".grc" + " &";
        system(sStartCmd.toStdString().c_str());
        QTest::qWait(2000);  //make sure the *.grc is generated;

       QString strLocalPythonPath = glbstrWorkDir + "/" + glbPyFileName;
   /*             QFile EXEfile(strLocalPythonPath);
                bool bFileOpen = false;
                qint32 nWaitTime = 0;
                while(!bFileOpen && !nWaitTime <= 5000)
                {
                    bFileOpen = EXEfile.open(QIODevice::ReadOnly);
                    QTest::qWait(100);
                    nWaitTime += 100;
                }
                if (nWaitTime <= 5000)
                {
                    EXEfile.close();
                    strLog = "The file" + strLocalPythonPath + "is generated succefully.";
                    LogFile(glbfileLog,strLog);
                }
                else
                {
                    strLog = "The file" + strLocalPythonPath + "didn't existed.";
                    LogFile(glbfileLog,strLog);
                }
*/




     //   if (!FileExists(strLocalPythonPath,3000))
      //  {
      //
         //   return;
       // }
      // else
      //  {
      //
       // }
        QString strLocalExePython  =  glbstrWorkDir + "/" + glbExePyFile;
        //       OPT_Modify_Py( QString(glbstrWorkDir + "/"  + localIp + ".grc").toStdString().c_str() , QString(glbstrWorkDir + "/" + glbPyFileName).toStdString().c_str() , QString(glbstrWorkDir + "/" + glbExePyFile).toStdString().c_str());
        OPT_Modify_Py(strLocalGrcFilePath.toStdString().c_str() ,
                      strLocalPythonPath.toStdString().c_str() ,
                      strLocalExePython.toStdString().c_str(),
                      XMLFileName.toStdString().c_str(),
                      XMLStatusFileName.toStdString().c_str());
        if (!FileExists(strLocalExePython,3000))
        {
            strLog = "The file" + strLocalExePython + "didn't existed.";
            LogFile(glbfileLog,strLog);
            return;
        }
        else
        {
            strLog = "The file" + strLocalExePython + " is generated succefully.";
            LogFile(glbfileLog,strLog);
        }
        break;
    }
    case CMD_START:                              //  Running signal processing program in each nodes.
    {
        LogFile(glbfileLog,"Receive CMD_START cmd.");
        QString strLocalExePython  =  glbstrWorkDir + "/" + glbExePyFile;
        if (!QFile::exists(strLocalExePython))
        {
            strLog = "The file" + strLocalExePython + "didn't existed.";
            LogFile(glbfileLog,strLog);
            return;
        }
        else
        {
            strLog = "The file" + strLocalExePython + "is generated succefully.";
            LogFile(glbfileLog,strLog);
        }
        glbExePythonPath = glbstrWorkDir + "/"  + glbExePyFile;
        QString sStartNewCmd = "python " +  glbExePythonPath + "&";
        system(sStartNewCmd.toStdString().c_str());
         timer->start(1000);
        break;
    }
    case  CMD_KILL:                                  //  Kill signal processing thread in each nodes.
    {
        LogFile(glbfileLog,"Receive CMD_KILL cmd.");
        stFrameHeader fh;
        fh.cmd = 0x05;
        fh.DATA_LEN = 0;
        QByteArray data((char *)&fh,sizeof(stFrameHeader));
        if (pserver->ClientsNum() > 0)
        {
            int nn = data.length();
            pserver->SendMsg(data.data(),data.length());
            strLog = "Send Kill_set CMD to GR Clients.";
            LogFile(glbfileLog,strLog);
        }
        else
        {
            strLog = "Watcher server is not connected by any GR client.";
            LogFile(glbfileLog,strLog);
        }
        break;
      /*  if (!KillProcess(glbExePythonPath))
        {
            strLog = "Error: Fail to kill process!!!" + glbExePythonPath;
            LogFile(glbfileLog,strLog);

        }
        else
        {
            strLog =  "Info: Kill process!!!";
            LogFile(glbfileLog,strLog);
            timer->stop();
        }
        break;*/
    }
    case  CMD_SETPARAM:                      //   Set system param by relaying *.xml
    {
        LogFile(glbfileLog,"Receive CMD_SETPARAM cmd!");
        char FileName[56];bool temp;
        memcpy(FileName,body,56);
        QString XMLFileName(FileName);
        XMLFileName = glbstrWorkDir + "/"  + XMLFileName;
        QFile paraFile(XMLFileName);
        QString strlog;
        if (!paraFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            strlog = "Error:Can't open" + XMLFileName +"file!!!" ;
            LogFile(glbfileLog,strLog);
            return ;
        }
        char *pdata = body;
        int fileLen = *(int *)(pdata + 56);
        pdata = pdata + 56 + sizeof(int);
        if (fileLen != paraFile.write(pdata,fileLen))
        {
            strLog =   "Error:Write param info failed!!!";
            LogFile(glbfileLog,strLog);
            paraFile.close();
            return;
        }
        else
        {
            strLog =   "Info:Write para info to para file successuflly!!!";
            LogFile(glbfileLog,strLog);
        }
        paraFile.close();
        stFrameHeader fh;
        fh.cmd = 0x04;
        fh.DATA_LEN = 0;
        QByteArray data((char *)&fh,sizeof(stFrameHeader));
        if (pserver->ClientsNum() > 0)
        {
            int nn = data.length();
            pserver->SendMsg(data.data(),data.length());
            strLog = "Send Param_set CMD to GR Clients.";
            LogFile(glbfileLog,strLog);
        }
        else
        {
            strLog = "Watcher server is not connected by any GR client.";
            LogFile(glbfileLog,strLog);
        }
        break;
    }
=======
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
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
    case  CMD_GETSTATUS:                     //   Get system status by relaying *.xml
        break;
    }

<<<<<<< HEAD
    temp = true;
    /*   qint16 cmd = header.cmd;
=======
 /*   qint16 cmd = header.cmd;
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
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
