#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QDebug>
tcpServer::tcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcpServer)
{
    ui->setupUi(this);
    setWindowTitle("服务器");
    server = new QTcpServer(this);

    udpSocket = new QUdpSocket(this);
    index = 0;

    connect(server, &QTcpServer::newConnection, [=](){
       socketList[index] = server->nextPendingConnection();
       QString ip = socketList[index]->peerAddress().toString().replace(QRegExp("[^0-9.]"),"");
       quint16 port = socketList[index]->peerPort();

       QString clnt  = QString("%1:%2").arg(ip).arg(port);
       QString temp = QString("[%1:%2] 连接成功!").arg(ip).arg(port);

       map[clnt] = index;
       qDebug() << map.size();
       //map[clnt] = tcpSocket;
       ui->textEditLog->append(temp);

        //组播这个在线列表
       QString clnt_con = QString("connect#%1:%2").arg(ip).arg(port);
       QString clnt_dis = QString("disconnect#%1:%2").arg(ip).arg(port);
       foreach (QString str, clientList) {
           udpSocket->writeDatagram(((QString("%1:%2#").arg(ip).arg(port)).append(str)).toUtf8(),QHostAddress("224.0.0.22"),5200);
       }
       udpSocket->writeDatagram(clnt_con.toLatin1().data(),QHostAddress("224.0.0.22"),5200);

       clientList.push_back(clnt);
       changeOnlineTextEdit();
        //为每个客户端创建一个子线程去处理
       childThread *thread = new childThread(socketList[index],ui->textEditLog);
       thread->start();

       connect(thread,&childThread::myDisconnect,[=]{
           thread->quit();
           thread->wait();
           map.remove(clnt);
           clientList.removeOne(clnt);
           changeOnlineTextEdit();
           ui->textEditLog->append(QString("[%1:%2] 断开连接!").arg(ip).arg(port));
           udpSocket->writeDatagram(clnt_dis.toLatin1().data(),QHostAddress("224.0.0.22"),5200);
       });
       index ++;
    });

}

void tcpServer::broadcastDatagram(QString clnt)
{
    foreach (QString str, clientList) {
        udpSocket->writeDatagram((clnt.append(str)).toUtf8(),QHostAddress("224.0.0.22"),5200);
        //qDebug() << clnt.append(str);
    }
}

tcpServer::~tcpServer()
{
    delete ui;
}

void tcpServer::changeOnlineTextEdit()
{
    ui->textEditOnline->clear();
    foreach (QString str, clientList) {
        ui->textEditOnline->append(str);
    }
}

void tcpServer::on_buttonStart_clicked()
{
    server->listen(QHostAddress::Any,5200);
    ui->lineEditState->setText("running");
}


