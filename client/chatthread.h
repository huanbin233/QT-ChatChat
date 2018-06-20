#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QWidget>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTimer>


namespace Ui {
class chatThread;
}

class chatThread : public QWidget
{
    Q_OBJECT

public:
    explicit chatThread(QUdpSocket*,QTcpSocket*, QString, QWidget *parent = 0);
    ~chatThread();
    void sendData();
private slots:
    void on_buttonSend_clicked();

    void on_buttonFile_clicked();
signals:
    void newMessage();
private:
    Ui::chatThread *ui;
    QTcpSocket *tcpSocket;
    QUdpSocket *socket;
    QString temp;
    bool isStart;

    QFile sendfile;
    QFile recfile;

    QString fileName;
    qint64 fileSize;
    qint64 sendSize;

    QString recFileName;
    qint64 recFileSize;
    qint64 recSize;


    QTimer timer;
};

#endif // CHATTHREAD_H
