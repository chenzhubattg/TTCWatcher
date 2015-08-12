#include "common.h"
#include <QTest>
#include <sstream>
#include <fstream>
#include <QRegExp>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <QSettings>
#include <QDir>
using namespace std;

const QString glbstrXMLParamFile = "Top_block_param.xml";
QString glbExeName = "top_block.py";
QString glbLocalAdress = "127.0.0.1";
int         glbLocalPort = 8010;
<<<<<<< HEAD
QString glbServerAdress = "192.168.0.110";
int         glbServerPort = 7002;
QString glbBlockPath = "~/TTCBlock";
QString glbLocalGRIDName = "top_block";
QString glbPyFileName =  glbLocalGRIDName + ".py";                                      //  "top_block_boxtest2.py";
QString glbExePyFile =      "EXE_" + glbPyFileName;                                          //  "top_block_boxtest_new.py";
QString glbExePythonPath;
QString XMLStatusFileName ;
bool temp = false;
=======
QString glbServerAdress = "127.0.0.1";
int         glbServerPort = 9010;
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1

QString glbstrWorkDir;
QFile glbfileLog;

void InitSystemParam()
{
    QDir dir = QDir::	current();
    QString sFile = "Option.ini";
<<<<<<< HEAD
   if (!dir.exists(sFile))
   {
       cout << "Info:Option.ini is not existed,the program will build a new Option.ini."<<endl;
      QSettings settings("Option.ini", QSettings::IniFormat); // 当前目录的INI文件
       settings.beginGroup("DevOption");
       settings.setValue("glbLocalAdress", glbLocalAdress);
       settings.setValue("glbLocalPort", glbLocalPort);
       settings.setValue("glbServerAdress", glbServerAdress);
       settings.setValue("glbServerPort", glbServerPort);
       settings.setValue("glbExeName", glbExeName);
       settings.endGroup();
   }
    QSettings settings("Option.ini", QSettings::IniFormat); // 当前目录的INI文件
    glbLocalAdress = settings.value("TTCWatcher/GRServerIpAdress").toString();
    glbLocalPort = settings.value("TTCWatcher/GRServerPort").toInt();
    glbServerAdress = settings.value("TTCServer/WatcherServerIpAdress").toString();
    glbServerPort = settings.value("TTCServer/WatcherServerPort").toInt();
    glbExeName = settings.value("DevOption/glbExeName").toString();
}

=======
    if (!dir.exists(sFile))
    {
        cout << "Info:Option.ini is not existed,the program will build a new Option.ini."<<endl;
        QSettings settings("Option.ini", QSettings::IniFormat); // 当前目录的INI文件
        settings.beginGroup("DevOption");
        settings.setValue("glbLocalAdress", glbLocalAdress);
        settings.setValue("glbLocalPort", glbLocalPort);
        settings.setValue("glbServerAdress", glbServerAdress);
        settings.setValue("glbServerPort", glbServerPort);
        settings.setValue("glbExeName", glbExeName);
        settings.endGroup();
    }

    QSettings settings("Option.ini", QSettings::IniFormat); // 当前目录的INI文件
    glbLocalAdress = settings.value("DevOption/glbLocalAdress").toString();
    glbLocalPort = settings.value("DevOption/glbLocalPort").toInt();
    glbServerAdress = settings.value("DevOption/glbServerAdress").toString();
    glbServerPort = settings.value("DevOption/glbServerPort").toInt();
    glbExeName = settings.value("DevOption/glbExeName").toString();
}
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
bool KillProcess(QString sName)
{
    QString RE = "\\d\\d:\\d\\d:\\d\\d python " +  sName; //  python top_block.py";
    QRegExp rgeexp(RE);
    system("ps -ef | grep python > peinfo &");
    QTest::qWait(1000);
    QFile file("peinfo");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Error:Can't find peinfo file!!!" << endl;
        return false;
    }
    bool bFindTopblock = false;
    QString strLine;
    while (!file.atEnd()) {
        strLine = QString(file.readLine());
        qDebug()<< strLine;
        if (strLine.contains(rgeexp))
        {
            bFindTopblock = true;
            break;
        }
    }
    if (!bFindTopblock)
    {
        cout << "Error:Can't find Radio Thread!!!" << endl;
        file.close();
        return false;
    }
    else
    {
        cout << "Info:Find Radio Thread!!!"<<endl;
        QStringList list1 = strLine.split(QRegExp("\\s+"));
        QString KillCmd = "kill -s 9 " + list1[1];
        cout << "Info:" << KillCmd.toStdString().c_str() << endl;
        system (KillCmd.toStdString().c_str());
        QTest::qWait(100);
        return true;
    }
}

void LogOut(QString strLog)
{
    cout << QTime::currentTime().toString("hh:mm:ss").toStdString().c_str() << " "<<strLog.toStdString().c_str() << endl;
}

void LogFile(QFile &file, QString strLog)
{
    if (!file.exists())
    {
        LogOut("Log file is not exist.");
        return;
    }
    strLog = QTime::currentTime().toString("hh:mm:ss.zzz ") + strLog + "\n";
    file.write(strLog.toStdString().c_str(),strLog.length());
    cout << strLog.toStdString().c_str();

}

<<<<<<< HEAD

//check if a file existed in a directionary,
//if the file dose not exested, the function will check it per 100 mseconeds until it existed or the time is more than nTime(mseconed).
bool FileExists(QString FileName,int nTime)
{
    int nWait = 0;
    while(nWait < nTime)
    {
        QTest::qWait(100);
        if (QFile::exists(FileName))
        {
            return true;
        }
        nWait += 100;
    }
    return false;
}

=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
