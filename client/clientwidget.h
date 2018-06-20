#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QPixmap>
#include <QList>
#include <QMap>
#include <QSet>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QGroupBox>
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <QThread>
#include "udphandler.h"
#include "chatthread.h"


namespace Ui {
class clientWidget;
}

class clientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientWidget(QWidget *parent = 0);
    ~clientWidget();
    //void setSocket(QTcpSocket *socket);
    void updateOnlineList();
    void deleteVBox();
private slots:


private:
    Ui::clientWidget *ui;

    QTcpSocket *toServerSocket;

    QString localIp;
    quint16 localPort;

    QList<QString> onlineList;
    QUdpSocket *udpSocket;
    QUdpSocket *udpChat;
    QUdpSocket *udpToServer;
    chatThread *thread[1024];
    QVBoxLayout *vbox;
    QMap<QString,int> map;
    QSet<QString> set;
    QString temp;
    QToolButton *btn[1024];

    UdpHandler *handler;
    int index;

};

#endif // CLIENTWIDGET_H
