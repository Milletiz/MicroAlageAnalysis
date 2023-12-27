#include "mainwindow.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/Combinear.qss");
    if(qss.open(QFile::ReadOnly))

    {
        qDebug()<<endl<<"open success";
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else
    {
        qDebug()<<endl<<"Open failed";
    }
    MainWindow w;
    w.show();
    return a.exec();
}
