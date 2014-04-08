#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    pCore=new Core()
    CoreThread *pCore = new CoreThread;

    MainWindow w(pCore);
    w.show();
    
    return a.exec();
}
