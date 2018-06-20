#ifndef CHILDTHREAD_H
#define CHILDTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTextEdit>

extern QMap<QString,int> map;
extern QTcpSocket* socketList[1024];


class childThread : public QThread
{
    Q_OBJECT
public:
    explicit childThread(QObject *parent = 0);
    childThread(QTcpSocket*,QTextEdit *);
    ~childThread();

signals:
    void myDisconnect();
protected:
    void run();
private:
    QTcpSocket *tcpSocket;
    QTextEdit *log;

    QString temp;
    QString ip;
    QString port;
    QTcpSocket *tempSocket;
    bool isStart;
    QString fileName;
    quint64 fileSize;
    quint64 sendSize;


public slots:
};

#endif // CHILDTHREAD_H
