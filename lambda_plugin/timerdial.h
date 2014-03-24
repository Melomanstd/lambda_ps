#ifndef TIMERDIAL_H
#define TIMERDIAL_H

#include <QDial>
#include <QTimer>

class timerDial : public QDial
{
    Q_OBJECT
public:
    explicit timerDial(QWidget *parent = 0);
    
signals:
    void newValue(int value);
    
public slots:
    void checkStatus();
    void setTimer(int val);

protected:
    QTimer timer;

};

#endif // TIMERDIAL_H
