#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QList>
#include <QSet>
#include <QMap>
#include <QUdpSocket>
#include "childthread.h"
namespace Ui {
class tcpServer;
}

class tcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit tcpServer(QWidget *parent = 0);
    ~tcpServer();
    void changeOnlineTextEdit();
    void broadcastDatagram(QString);
private slots:



    void on_buttonStart_clicked();



private:
    Ui::tcpServer *ui;


    QUdpSocket *udpSocket;

    QTcpServer *server;
    QList<QString> clientList;

    int index;

};

#endif // TCPSERVER_H
