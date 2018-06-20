#include "chatthread.h"
#include "ui_chatthread.h"
chatThread::chatThread(QUdpSocket* udpChat,QTcpSocket* tcpSocket, QString temp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatThread)
{
    ui->setupUi(this);

    this->socket = udpChat;
    this->tcpSocket = tcpSocket;
    this->temp = temp;
    QString ip = temp.section(":",0,0);
    QString port = temp.section(":",1,1);
    isStart = false;

    ui->textEditReceive->append(QString("当前[%1:%2]")
                                .arg(socket->localAddress().toString())
                                .arg(socket->localPort()));

    ui->textEditReceive->append(QString("对方[%1:%2]")
                                .arg(ip)
                                .arg(port));

    //有其他用户消息到来
    connect(socket,&QUdpSocket::readyRead,[=](){
         QByteArray array;
         emit newMessage();
         while(socket->hasPendingDatagrams())
         {
             array.resize(socket->pendingDatagramSize());
             socket->readDatagram(array.data(),array.size());
             ui->textEditReceive->append(QString("对方:\n").append(QString(array)));
         }
    });

    connect(&timer,&QTimer::timeout,[=](){
       timer.stop();
       sendData();
    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=](){


        QByteArray array = tcpSocket->readAll();
        if(!isStart)
        {
            isStart = true;
            recSize = 0;
            recFileName = QString(array).section("##",0,0);
            recFileSize = QString(array).section("##",1,1).toInt();
            recfile.setFileName(recFileName);
            recfile.open(QIODevice::WriteOnly);

        }
        else
        {
            //ui->textEditReceive->append(QString("接受中:").append(array));

            qint64 len = recfile.write(array);
            recSize += len;
            if(recSize == recFileSize)
            {
                isStart = false;
                recfile.close();
                QMessageBox::information(this,"ok","receive ok");
            }
        }

    });
}

chatThread::~chatThread()
{
    delete ui;
}


void chatThread::on_buttonSend_clicked()
{
    if(socket == nullptr)
        return;
    QByteArray array = ui->textEditSend->toPlainText().toUtf8();
    ui->textEditSend->clear();
    QString ip = temp.section(":",0,0);
    QString port = temp.section(":",1,1);

    ui->textEditReceive->append(QString("我方:\n").toUtf8() + array);
    socket->writeDatagram(array,QHostAddress(ip),(quint16)(port.toInt()));
}

void chatThread::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    if(!filePath.isEmpty())
    {
        fileName.clear();
        fileSize = 0;
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();

        sendSize = 0;
        sendfile.setFileName(filePath);
        bool isOk = sendfile.open(QIODevice::ReadOnly);
        if(isOk)
        {
            QString str = QString("%1##%2##").append(temp).arg(fileName).arg(fileSize);
            qint64 len = tcpSocket->write( str.toUtf8());
            if(len > 0)
            {
                timer.start(50);
            }
            else
            {
                sendfile.close();
            }
        }
    }
}
void chatThread::sendData()
{
    qint64 len = 0;
    sendSize = 0;
    while(sendSize < fileSize)
    {
        char buf[10*1024] = {0};
        len = sendfile.read(buf,sizeof(buf));
        tcpSocket->write(buf,len);
        sendSize += len;
    }
    if(sendSize == fileSize)
    {
        QMessageBox::information(this,"ok","send ok");
        sendfile.close();
    }
}
