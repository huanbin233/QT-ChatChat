#include "loginwidget.h"
#include "ui_loginWidget.h"


#include <QDebug>

loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWidget)
{
    ui->setupUi(this);

    serverIp = "127.0.0.1";
    serverPort = 5200;


    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/new/prefix1/timg.png").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图


    toServerSocket = new QTcpSocket(this);

    /*connect(toServerSocket, &QTcpSocket::connected,[=](){
        this->hide();
        w.setSocket(toServerSocket);
        w.show();
    });*/
}

loginWidget::~loginWidget()
{
    delete ui;
}

void loginWidget::on_pushButton_clicked()
{
    toServerSocket->connectToHost(QHostAddress(serverIp),serverPort);
}
