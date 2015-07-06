#include "TTCWatcher.h"
#include "ui_TTCWatcher.h"
#include <QDebug>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <string.h>
#include <sys/statfs.h>
#include <stdlib.h>

#include <QDir>
#include <QMessageBox>
#include "common.h"
#include "/usr/include/python2.7/Python.h"

using namespace std;

/*Global Object Variables Declaration*/
CpuInfo cpu_info;
QString localHostName, localHostIp;

/*Function Front Declaration*/
extern void TestCpuInfo();

QList<CpuInfo> Cpulist; //LIST



TTCWatcher::TTCWatcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TTCWatcher)
{
    ui->setupUi(this);

    /*get info*/
    getHostinfo();
    TestCpuInfo();
//    collectinfo();
    /*client*/
    status = false;

    port = 8010;
    ui->P_ort->setText(QString::number(port));

    serverIP =new QHostAddress();

    connect(ui->Join_in,SIGNAL(clicked()),this,SLOT(slotEnter()));
    connect(ui->Send_info,SIGNAL(clicked()),this,SLOT(slotSend()));

}

TTCWatcher::~TTCWatcher()
{
    delete ui;
}

void TTCWatcher::getHostinfo()
{
    localHostName = QHostInfo::localHostName();
    ui->Host_name->setText(localHostName);
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.isEmpty())
    {
        ui->Ip_localaddress->setText(listAddress.first().toString());
    }
}

void TestCpuInfo()
{
    //getcpuinfo
    ifstream infile("/proc/cpuinfo");
    string word;
    cpu_info.CpuNum = 0;

    while(infile>>word)
    {
        if(word=="processor")
        {
            cpu_info.CpuNum++;
            continue;
        }

        if(word=="vendor_id")
        {
            infile>>word;
            infile>>word;
            cpu_info.name = word;
            continue;
        }
        if(word=="MHz")
        {
            infile>>word;
            infile>>word;
            cpu_info.freq = word;
            //QString st(cpu_info.freq);
 //           qDebug() << QString::fromStdString(cpu_info.freq);
            continue;
        }
        /*kylin changed to other databases*/
        if(word=="cache")
        {
            infile>>word;
            infile>>word;
            infile>>word;
            cpu_info.CapOfCache = word+" KB";
//            Centerpu.insert(cpu_info);  //read info in list
            Cpulist.append(cpu_info);
            continue;
        }

       // qDebug()<<QString::fromStdString(Centerpu.next().freq);
        /*continue*/
    }
}

void TTCWatcher::slotEnter()
{
    if(!status)
    {
        QString ip = ui->Ip_address->text();
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(this,tr("error"),tr("server ip address error!"));
            return;
        }
        if(ui->Host_name->text()=="")
        {
            QMessageBox::information(this,tr("error"),tr("User name error!"));
            return;
        }
        userName=localHostName;
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
        connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
        tcpSocket->connectToHost(*serverIP,port);
        status=true;
    }
    else
    {
        int length=0;
        QString msg=userName+tr(":Disconnected");
        if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg. length())
        {
            return;
        }

        tcpSocket->disconnectFromHost();

        status=false;
    }
}

void TTCWatcher::slotConnected()
{
//    sendBtn->setEnabled(true);
//    stNodeInfo nodeinfo;
    /*
    stFrameHead_msg FrameHead_msg;
    ui->Join_in->setText(tr("left"));

    int length=0;
    QString msg=userName+tr(":Join in!");
    sizeof_msg = sizeof(msg);
    char *pdata = new char[sizeof(stFrameHead_msg) + sizeof_msg];
    memcpy(pdata,&FrameHead_msg,sizeof(stFrameHead_msg));
//    char  *p = pdata;
//    p += sizeof(stFrameHead_msg);
    memcpy((pdata+sizeof(stFrameHead_msg)),&msg,sizeof_msg);

//    QString msg=userName+tr(":Join in!");
//    tcpSocket->write((char *)&nodeinfo,sizeof(stNodeInfo));
   if((length=tcpSocket->write(pdata+sizeof(stFrameHead_msg),sizeof_msg))!=sizeof_msg)
  {
      return;
  }

   delete [] pdata;*/
}

void TTCWatcher::slotDisconnected()
{
//    sendBtn->setEnabled(false);
    ui->Join_in->setText(tr("Join!!"));
}

