#include "udphandler.h"

UdpHandler::UdpHandler(QVBoxLayout* vbox,QObject *parent) : QThread(parent)
{
    this->vbox = vbox;
    //this->udpChat = udpChat;
    index = 1;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4,5200,QUdpSocket::ReuseAddressHint);
    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.22"));
}
void UdpHandler::setUdpChat(QUdpSocket *udpChat)
{
    this->udpChat = udpChat;
}

void UdpHandler::run()
{

    connect(udpSocket, &QUdpSocket::readyRead,[=](){
        QByteArray array;
        while(udpSocket->hasPendingDatagrams())
        {
            array.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(array.data(),array.size());
            QString ret = QString(array);
            QString status = ret.section('#',0,0);
            QString address = ret.section('#',1,-1);

            if(status  == "connect" || status == QString("%1:%2")
                    .arg(udpSocket->localAddress().toString())
                    .arg(udpSocket->localPort()).toLatin1() )
            {
                map[address] = index;
                btn[index] = new QToolButton();
                btn[index]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
                btn[index]->setText(address);
                QString tmp = QString(":/new/prefix1/%1.png").arg(7);
                btn[index]->setIcon(QPixmap(tmp));
                btn[index]->setIconSize(QPixmap(tmp).size());
                btn[index]->setAutoRaise(true);
                vbox->insertWidget(0,btn[index]);
                thread[index] = new chatThread(udpChat,address);
                connect(btn[map[address]],&QToolButton::clicked,[=](){
                    thread[map[address]]->show();
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
