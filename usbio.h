#ifndef USBIO_H
#define USBIO_H

#include <QObject>
#include <QTimer>
#include "ahid.h"

#define VID 0x9999
#define PID 0x0101
#define REPORT_ID 0
#define OUTPUT_REPORT_SIZE 16
#define INPUT_REPORT_SIZE 16

#define POOL_MS 5

class usbIO : public QObject
{
    Q_OBJECT

public:
    explicit usbIO(QObject *parent = nullptr);

    void init();

signals:
    void readedBuffer(QString buffer);
    void writedBuffer(QString buffer);
    void usbConnected(bool status);
    void getStatistics(unsigned int n_in , unsigned int n_out);
    void getParsedData(int yaw, int trasl);

public slots:
    void update();
    void update_statistics();

private:
    AHid hid;

    int hid_status = -1; // stato di funzionamento libreria ahid
    int in_pipe, out_pipe = 0;

    unsigned char readBuffer[INPUT_REPORT_SIZE] = {};
    unsigned char writeBuffer[OUTPUT_REPORT_SIZE] = {};

    unsigned int n_readed_buffer = 0;
    unsigned int n_writed_buffer = 0;

    QTimer *pool_timer = new QTimer(this);
    QTimer *statistics_timer = new QTimer(this);

    bool isConnected();

    void parsingReadedData();
    //QString uChartoQString(unsigned char *  byte, unsigned int size);
};


#endif // USBIO_H
