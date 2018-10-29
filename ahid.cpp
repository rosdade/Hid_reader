#include <QDebug>
#include <windows.h>
#include "ahid.h"

AHid::AHid(QObject *parent) : QObject(parent)
{
}

/*
QString toString (unsigned char * buffer, unsigned int buffer_size) {
    std::string result = "";
    unsigned char s;
    for (unsigned int i = 0 ; i < buffer_size ; i++) {
        s = buffer[i];
        result += s;
    }
    return QString::fromStdString(result) ;
}
*/

void AHid::start() {
    QString func_return;
    AHid_dll = LoadLibrary(L"AHid.dll");
    if (AHid_dll != nullptr) {
        qDebug("AHid library loaded");
        func_return = "AHid library loaded";
        hid_status = 0;
    }
    else {
        qDebug("AHid library not found");
        func_return = "AHid library not found";
        hid_status = -1;
    }
}

void AHid::release() {
    FreeLibrary( AHid_dll );
    hid_status = -1 ;
    Sleep(100);
}

bool AHid::isConnected() {
    return (Find(in_pipe) == 0 && Find(out_pipe) == 0);
}

void AHid::update() {
    unsigned int result = 0;
    switch (hid_status) {
        case -1:
            start();
            break;
        case 0:
            result = Init();
            if (result == 0) {
                hid_status = 1;
                qDebug("AHid library initializated");
            }
            else {
                release();
            }
            break;
        case 1:
            result = Register(&out_pipe, VID, PID, -1, REPORT_ID, OUTPUT_REPORT_SIZE, AHID_REPTYPE_INT_OUT);
            result += Register(&in_pipe, VID, PID, -1, REPORT_ID, INPUT_REPORT_SIZE, AHID_REPTYPE_INT_IN);
            if (result >=5) {
                hid_status = -1;
                release();
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
        case 2:
        result = Read(in_pipe, readBuffer, INPUT_REPORT_SIZE, &readed);
        if (result == 0) {
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
            Deregister(in_pipe);
            Deregister(out_pipe);
        }
            result = Write(out_pipe, writeBuffer, OUTPUT_REPORT_SIZE, &writtened);
            if (result == 0) {
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
                Deregister(out_pipe);
            }
            break;
        default:
            start();
            break;
    }
}

int AHid::Init() {
    AHid_Init aInit = (AHid_Init) GetProcAddress( AHid_dll, "AHid_Init" );
    uchar* sn = (uchar*)("ciao");
    int result = aInit(nullptr, sn);
    return result;
}

int AHid::Register(int * pipeId, unsigned int vendorId, unsigned int productId, int interfaceId, unsigned char reportId, unsigned char reportSize, unsigned char reportType) {
    AHid_Register aRegister = (AHid_Register) GetProcAddress( AHid_dll, "AHid_Register" );
    return aRegister(pipeId, vendorId, productId, interfaceId, reportId, reportSize, reportType);
}

int AHid::Deregister(int pipeId) {
    AHid_Deregister aDeregister = (AHid_Deregister) GetProcAddress( AHid_dll, "AHid_Deregister" );
    return aDeregister(pipeId);
}

int AHid::Find(int pipeId) {
    AHid_Find aFind = (AHid_Find) GetProcAddress( AHid_dll, "AHid_Find" );
    return aFind(pipeId);
}

int AHid::Identify(int pipeId, unsigned char * buffer, unsigned int bufferSize) {
    AHid_Identify aIdentify = (AHid_Identify) GetProcAddress( AHid_dll, "AHid_Identify" );
    return aIdentify(pipeId, buffer, bufferSize);
}

int AHid::Read(int pipeId, unsigned char * buffer, unsigned int bytesToRead, unsigned int * bytesRead) {
    AHid_Read aRead = (AHid_Read) GetProcAddress( AHid_dll, "AHid_Read" );
    return aRead(pipeId, buffer, bytesToRead, bytesRead);
}


int AHid::Write(int pipeId, unsigned char * buffer, unsigned int bytesToWrite, unsigned int * bytesWritten) {
    AHid_Write aWrite = (AHid_Write) GetProcAddress( AHid_dll, "AHid_Write" );
    return aWrite(pipeId, buffer, bytesToWrite, bytesWritten);
}

int AHid::Request(int pipeId) {
    AHid_Request aRequest = (AHid_Request) GetProcAddress( AHid_dll, "AHid_Request" );
    return aRequest(pipeId);
}

int AHid::Info(void) {
    AHid_Info aInfo = (AHid_Info) GetProcAddress( AHid_dll, "AHid_Info" );
    return aInfo();
}


