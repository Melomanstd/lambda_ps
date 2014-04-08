#ifndef THREAD_H
#define THREAD_H

#include <QtCore>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "lambda_drv.h"

//class QueueItem;

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);
    void run();
    void sendingCommand(bool s);
    void setSocketIp(QString s);
    void processingQueue();
    void addCommand(int cmdNum, QString param);
    
signals:
    void stateUpdate(double par1, double par2, QString par3);
    void connectionLost();
    
public slots:
    void stopThread();
    void resumeThread();

protected:
    bool bStop;
    QMutex mutex;
    QWaitCondition m_wait;
    QString scIP;
//    QQueue<QueueItem*> queue;
};

//class QueueItem
//{
//public:
//    QueueItem(int c, QString s){cmdNum= c ; param = s;}

//    int cmdNum;
//    QString param;
//};

#endif // THREAD_H
