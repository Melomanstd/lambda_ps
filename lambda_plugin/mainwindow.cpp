#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(CoreThread *core, bool limFunc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

//    setWindowTitle("Lambda Power Supply");



    ui->pushButton->setVisible(false);
    ui->label_4->setVisible(false);
    ui->const_mode_lbl->setVisible(false);

    this->limFunc = limFunc;
    if(!limFunc)
        blockUI(true);
    else
    {
        ui->ip_edit->setEnabled(false);
        ui->connect_btn->setEnabled(false);
    }
//    setEnabled(false);

    volt_updated = false;
    curr_updated = false;
    connected = false;
    underVoltLimit = 0;
    overVoltLimit = 0;
    ui->voltage_output_lcd->display("0FF");
    ui->current_output_lcd->display("0FF");
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

    QString dir = QCoreApplication::applicationDirPath();
    dir.append("/project_lambda_ru.qm");
    //    b = translator.load("C:/Projects/GeneratorLib/GeneratorPlug/project_ru.qm");
       bool b = translator.load(dir);
        QCoreApplication::installTranslator(&translator);
    //    a.installTranslator(&translator);
        ui->retranslateUi(this);

    thr = core;//new Thread;
//    checkTimer.start(500);
    connect(ui->connect_btn, SIGNAL(clicked()), this, SLOT(connectClicked()));
    connect(&checkTimer, SIGNAL(timeout()), this, SLOT(checkState()));
//    connect(thr, SIGNAL(stateUpdate(double,double,QString)), this, SLOT(stateUpdated(double,double,QString)));
    connect(thr, SIGNAL(connectionLost()), this, SLOT(connectionLost()));
//    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(testSlot()));
//    thr->start();
    connect(&checkTimer, SIGNAL(timeout()), this, SLOT(checkState()));
    connect(thr, SIGNAL(socketState(bool)), this, SLOT(startConnection(bool)));

    QSettings s("lambdaconf.ini",QSettings::IniFormat);
    ui->ip_edit->setText(s.value("lambda/ip").toString());
}

MainWindow::~MainWindow()
{   
//    psDrvPtr->closeSocket();
    if (!limFunc)
        if(thr)
        {
            thr->stopThread();
            thr->wait(1000);
            delete thr;
        }
//    closeSocket();
    delete ui;
}

void MainWindow::connectClicked()
{
    if (!connected)
    {
//        QByteArray ip = ui->ip_edit->text().toAscii();
//        thr->setSocketIp(ui->ip_edit->text());
//        int state = openSocket(ip.data(), "8003");
//        if (state<0) return;
        thr->startThread(ui->ip_edit->text(), "8003");
        QSettings s("lambdaconf.ini",QSettings::IniFormat);
        s.setValue("lambda/ip", ui->ip_edit->text());
//        startConnection();
//        ui->oper_mode_combo->setCurrentIndex(1);
//        SET_OUTPUT_STATE_F(0);
    }
    else
    {
        connectionLost();
//        thr->stopThread();
//        thr->stopThread();
//        closeSocket();
//        connected = false;
//        ui->connect_btn->setText("Connect");
    }
}

void MainWindow::updateInerface()
{
    if (!connected) return;
    QueueItem item(0, "");
    checkOutputState(item);
    checkFoldbackState(item);
    checkStartMode(item);
    checkOperationMode(item);
    checkOverVolt(item);
    checkUnderVolt(item);

//    int max, t;
//    t = QString(GET_UNDERVOLT_LIMIT_F()).toDouble()*5;//psDrvPtr->GET_UNDERVOLT_LIMIT_F().toDouble()*5;
//    ui->volt_dial->setMinimum(t);
//    t = qRound(QString(GET_OVERVOLT_PROTECTION_F()).toDouble())*5;
//    max = qRound(QString(GET_OVERVOLT_PROTECTION_F()).toDouble())*100;
//    ui->volt_dial->setMaximum(max-t);
//    ui->underVolt->setValue(QString(GET_UNDERVOLT_LIMIT_F()).toDouble());//(psDrvPtr->GET_UNDERVOLT_LIMIT_F().toDouble());
//    ui->overVolt->setValue(QString(GET_OVERVOLT_PROTECTION_F()).toDouble());//psDrvPtr->GET_OVERVOLT_PROTECTION_F().toDouble());
//    ui->volt_output->setValue(QString(GET_VOLT_LIMIT_F()).toDouble());
//    ui->curr_output->setValue(QString(GET_CURR_LIMIT_F()).toDouble());
    qDebug()<<"";
}

