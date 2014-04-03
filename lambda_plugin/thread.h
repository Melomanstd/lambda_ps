#ifndef THREAD_H
#define THREAD_H

#include <QtCore>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "lambda_drv.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);
    void run();
    
signals:
    void stateUpdate(double par1, double par2, QString par3);
    void connectionLost();
    
public slots:
    void stopThread();

protected:
    bool bStop;
    QMutex mutex;
    QWaitCondition m_wait;
};

#endif // THREAD_H
