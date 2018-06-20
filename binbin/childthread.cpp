#include "childthread.h"
QMap<QString,int> map;
QTcpSocket* socketList[1024];

childThread::childThread(QObject *parent) : QThread(parent)
{

}

childThread::~childThread()
{

}

childThread::childThread(QTcpSocket *tcpsocket,QTextEdit *log)
{
    this->tcpSocket = tcpsocket;
    this->log = log;
}
void childThread::run()
{
    isStart = false;
    sendSize = 0;
    connect(tcpSocket, &QTcpSocket::readyRead, [=](){
       QByteArray array = tcpSocket->readAll();
       //log->append(QString(array));
       if(!isStart)
       {
           isStart = true;
           fileName = QString(array).section("##",0,0);
           fileSize = QString(array).section("##",1,1).toInt();
           temp = QString(array).section("##",2,2);
           log->append(QString(QString("文件传输给：").append(temp)));
           ip = temp.section(":",0,0);
           port = temp.section(":",1,1).toInt();
           tempSocket = socketList[map[temp]];
           tempSocket->write(array);
       }else{
           tempSocket->write(array);
           sendSize += array.length();
           //log->append(QString("传输：").append(QString(array)));
           if(sendSize == fileSize)
           {
               //QMessageBox::information(this,"ok","send ok");
                log->append(QString("文件传输成功！"));
           }
       }
    });
    connect(tcpSocket, &QTcpSocket::disconnected, [=](){
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        emit myDisconnect();
    });
}


