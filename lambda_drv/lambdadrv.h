#ifndef LABMDADRV_H
#define LABMDADRV_H

#include <QtCore>
#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>

enum
{
    FIRMWARE_REVISION,
    SET_VOLT_LIMIT,
    GET_VOLT_LIMIT,
    SET_CURR_LIMIT,
    GET_CURR_LIMIT,
    SET_OUTPUT_STATE,
    GET_OUTPUT_STATE,
    MEAS_VOLTAGE,
    MEAS_CURRENT,
    READ_CONSTANT_MODE,
    SET_SETTING_MODE,
    GET_SETTING_MODE,
    SET_START_MODE,
    GET_START_MODE,
    SET_OVERVOLT_PROTECTION,
    GET_OVERVOLT_PROTECTION,
    READ_OVERVOLT_TRIPPED,
    SET_UNDERVOLT_LIMIT,
    GET_UNDERVOLT_LIMIT,
    SET_FOLDBACK_PROTECTION,
    GET_FOLDBACK_PROTECTION,
    READ_FOLDBACK_TRIPPED,
    SET_LAN_LED_STATE,
    READ_HOSTNAME,
    READ_IP_ADDRESS,
    READ_MAC_ADDRESS,
    RESET_LAN_SETTINGS,
    RESET_PS_SETTINGS,
    SAVE_SP_SETTINGS,
    RECALL_SP_SETTINGS,
    SELF_TEST
};


class LambdaDrv : public QObject
{
    Q_OBJECT
public:
    explicit LambdaDrv(QObject *parent = 0);
    virtual ~LambdaDrv();
    int openSocket(QString ip, QString port);
    int closeSocket();
    int writeData(QString query);
    void readData(QByteArray &msg);
    void checkForErrors();
    int sendedState();

    QString FIRMWARE_REVISION_F();
    int SET_VOLT_LIMIT_F(double val);
    QString GET_VOLT_LIMIT_F();
    int SET_CURR_LIMIT_F(double val);
    QString GET_CURR_LIMIT_F();
    int SET_OUTPUT_STATE_F(int val);
    QString GET_OUTPUT_STATE_F();
    QString MEAS_VOLTAGE_F();
    QString MEAS_CURRENT_F();
    QString READ_CONSTANT_MODE_F();
    int SET_SETTING_MODE_F(int val);
    QString GET_SETTING_MODE_F();
    int SET_START_MODE_F(int val);
    QString GET_START_MODE_F();
    int SET_OVERVOLT_PROTECTION_F(double val);
    QString GET_OVERVOLT_PROTECTION_F();
    QString READ_OVERVOLT_TRIPPED_F();
    int SET_UNDERVOLT_LIMIT_F(double val);
    QString GET_UNDERVOLT_LIMIT_F();
    int SET_FOLDBACK_PROTECTION_F(int val);
    QString GET_FOLDBACK_PROTECTION_F();
    QString READ_FOLDBACK_TRIPPED_F();
    int SET_LAN_LED_STATE_F(int val);
    QString READ_HOSTNAME_F();
    QString READ_IP_ADDRESS_F();
    QString READ_MAC_ADDRESS_F();
    int RESET_LAN_SETTINGS_F();
    int RESET_PS_SETTINGS_F();
    int SAVE_PS_SETTINGS_F();
    int RECALL_PS_SETTINGS_F();
    int SELF_TEST_F();
    
signals:
    void connectionLost();
    
public slots:
//    void readSomething();

protected:
    QTcpSocket *tcpSocket;
    bool somethingSended;
};

#endif // LABMDADRV_H
