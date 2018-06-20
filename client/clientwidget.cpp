#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
clientWidget::clientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientWidget)
{
    srand(time(0));
    ui->setupUi(this);
    setWindowTitle("ChatChat");


    vbox = new QVBoxLayout(ui->groupBoxOnline);
    vbox->addStretch();
    index = 1;

    //连接到服务器
    toServerSocket = new QTcpSocket(this);
    toServerSocket->connectToHost(QHostAddress("127.0.0.1"),5200);
    //udpsocket加入多播组
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4,5200,QUdpSocket::ReuseAddressHint);
    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.22"));
    //用来与其他客户端进行通信的套接字
    udpChat = new QUdpSocket(this);
    //handler = new UdpHandler(vbox);
    connect(toServerSocket, &QTcpSocket::connected,[=](){
        localIp = toServerSocket->localAddress().toString();
        localPort = toServerSocket->localPort();
        udpChat->bind(QHostAddress(localIp),localPort);
        temp = QString("%1:%2").arg(localIp).arg(localPort);
        ui->lineEditIp->setText(toServerSocket->localAddress().toString());
        ui->lineEditPort->setText(QString::number(toServerSocket->localPort()));   
    });

    connect(udpSocket, &QUdpSocket::readyRead,[=](){
        QByteArray array;
        while(udpSocket->hasPendingDatagrams())
        {
            array.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(array.data(),array.size());
            QString ret = QString(array);
            QString status = ret.section('#',0,0);
            QString address = ret.section('#',1,-1);
            QString localAddress = QString("%1:%2")
                    .arg(toServerSocket->localAddress().toString())
                    .arg(toServerSocket->localPort()).toLatin1();
            //qDebug() << address;
            if(status  == "connect" || status == localAddress)
            {
                if(address == localAddress)
                    continue;
                map[address] = index;
                btn[index] = new QToolButton(this);
                btn[index]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
                btn[index]->setText(address);
                QString tmp = QString(":/new/prefix1/%1.png").arg(7);
                btn[index]->setIcon(QPixmap(tmp));
                btn[index]->setIconSize(QPixmap(tmp).size());
                btn[index]->setAutoRaise(true);
                btn[index]->setStyleSheet("background-color:#FFFFFF");
                vbox->insertWidget(0,btn[index]);
                thread[index] = new chatThread(udpChat,toServerSocket,address);
                connect(btn[map[address]],&QToolButton::clicked,[=](){
                    btn[map[address]]->setStyleSheet("background-color:#FFFFFF");
                    thread[map[address]]->show();
                });
                connect(thread[map[address]], &chatThread::newMessage,[=](){
                    btn[map[address]]->setStyleSheet("background-color:#FF0000");
                });
                index ++;
            }
            else if(status == "disconnect")
            {
               if(map[address] > 0){
                   vbox->removeWidget(btn[map[address]]);
                   delete btn[map[address]];
                   delete thread[map[address]];
               }
            }
        }

    });




}

void clientWidget::deleteVBox()
{
    for(int i =0;i < index;i ++) {
        vbox->removeWidget(btn[i]);
        delete btn[i];
    }
}

void clientWidget::updateOnlineList()
{
    for(int i = 0;i < index;i ++){
        vbox->insertWidget(0,btn[i]);
    }
}

clientWidget::~clientWidget()
{
    delete ui;

}
/*
void clientWidget::setSocket(QTcpSocket *socket)
{
    this->toServerSocket =  socket;

    localIp = toServerSocket->localAddress().toString();
    localPort = toServerSocket->localPort();


    //udpToServer->bind(QHostAddress(localIp),localPort);

    temp = QString("%1:%2").arg(localIp).arg(localPort);

    ui->lineEditIp->setText(toServerSocket->localAddress().toString());
    ui->lineEditPort->setText(QString::number(toServerSocket->localPort()));
}*/

