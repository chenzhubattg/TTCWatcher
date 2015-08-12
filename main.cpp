#include <QCoreApplication>
#include <iostream>
#include "common.h"
#include "TCPServer.h"
#include"TCPClient.h"
#include <QDebug>
#include <QDir>
#include<QDateTime>
#include<QFile>
#include<QTextStream>
#include <QSettings>

#include <QList>
#include <QNetworkInterface>


using namespace std;
TCPServer *pserver;
TCPClient *pclient;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    QDir dirLog;
    QString strLogPath = QString("%1/WatcherLog").arg(QDir::currentPath());
    dirLog.mkdir(strLogPath);
    QString strLogName = QString("%1.wlog").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    strLogName = strLogPath + "/" + strLogName;
    glbfileLog.setFileName(strLogName);
    if (!glbfileLog.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered))
    {
        QString strLog("Creating log file is failure!");
        LogOut(strLog);
    }
    //make log directory
    QDir dirWork;
    glbstrWorkDir = QString("%1/WatcherWork").arg(QDir::currentPath());
    dirWork.mkdir(glbstrWorkDir);
    //system("cp ./Support/tcpclient.py ./WatcherWork/");

    QString strOptionFile = "Option.ini";
    QString strLog("Option.ini is not existed, the default params will be used.");
    QDir dir = QDir::	current();
    if (!dir.exists(strOptionFile))
    {
        LogFile(glbfileLog,strLog);
    }
    else
    {
        QSettings settings(strOptionFile, QSettings::IniFormat); // 当前目录的INI文件
        glbLocalAdress = settings.value("TTCWatcher/GRServerIpAdress").toString();
        glbLocalPort = settings.value("TTCWatcher/GRServerPort").toInt();
        glbServerAdress = settings.value("TTCServer/WatcherServerIpAdress").toString();
        glbServerPort = settings.value("TTCServer/WatcherServerPort").toInt();
        glbExeName = settings.value("DevOption/glbExeName").toString();
    }


    pserver = new TCPServer(NULL,glbLocalPort);
    pclient = new TCPClient(glbServerAdress,glbServerPort);
    return a.exec();
}