void MainWindow::on_resetSettings_clicked()
{
//    psDrvPtr->SET_UNDERVOLT_LIMIT_F(2);
//    psDrvPtr->RESET_PS_SETTINGS_F();
    if (!connected) return;
    QueueItem item(RESET_PS_SETTINGS, "");
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex, 1000);
    updateInerface();
//    RESET_PS_SETTINGS_F();
//    updateInerface();
}

void MainWindow::checkState()
{
    if (!thr) return;
    if (!connected) return;

    if(ui->outputStateBtn->isChecked())
    {
        ui->voltage_output_lcd->display(thr->getVoltage());
        ui->current_output_lcd->display(thr->getCurrent());
    }
    else
    {
        ui->voltage_output_lcd->display("0FF");
        ui->current_output_lcd->display("0FF");
    }

    if(volt_updated)
    {
        QueueItem item(SET_VOLT_LIMIT, QString::number(ui->volt_output->value()));
        thr->addRequest(&item);
        thr->resumeThread();
        item.wait.wait(&mutex, 1000);
        volt_updated = false;
    }
    if(curr_updated)
    {
        QueueItem item(SET_CURR_LIMIT, QString::number(ui->curr_output->value()));
        thr->addRequest(&item);
        thr->resumeThread();
        item.wait.wait(&mutex, 1000);
        curr_updated = false;
    }
}

void MainWindow::checkOutputState(QueueItem &item)
{
    item.cmdNum = GET_OUTPUT_STATE;
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex,1000);
    QString res = item.result;
    connected=false;
    if(res == "OFF") ui->outputStateBtn->setChecked(false);
    if(res == "ON") ui->outputStateBtn->setChecked(true);
    connected=true;
}

void MainWindow::checkFoldbackState(QueueItem &item)
{
    item.cmdNum = GET_FOLDBACK_PROTECTION;
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex,1000);
    QString res = item.result;
    connected=false;
    if(res == "OFF") ui->foldback_btn->setChecked(false);
    if(res == "ON") ui->foldback_btn->setChecked(true);
    connected=true;
}

void MainWindow::checkStartMode(QueueItem &item)
{
    item.cmdNum = GET_START_MODE;
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex,1000);
    QString res = item.result;
    connected=false;
    if(res == "OFF") ui->power_up_combo->setCurrentIndex(0);
    if(res == "ON") ui->power_up_combo->setCurrentIndex(1);
    connected=true;
}

void MainWindow::checkOperationMode(QueueItem &item)
{
    item.cmdNum = GET_SETTING_MODE;
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex,1000);
    QString res = item.result;
    connected=false;
    if(res == "LOC") ui->oper_mode_combo->setCurrentIndex(0);
    if(res == "REM") ui->oper_mode_combo->setCurrentIndex(1);
    if(res == "LLO") ui->oper_mode_combo->setCurrentIndex(2);
    connected=true;
}

void MainWindow::checkOverVolt(QueueItem &item)
{
    int max, t;
    item.cmdNum = GET_OVERVOLT_PROTECTION;
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex,1000);
    QString res = item.result;
    connected=false;
    ui->overVolt->setValue(res.toDouble());
    t = res.toDouble()*5;
    max = res.toDouble()*100;
    ui->volt_dial->setMaximum(max-t);
    connected=true;
}

void MainWindow::checkUnderVolt(QueueItem &item)
{
    int t;
    item.cmdNum = GET_UNDERVOLT_LIMIT;
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex,1000);
    QString res = item.result;
    connected=false;
    ui->underVolt->setValue(res.toDouble());
    t = res.toDouble()*105;
    ui->volt_dial->setMinimum(t);
    connected=true;
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
//    ui->volt_dial->setNotchTarget(ui->volt_dial->maximum()/10);
    if (!connected) return;
    if (qRound(val)*100 >= ui->volt_dial->maximum())
    {
        ui->underVolt->setValue(underVoltLimit);
        return;
    }
    underVoltLimit = val;
    {
        QueueItem item(SET_UNDERVOLT_LIMIT, QString::number(val));
        thr->addRequest(&item);
        thr->resumeThread();
        item.wait.wait(&mutex, 1000);
//        volt_updated = false;
    }

//        SET_UNDERVOLT_LIMIT_F(val);
//    int t = qRound(val*100);
    ui->volt_dial->setMinimum(qRound(val*105));
