#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    QStringList items;

    psDrvPtr = new LambdaDrv;
    psDrvPtr->openSocket(QString("192.168.1.105"), QString("8003"));
//    qDebug()<<psDrvPtr->FIRMWARE_REVISION_F();
//    qDebug()<<psDrvPtr->SET_VOLT_LIMIT_F(18);
//    psDrvPtr->GET_UNDERVOLT_LIMIT_F();
//    qDebug()<<psDrvPtr->GET_VOLT_LIMIT_F();

    items.clear();
    items.append(tr("LOC"));
    items.append(tr("REM"));
    items.append(tr("LLO"));
    ui->oper_mode_combo->addItems(items);

    items.clear();
    items.append(tr("Safe start"));
    items.append(tr("Auto restart"));
    ui->power_up_combo->addItems(items);

//    qDebug()<<"";
//    o.readSomething();
//    psDrvPtr->GET_OUTPUT_STATE_F();
//    psDrvPtr->MEAS_VOLTAGE_F();
//    psDrvPtr->READ_CONSTANT_MODE_F();
//    psDrvPtr->GET_SETTING_MODE_F();
//    psDrvPtr->MEAS_CURRENT_F();
    psDrvPtr->GET_START_MODE_F();
    updateInerface();

    checkTimer.start(500);

    connect(&checkTimer, SIGNAL(timeout()), this, SLOT(checkState()));
}

MainWindow::~MainWindow()
{   
    psDrvPtr->closeSocket();
    delete ui;
}

void MainWindow::updateInerface()
{
    int max, t;
    t = psDrvPtr->GET_UNDERVOLT_LIMIT_F().toDouble()*5;
    ui->volt_dial->setMinimum(t);
    t = qRound(psDrvPtr->GET_OVERVOLT_PROTECTION_F().toDouble())*5;
    max = qRound(psDrvPtr->GET_OVERVOLT_PROTECTION_F().toDouble())*100;
    ui->volt_dial->setMaximum(max-t);
    ui->underVolt->setValue(psDrvPtr->GET_UNDERVOLT_LIMIT_F().toDouble());
    ui->overVolt->setValue(psDrvPtr->GET_OVERVOLT_PROTECTION_F().toDouble());
    ui->volt_dial->setValue(psDrvPtr->GET_VOLT_LIMIT_F().toDouble()*100);
    ui->curr_dial->setValue(psDrvPtr->GET_CURR_LIMIT_F().toDouble()*100);
//    ui->volt_dial->setValue(qRound(psDrvPtr->GET_VOLT_LIMIT_F().toDouble()*100));

}

void MainWindow::on_resetSettings_clicked()
{
//    psDrvPtr->SET_UNDERVOLT_LIMIT_F(2);
    psDrvPtr->RESET_PS_SETTINGS_F();
    updateInerface();
}

void MainWindow::checkState()
{
    ui->voltage_output_lcd->display(psDrvPtr->MEAS_VOLTAGE_F().toDouble());
    ui->current_output_lcd->display(psDrvPtr->MEAS_CURRENT_F().toDouble());
    ui->const_mode_lbl->setText(psDrvPtr->READ_CONSTANT_MODE_F());
    psDrvPtr->SET_VOLT_LIMIT_F(ui->volt_output->value());
    psDrvPtr->SET_CURR_LIMIT_F(ui->curr_output->value());
}

void MainWindow::on_volt_dial_valueChanged(int val)
{
    ui->volt_output->setValue((double) val/100);
}

void MainWindow::on_underVolt_valueChanged(double val)
{
    psDrvPtr->SET_UNDERVOLT_LIMIT_F(val);
//    int t = qRound(val*100);
    ui->volt_dial->setMinimum(qRound(val*5));
}

void MainWindow::on_overVolt_valueChanged(double val)
{
    psDrvPtr->SET_OVERVOLT_PROTECTION_F(val);
    int t = qRound(val*100);
    ui->volt_dial->setMaximum(t-qRound(val*5));
    ui->volt_dial->setNotchTarget(ui->volt_dial->maximum()/10);
}

void MainWindow::on_volt_output_valueChanged(double val)
{
    ui->volt_dial->setValue(val*100);
//    psDrvPtr->SET_VOLT_LIMIT_F(val);
}

//--------------------------------

void MainWindow::on_curr_dial_valueChanged(int val)
{
    ui->curr_output->setValue((double) val/100);
}

void MainWindow::on_curr_output_valueChanged(double val)
{
    ui->curr_dial->setValue(val*100);
//    psDrvPtr->SET_CURR_LIMIT_F(val);
}

//---------------------------------

void MainWindow::on_outputStateBtn_clicked()
{
    psDrvPtr->SET_OUTPUT_STATE_F(ui->outputStateBtn->isChecked());
}

void MainWindow::on_oper_mode_combo_currentIndexChanged(int index)
{
    psDrvPtr->SET_SETTING_MODE_F(index);
}

void MainWindow::on_foldback_btn_clicked()
{
    psDrvPtr->SET_FOLDBACK_PROTECTION_F(ui->foldback_btn->isChecked());
}

void MainWindow::on_power_up_combo_currentIndexChanged(int index)
{
    psDrvPtr->SET_START_MODE_F(index);
}
