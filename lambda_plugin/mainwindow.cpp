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

    volt_updated = false;
    curr_updated = false;
    connected = false;

    QStringList items;

//    openSocket("192.168.1.105", "8003");
//    psDrvPtr = new LambdaDrv;
//    psDrvPtr->openSocket(QString("192.168.1.105"), QString("8003"));
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
//    psDrvPtr->GET_START_MODE_F();
//    updateInerface();

    thr = new Thread;
//    checkTimer.start(500);

    connect(ui->connect_btn, SIGNAL(clicked()), this, SLOT(connectClicked()));
    connect(&checkTimer, SIGNAL(timeout()), this, SLOT(checkState()));
    connect(thr, SIGNAL(stateUpdate(double,double,QString)), this, SLOT(stateUpdated(double,double,QString)));
    connect(thr, SIGNAL(connectionLost()), this, SLOT(connectionLost()));
//    thr->start();
}

MainWindow::~MainWindow()
{   
//    psDrvPtr->closeSocket();
    closeSocket();
    delete ui;
}

void MainWindow::connectClicked()
{
    if (!connected)
    {
        QByteArray ip = ui->ip_edit->text().toAscii();
        int state = openSocket(ip.data(), "8003");
        if (state<0) return;
        updateInerface();
        connected = true;
        thr->start();
        ui->connect_btn->setText("Disconnect");
    }
    else
    {
        closeSocket();
        connected = false;
        thr->stopThread();
        ui->connect_btn->setText("Connect");
    }
}

void MainWindow::updateInerface()
{
    if (!connected) return;
    int max, t;
    t = QString(GET_UNDERVOLT_LIMIT_F()).toDouble()*5;//psDrvPtr->GET_UNDERVOLT_LIMIT_F().toDouble()*5;
    ui->volt_dial->setMinimum(t);
    //t = qRound(psDrvPtr->GET_OVERVOLT_PROTECTION_F().toDouble())*5;
    t = qRound(QString(GET_OVERVOLT_PROTECTION_F()).toDouble())*5;
//    max = qRound(psDrvPtr->GET_OVERVOLT_PROTECTION_F().toDouble())*100;
    max = qRound(QString(GET_OVERVOLT_PROTECTION_F()).toDouble())*100;
    ui->volt_dial->setMaximum(max-t);
    ui->underVolt->setValue(QString(GET_UNDERVOLT_LIMIT_F()).toDouble());//(psDrvPtr->GET_UNDERVOLT_LIMIT_F().toDouble());
    ui->overVolt->setValue(QString(GET_OVERVOLT_PROTECTION_F()).toDouble());//psDrvPtr->GET_OVERVOLT_PROTECTION_F().toDouble());
    ui->volt_dial->setValue(QString(GET_VOLT_LIMIT_F()).toDouble()*100);//psDrvPtr->GET_VOLT_LIMIT_F().toDouble()*100);
    ui->curr_dial->setValue(QString(GET_CURR_LIMIT_F()).toDouble()*100);//psDrvPtr->GET_CURR_LIMIT_F().toDouble()*100);
//    ui->volt_dial->setValue(qRound(psDrvPtr->GET_VOLT_LIMIT_F().toDouble()*100));

}

void MainWindow::on_resetSettings_clicked()
{
//    psDrvPtr->SET_UNDERVOLT_LIMIT_F(2);
//    psDrvPtr->RESET_PS_SETTINGS_F();
    if (!connected) return;
    RESET_PS_SETTINGS_F();
    updateInerface();
}

void MainWindow::checkState()
{
//    ui->voltage_output_lcd->display(QString(MEAS_VOLTAGE_F()).toDouble());//psDrvPtr->MEAS_VOLTAGE_F().toDouble());
//    ui->current_output_lcd->display(QString(MEAS_CURRENT_F()).toDouble());//psDrvPtr->MEAS_CURRENT_F().toDouble());
//    ui->const_mode_lbl->setText(QString(READ_CONSTANT_MODE_F()));//psDrvPtr->READ_CONSTANT_MODE_F());
//    psDrvPtr->SET_VOLT_LIMIT_F(ui->volt_output->value());
//    psDrvPtr->SET_CURR_LIMIT_F(ui->curr_output->value());
//    SET_VOLT_LIMIT_F(ui->volt_output->value());
//    SET_CURR_LIMIT_F(ui->curr_output->value());
}

void MainWindow::stateUpdated(double par1, double par2, QString par3)
{
    if (!connected) return;

    if(volt_updated)
    {
        SET_VOLT_LIMIT_F(ui->volt_output->value());
        volt_updated = false;
    }
    if(curr_updated)
    {
        SET_CURR_LIMIT_F(ui->curr_output->value());
        curr_updated = false;
    }
    voltage = par1;
    current = par2;
    ui->voltage_output_lcd->display(par1);//psDrvPtr->MEAS_VOLTAGE_F().toDouble());
    ui->current_output_lcd->display(par2);//psDrvPtr->MEAS_CURRENT_F().toDouble());
    ui->const_mode_lbl->setText(par3.trimmed());//psDrvPtr->READ_CONSTANT_MODE_F());
}

void MainWindow::on_volt_dial_valueChanged(int val)
{
    ui->volt_output->setValue((double) val/100);
}

void MainWindow::on_underVolt_valueChanged(double val)
{

//    psDrvPtr->SET_UNDERVOLT_LIMIT_F(val);
    underVoltLimit = val;
    if (connected)
        SET_UNDERVOLT_LIMIT_F(val);
//    int t = qRound(val*100);
    ui->volt_dial->setMinimum(qRound(val*5));
}

void MainWindow::on_overVolt_valueChanged(double val)
{
//    psDrvPtr->SET_OVERVOLT_PROTECTION_F(val);
    if(connected)
        SET_OVERVOLT_PROTECTION_F(val);
    overVoltLimit = val;
    int t = qRound(val*100);
    ui->volt_dial->setMaximum(t-qRound(val*5));
    ui->volt_dial->setNotchTarget(ui->volt_dial->maximum()/10);
}

void MainWindow::on_volt_output_valueChanged(double val)
{
    ui->volt_dial->setValue(val*100);
    volt_updated = true;
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
    curr_updated = true;
//    psDrvPtr->SET_CURR_LIMIT_F(val);
}

//---------------------------------

void MainWindow::on_outputStateBtn_clicked()
{
//    psDrvPtr->SET_OUTPUT_STATE_F(ui->outputStateBtn->isChecked());
    if (!connected) return;
    SET_OUTPUT_STATE_F(ui->outputStateBtn->isChecked());
    updateInerface();
}

void MainWindow::on_oper_mode_combo_currentIndexChanged(int index)
{
//    psDrvPtr->SET_SETTING_MODE_F(index);
    if(!connected) return;
    SET_SETTING_MODE_F(index);
}

void MainWindow::on_foldback_btn_clicked()
{
    if (!connected) return;
//    psDrvPtr->SET_FOLDBACK_PROTECTION_F(ui->foldback_btn->isChecked());
    SET_FOLDBACK_PROTECTION_F(ui->foldback_btn->isChecked());
}

void MainWindow::on_power_up_combo_currentIndexChanged(int index)
{
//    psDrvPtr->SET_START_MODE_F(index);
    if(!connected) return;
    SET_START_MODE_F(index);
}

void MainWindow::connectionLost()
{

}
