#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include "clientwidget.h"
namespace Ui {
class loginWidget;
}

class loginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit loginWidget(QWidget *parent = 0);
    ~loginWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::loginWidget *ui;
    QTcpSocket *toServerSocket;

    QString serverIp;
    quint64 serverPort;
    clientWidget w;
};

#endif // LOGINWIDGET_H
