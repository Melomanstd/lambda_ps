#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QTimer>
#include "lambdadrv.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInerface();
    void on_resetSettings_clicked();
    void checkState();

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
    
private:
    Ui::MainWindow *ui;
    QTimer checkTimer;

    LambdaDrv *psDrvPtr;
};

#endif // MAINWINDOW_H
