#include "clientwidget.h"
#include <QApplication>
#include "loginwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    clientWidget w;
    w.show();

    return a.exec();
}
