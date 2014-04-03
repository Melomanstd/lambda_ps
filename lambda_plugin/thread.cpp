#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{
    bStop = false;
}

void Thread::run()
{
    bStop = false;
    double par1=0;
    double par2=0;
    QString par3;
    while(!bStop)
    {
//        QString sss = QString(FIRMWARE_REVISION_F());
//        if (sss.isEmpty())
//        {
//            emit connectionLost();
//            return;
//        }
        par1 = QString(MEAS_VOLTAGE_F()).toDouble();
        msleep(100);
        par2 = QString(MEAS_CURRENT_F()).toDouble();
        msleep(100);
        par3 = QString(READ_CONSTANT_MODE_F());
//        qDebug()<<par3;
        msleep(100);
        emit stateUpdate(par1, par2, par3);
        msleep(500);
    }
}

void Thread::stopThread()
{
    mutex.lock();
    bStop = true;
    mutex.unlock();
}
