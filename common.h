#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <QString>
#include<QFile>

<<<<<<< HEAD
#pragma pack(push)
#pragma pack(1)
=======

>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1

using namespace std;
extern const QString glbstrXMLParamFile;
extern  QString glbExeName;

extern QString glbLocalAdress;
extern int         glbLocalPort;
extern QString glbServerAdress;
extern int         glbServerPort;
extern QString glbstrWorkDir;   //Save XML and GRC File
extern QFile glbfileLog;
<<<<<<< HEAD
extern QString glbLocalGRIDName;
extern QString glbBlockPath;
extern QString glbPyFileName;
extern QString glbExePyFile;
extern QString glbExePythonPath;
extern QString XMLStatusFileName ;
extern bool temp;
=======

>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
/*const int CMD_LOAD = 0x0001;
const int CMD_LOAD_RES = 0x0101;
const int CMD_START = 0x0002;
const int CMD_START_RES = 0x0102;
const int CMD_STOP = 0x0003;
const int CMD_STOP_RES = 0x0203;
const int CMD_SET = 0x0004;
const int CMD_SET_RES = 0x0104;
const int CMD_KILL = 0x0005;
const int CMD_KILL_RES = 0x0105;
*/

const int  CMD_LOAD = 0x01;                               //  Load *.grc and *.xml of flow graph
const int  CMD_START = 0x02           ;                  //  Running signal processing program in each nodes.
const int CMD_KILL = 0x03              ;                    //  Kill signal processing thread in each nodes.
const int CMD_SETPARAM = 0x04  ;                    //   Set system param by relaying *.xml
const int CMD_GETSTATUS = 0x05;                     //   Get system status by relaying *.xml



//TODO
class CpuInfo{
public:
    int CpuNum;
    string name;
    string CapOfCache;
    string freq;
};



//GNU <===============================> Watcher
//FALG = "RRSI"
// cmd = 0x0001   load python file               g<==w
// cmd = 0x0101   reply 0x0001                    g==>w
// cmd = 0x0002   start graph                       g<==w
// cmd = 0x0102   reply 0x0002                    g==>w
// cmd = 0x0003   stop graph                       g<==w
// cmd = 0x0103   reply 0x0003                    g==>w
// cmd = 0x0004   set param                         g<==w
// cmd = 0x0204   reply 0x0004                    g==>w





class stFrameHeader
{
public:
    stFrameHeader()
    {
        FLAG[0] = 'M';
        FLAG[1]= 'M';
        FLAG[2]='X';
        FLAG[3] = 'H';
        cmd = 0x11;
    }
    char FLAG[4];
<<<<<<< HEAD
    qint32 DATA_LEN;
=======
    qint16 DATA_LEN;
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
    qint16 cmd;
};//head for msg

class stSetParamMsg
{
public:
    stSetParamMsg()
    {

    }
    char filename[56];
    char *pdata;
};


class stNodeInfo
{
public:
    stNodeInfo()
    {
       memset(&strHostname,0,32);
       memset(&strCPUName,0,32);
//       memset(&I_D,0,3);
//       memset(&Msg,0,sizeof(Msg));
//       Monitor[0] = 'R'; Monitor[1]='I'; Monitor[2]='M';
       nCoreNum = 0;
//       nMem = 0;
    }
//    QString Msg;
//    char Monitor[3];
//    char I_D[3];
    char strHostname[32];
    char strCPUName[32];
    int     nCoreNum;
//    int     nMem;
};      // ID : 000 001 010 011 100  101 110 111
extern bool KillProcess(QString sName);
extern void InitSystemParam();
extern void LogOut(QString strLog);
extern void LogFile(QFile &file, QString strLog);
<<<<<<< HEAD
extern bool FileExists(QString FileName,int nTime);
#pragma pack(pop)
=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
#endif  // DATACLASS

