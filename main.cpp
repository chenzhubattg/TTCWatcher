#include <QCoreApplication>
#include <iostream>
#include "common.h"
#include "TCPServer.h"
#include"TCPClient.h"
#include <QDebug>
#include <QDir>
#include<QDateTime>

using namespace std;
TCPServer *pserver;
TCPClient *pclient;

int main(int argc, char *argv[])
{
  //  InitSystemParam();
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

    QDir dirWork;
    glbstrWorkDir = QString("%1/WatcherWork").arg(QDir::currentPath());
    dirWork.mkdir(glbstrWorkDir);

    //pserver = new TCPServer(NULL,glbLocalPort);
    glbServerPort = 7002;
    pclient = new TCPClient(glbServerAdress,glbServerPort);
    return a.exec();
}
