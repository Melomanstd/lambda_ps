#ifndef CORETHREAD_H
#define CORETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QWaitCondition>
#include "lambda_drv.h"

class QueueItem;

class CoreThread : public QThread
{
    Q_OBJECT
public:
    explicit CoreThread(QObject *parent = 0);
    ~CoreThread();
    
    void run();
    int startThread(QString ip, QString port);
    void stopThread();
    void resumeThread();
    double getVoltage();
    double getCurrent();
    void addRequest(QueueItem *item);

signals:
//    void dataUpdate(QString volt, QString curr);
    void connectionLost();
    void socketState(bool s);
    
public slots:
    void processingQueue();

public:
    double voltage, current;
    double uVolt, oVolt;
    
protected:
    bool bStop;
    QWaitCondition m_wait;
    QMutex mutex;
    QQueue<QueueItem*> queue;
    QString ip, port;
    bool startedFromGUI;
};

class QueueItem
{
public:
    QueueItem(int c, QString s){cmdNum= c ; param = s;}

    QWaitCondition wait;
    int cmdNum;
    QString param;
    QString result;
};
#endif // CORETHREAD_H
