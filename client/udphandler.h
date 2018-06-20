#ifndef UDPHANDLER_H
#define UDPHANDLER_H

#include <QMap>
#include <QThread>
#include <QUdpSocket>
#include "chatthread.h"
#include <QToolButton>
#include <QVBoxLayout>


class UdpHandler : public QThread
{
    Q_OBJECT
public:
    explicit UdpHandler(QVBoxLayout*,QObject *parent = nullptr);
     void setUdpChat(QUdpSocket*);
signals:
protected:
    void run();
public slots:
private:
    chatThread *thread[1024];
    QToolButton *btn[1024];
    QUdpSocket *udpChat;
    QUdpSocket *udpSocket;
    QVBoxLayout* vbox;
    QMap<QString,int> map;
    int index;

};

#endif // UDPHANDLER_H
