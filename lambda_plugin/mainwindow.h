#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtGui/QMainWindow>

#include <QMainWindow>
#include <QTextCodec>
#include <QTimer>
#include <QTranslator>
//#include "lambdadrv.h"
//#include "lambda_drv.h"
#include "thread.h"
#include "corethread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(CoreThread *core=0, bool limFunc = false, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void testSlot();

    void connectionLost();
    void startConnection(bool state);

    void blockUI(bool s);

    void connectClicked();
    void updateInerface();
    void on_resetSettings_clicked();
    void checkState();
    void checkOutputState(QueueItem &item);
    void checkFoldbackState(QueueItem &item);
    void checkStartMode(QueueItem &item);
    void checkOperationMode(QueueItem &item);
    void checkOverVolt(QueueItem &item);
    void checkUnderVolt(QueueItem &item);
    void stateUpdated(double par1, double par2, QString par3);

    void on_volt_dial_valueChanged(int val);
    void on_underVolt_valueChanged(double val);
    void on_overVolt_valueChanged(double val);
    void on_volt_output_valueChanged(double val);

    void on_curr_dial_valueChanged(int val);
//    void on_underCurrent_valueChanged(double val);
//    void on_overCurrent_valueChanged(double val);
    void on_curr_output_valueChanged(double val);

    void on_outputStateBtn_clicked();
    void on_oper_mode_combo_currentIndexChanged(int index);
    void on_foldback_btn_clicked();
    void on_power_up_combo_currentIndexChanged(int index);
    
public:
    QTranslator translator;
    double voltage, current;
    double underVoltLimit, overVoltLimit;

private:
    Ui::MainWindow *ui;
    QTimer checkTimer;
    CoreThread/*Thread*/ *thr;
    bool connected;
    bool volt_updated;
    bool curr_updated;
    QWaitCondition m_wait;
    QMutex mutex;
    bool limFunc;



//    LambdaDrv *psDrvPtr;
};

#endif // MAINWINDOW_H
