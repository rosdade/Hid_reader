#ifndef USBIO_H
#define USBIO_H

#include <QObject>
#include <QTimer>
#include "ahid.h"

class usbIO : public QObject
{
    Q_OBJECT

public:
    explicit usbIO(QObject *parent = nullptr);

    void init();

    unsigned char readBuffer[INPUT_REPORT_SIZE] = {};
    unsigned char writeBuffer[OUTPUT_REPORT_SIZE] = {};

signals:
    void readedBuffer(QString buffer);
    void writedBuffer(QString buffer);
    void usbConnected(bool status);
    void getStatistics(unsigned int n_in , unsigned int n_out);

public slots:
     void update();
     void update_statistics();

private:
    AHid hid;

    int pool_ms = 10;

    int hid_status = -1; // stato di funzionamento libreria ahid
    int in_pipe, out_pipe = 0;

    unsigned int n_readed_buffer = 0;
    unsigned int n_writed_buffer = 0;

    QTimer *pool_timer = new QTimer(this);
    QTimer *statistics_timer = new QTimer(this);

    bool isConnected();
};


#endif // USBIO_H