void TTCWatcher::slotSend()
{
    stNodeInfo nodeinfo;
    stFrameHeader FrameHead;

//    QString temp=QString::number(cpu_info.CpuNum);
    memcpy(&nodeinfo.strHostname,localHostName.toStdString().c_str(), localHostName.length());
    memcpy(&nodeinfo.strCPUName,cpu_info.name.c_str(), cpu_info.name.length());
    nodeinfo.nCoreNum = cpu_info.CpuNum;
//    nodeinfo.I_D={'0','0','1'};

    char *pdata = new char[sizeof(stFrameHeader) + sizeof(stNodeInfo)];
    memcpy(pdata,&FrameHead,sizeof(stFrameHeader));
//    char  *p = pdata;
//    p += sizeof(stFrameHead);
    memcpy((pdata+sizeof(stFrameHeader)),&nodeinfo,sizeof(stNodeInfo));

//    strcpy(nodeinfo.I_D, "001");//Add ID signal.

//    QString msg="@_@"+localHostName+"$"+QString::fromStdString(cpu_info.name)+"$"+temp;
//    tcpSocket->write(msg.toLatin1(),msg.length());

//    QString msg=userName+":"+sendLineEdit->text();

 //    tcpSocket->write(msg.toLatin1(),msg.length());
//    tcpSocket->write((char *)&nodeinfo,sizeof(stNodeInfo));
    tcpSocket->write(pdata, sizeof(stNodeInfo)+sizeof(stFrameHeader));
    ui->Send_info->setEnabled(false);
    delete [] pdata;
}

void TTCWatcher::dataReceived()
{
    QByteArray block ;
    while(tcpSocket->bytesAvailable())
    {
        block.append(tcpSocket->readAll());
        char *p = block.data();
        char *q = p + block.size();
        while (true)
        {
            if( (p - q) < sizeof(stFrameHeader) )
                break;
            stFrameHeader head;
            qDebug() << "headSize:"  << sizeof(stFrameHeader);
            memcpy(&head, p, sizeof(stFrameHeader));
            if(head.FLAG[0] != 'R' || head.FLAG[1] != 'R' || head.FLAG[2] != 'S' || head.FLAG[3] != 'I')
            {
                p = q;
                break;
            }
            if( (p - q) < (sizeof(stFrameHeader) + head.DateLen) )
                break;
            readMsgBody(head, p + sizeof(head), head.DateLen);
            p += sizeof(stFrameHeader)+head.DateLen;
        }
        block = block.right( q - p);
    }
}

#define CMD_EXECUTEPY 0x01
#define CMD_PARAM 0x02
void TTCWatcher::readMsgBody(stFrameHeader &head, char *body, int bodyLength)
{
    unsigned int BID = head.BID;
    char *pdata = body + sizeof(unsigned int);
    int     nDataLen = bodyLength -  sizeof(unsigned int);
    switch (BID)
    {
    case CMD_EXECUTEPY:
        RunningPy("top_block.py");
        //connect top_block.py

        break;
    case CMD_PARAM:
        QFile fileXMLParam(glbstrXMLParamFile);
        if (!fileXMLParam.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            cout << "Error: "<< glbstrXMLParamFile.toStdString().c_str() << "is not created correctly!" << endl;
            return;
        }
        if (nDataLen != fileXMLParam.write(pdata,nDataLen))
        {
            cout << "Error: Write file failure!";
        }
        fileXMLParam.close();
        SendMsgToGraph()
        break;
    }
}

void TTCWatcher::RunningPy(QString strFileName)
{
    int n = 0;
    QString strExe = QString("execfile('%1')").arg(strFileName);
    Py_Initialize();
    n = PyRun_SimpleString(strExe.toStdString().c_str());
    Py_Finalize();
}

void TTCWatcher::on_pushButton_clicked()
{
    QString strFileName("/home/radio/Test/CplusPython/top_block.py");
    RunningPy(strFileName);
}

void TTCWatcher::SendTask(int nCMD)
{

}

void TTCWatcher::slotCreateServer()
{
    server = new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));

    CreateBtn->setEnabled(false);
}

void TTCWatcher::updateServer(QString msg,int length)
{
    ContentListWidget->addItem(msg.left(length));
}
