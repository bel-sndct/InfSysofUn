#include "mainwindow.h"
#include "keypress.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPalette pal;
    QColor *clr = new QColor(121, 190, 201);
    pal.setColor(QPalette::Window,*clr);
    a.setPalette(pal);
    MainWindow w;
    w.setFixedSize(1300, 680);
    w.show();
    w.setWindowTitle("Информационная система деканата");
    return a.exec();
}
