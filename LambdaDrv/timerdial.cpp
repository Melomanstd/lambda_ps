#include "timerdial.h"

timerDial::timerDial(QWidget *parent) :
    QDial(parent)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(setTimer(int)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkStatus()));
}

void timerDial::checkStatus()
{
    emit newValue(value());
    timer.stop();
}

void timerDial::setTimer(int val)
{
    if (timer.isActive())
        timer.setInterval(300);
    else timer.start(300);
}
