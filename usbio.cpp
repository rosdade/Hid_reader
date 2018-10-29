#include <QDebug>
#include "usbio.h"
#include "ahid.h"

usbIO::usbIO(QObject *parent) : QObject(parent)
{

}

bool usbIO::isConnected() {
    return (hid.Find(in_pipe) == 0 && hid.Find(out_pipe) == 0);
}

void usbIO::init() {
    connect(pool_timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(statistics_timer, SIGNAL(timeout()), this, SLOT(update_statistics()));
    statistics_timer->start(1000);
    update();
}

void usbIO::update() {
    int result = 0;
    switch (hid_status) {
        case -1:
            if (hid.start() == 0) {
                pool_timer->start(pool_ms);
                hid_status = 0;
                qDebug("AHid library loaded");
            }
            else {
                qWarning("AHid library not found");
            }
            break;
        case 0:
            result = hid.Init();
            if (result == 0) {
                hid_status = 1;
                qDebug("AHid library initializated");
                pool_timer->start(pool_ms);
            }
            else {
                pool_timer->stop();
                result = hid.release();
            }
            break;
        case 1:
            result = hid.Register(&out_pipe, VID, PID, -1, REPORT_ID, OUTPUT_REPORT_SIZE, AHID_REPTYPE_INT_OUT);
            result += hid.Register(&in_pipe, VID, PID, -1, REPORT_ID, INPUT_REPORT_SIZE, AHID_REPTYPE_INT_IN);
            if (result >=5) {
                hid_status = -1;
                hid.release();
            }
            else if (isConnected() == true && result == 00) {
                hid_status = 2;
                emit usbConnected(true);
                qDebug("device connected");

            }
            else {
                emit usbConnected(false);
            }
            break;
        case 2: {
            unsigned int readed = 0;
            result = hid.Read(in_pipe, readBuffer, INPUT_REPORT_SIZE, &readed);
            if (result == 0) {
                n_readed_buffer ++;
                QString toQString = "R ";
                QString s;
                for (unsigned int i = 0 ; i < INPUT_REPORT_SIZE ; i++) {
                    s.sprintf("%02x", readBuffer[i]);
                    toQString += s;
                }
                emit readedBuffer(toQString);
            }
            else {
                qWarning("error reading data");
                hid_status = 1;
                hid.Deregister(in_pipe);
                hid.Deregister(out_pipe);
                break;
            }
            unsigned int byte_writed = 0;
            result = hid.Write(out_pipe, writeBuffer, OUTPUT_REPORT_SIZE, &byte_writed);
            if (result == 0) {
                n_writed_buffer ++;
                QString toQString = "W ";
                QString s;
                for (unsigned int i = 0 ; i < OUTPUT_REPORT_SIZE ; i++) {
                    s.sprintf("%02x", writeBuffer[i]);
                    toQString += s;
                }
                emit writedBuffer(toQString);
            }
            else{
                qWarning("error writing data");
                hid_status = 1;
                hid.Deregister(out_pipe);
            }
            break;
        }
        default:
            hid.start();
            break;
    }
}

void usbIO::update_statistics() {
    emit getStatistics(n_readed_buffer, n_writed_buffer);
    n_readed_buffer = 0;
    n_writed_buffer = 0;
}