//    ui->volt_dial->setNotchTarget(ui->volt_dial->maximum()/10);
    if (ui->volt_output->value() < underVoltLimit)
        ui->volt_output->setValue(underVoltLimit);
}

void MainWindow::on_overVolt_valueChanged(double val)
{
//    psDrvPtr->SET_OVERVOLT_PROTECTION_F(val);
//    ui->volt_dial->setNotchTarget(ui->volt_dial->maximum()/10);
    if(!connected) return;
//    int s1=qRound(val)*100;
//    int s2 = ui->volt_dial->minimum();
    if (qRound(val)*100 <= ui->volt_dial->minimum())
    {
        ui->overVolt->setValue(overVoltLimit);
        return;
    }
    {
        QueueItem item(SET_OVERVOLT_PROTECTION, QString::number(val));
        thr->addRequest(&item);
        thr->resumeThread();
        item.wait.wait(&mutex, 1000);
    }
//        SET_OVERVOLT_PROTECTION_F(val);
    overVoltLimit = val;
    int t = qRound(val*100);
    ui->volt_dial->setMaximum(t-qRound(val*5));
//    ui->volt_dial->setNotchTarget(ui->volt_dial->maximum()/10);
//    ui->volt_dial->setNotchTarget(ui->volt_dial->maximum()/10);
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
    ui->curr_output->setValue((double) val/*/100*/);
}

void MainWindow::on_curr_output_valueChanged(double val)
{
    if(!connected) return;
    ui->curr_dial->setValue(val/**100*/);
    curr_updated = true;
//    SET_CURR_LIMIT_F(val);
//    psDrvPtr->SET_CURR_LIMIT_F(val);
}

//---------------------------------

void MainWindow::on_outputStateBtn_clicked()
{
    if (!connected) return;
//    item.cmdNum = SET_OUTPUT_STATE;
//    item.param = QString::number(ui->outputStateBtn->isChecked());
    QueueItem item(SET_OUTPUT_STATE, QString::number(ui->outputStateBtn->isChecked()));
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex, 1000);
//    if(item.result.isEmpty())
//        QMessageBox::critical(this, "ERROR","CONNECTOIN LOST", QMessageBox::Ok);
}

void MainWindow::on_oper_mode_combo_currentIndexChanged(int index)
{
//    psDrvPtr->SET_SETTING_MODE_F(index);
    if(!connected) return;
//    SET_SETTING_MODE_F(index);
    QueueItem item(SET_SETTING_MODE, QString::number(index));
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex, 1000);
}

void MainWindow::on_foldback_btn_clicked()
{
    if (!connected) return;
    QueueItem item(SET_FOLDBACK_PROTECTION, QString::number(ui->foldback_btn->isChecked()));
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex, 1000);
//    psDrvPtr->SET_FOLDBACK_PROTECTION_F(ui->foldback_btn->isChecked());
//    SET_FOLDBACK_PROTECTION_F(ui->foldback_btn->isChecked());
}

void MainWindow::on_power_up_combo_currentIndexChanged(int index)
{
//    psDrvPtr->SET_START_MODE_F(index);
    if(!connected) return;
//    SET_START_MODE_F(index);
    QueueItem item(SET_START_MODE, QString::number(index));
    thr->addRequest(&item);
    thr->resumeThread();
    item.wait.wait(&mutex, 1000);
}

void MainWindow::connectionLost()
{
    checkTimer.stop();
    thr->stopThread();
//    closeSocket();
    if (!limFunc)
        blockUI(true);
    connected = false;
    ui->connect_btn->setText(tr("Connect"));
}

void MainWindow::startConnection(bool state)
{
//    thr->startThread(ui->ip_edit->text(), "8003");
    if (!state) return;
    connected = true;
//    checkState();
    if (!limFunc)
        blockUI(false);
    checkTimer.start(500);
    updateInerface();

    ui->connect_btn->setText(tr("Disconnect"));
}

void MainWindow::testSlot()
{
    QString test = QString(FIRMWARE_REVISION_F());

    qDebug()<<"test "<<test;
}

void MainWindow::blockUI(bool s)
{
    ui->outputStateBtn->setEnabled(!s);
    ui->power_up_combo->setEnabled(!s);
    ui->oper_mode_combo->setEnabled(!s);
    ui->foldback_btn->setEnabled(!s);
    ui->volt_box->setEnabled(!s);
    ui->curr_box->setEnabled(!s);
    ui->resetSettings->setEnabled(!s);
}
