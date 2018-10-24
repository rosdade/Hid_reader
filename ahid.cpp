#include <QDebug>
#include <QTimer>
#include <windows.h>
#include "ahid.h"

AHid::AHid(QObject *parent) : QObject(parent)
{
}

void AHid::start() {
    AHid_dll = LoadLibrary(L"AHid.dll");
    if (AHid_dll != nullptr) {
        qDebug("AHid library loaded");
        hid_status = 0;
        connect(update_timer, SIGNAL(timeout()), this, SLOT(update()));
        update_timer->start(5);
    }
    else {
        qDebug("AHid library not found");
    }
}

void AHid::release() {
    FreeLibrary( AHid_dll );
    write_timer->stop();
    Sleep(1000);
}

bool AHid::isConnected() {
    return (Find(in_pipe) == 0 && Find(out_pipe) == 0);
}

void AHid::update() {
    unsigned int result = 0;
    switch (hid_status) {
        case 0:
            result = Init();
            if (result == 0) {
                hid_status = 1;
                qDebug("AHid library initializated");
            }
            else release();
            break;
        case 1:
            result = Register(&out_pipe, VID, PID, -1, REPORT_ID, OUTPUT_REPORT_SIZE, AHID_REPTYPE_INT_OUT);
            result += Register(&in_pipe, VID, PID, -1, REPORT_ID, INPUT_REPORT_SIZE, AHID_REPTYPE_INT_IN);
            if (result >=5) {
                hid_status = 0;
                release();
            }
            else if (isConnected() == true && result == 00) {
                hid_status = 2;
                qDebug("device connected");
            }

            break;
        case 2:
            result = Read(in_pipe, readBuffer, INPUT_REPORT_SIZE, &readed);
            Sleep(1);
            result += Write(out_pipe, writeBuffer, OUTPUT_REPORT_SIZE, &writtened);
            if (result >= 5) hid_status = 1;
            break;
        default:
            start();
            break;
    }


}

int AHid::Init() {
    AHid_Init aInit = (AHid_Init) GetProcAddress( AHid_dll, "AHid_Init" );
    //AHid_Info aInfo = (AHid_Info) GetProcAddress( AHid_dll, "AHid_Info" );
    uchar* sn = (uchar*)("ciao");
    int result = aInit(nullptr, sn);
    //aInfo();
    return result;
}

int AHid::Register(int * pipeId, unsigned int vendorId, unsigned int productId, int interfaceId, unsigned char reportId, unsigned char reportSize, unsigned char reportType) {
    AHid_Register aRegister = (AHid_Register) GetProcAddress( AHid_dll, "AHid_Register" );
    return aRegister(pipeId, vendorId, productId, interfaceId, reportId, reportSize, reportType);
}

int AHid::Find(int pipeId) {
    AHid_Find aFind = (AHid_Find) GetProcAddress( AHid_dll, "AHid_Find" );
    return aFind(pipeId);
}

int AHid::Read(int pipeId, unsigned char * buffer, unsigned int bytesToRead, unsigned int * bytesRead) {
    AHid_Read aRead = (AHid_Read) GetProcAddress( AHid_dll, "AHid_Read" );
    return aRead(pipeId, buffer, bytesToRead, bytesRead);
}


int AHid::Write(int pipeId, unsigned char * buffer, unsigned int bytesToWrite, unsigned int * bytesWritten){
    AHid_Write aWrite = (AHid_Write) GetProcAddress( AHid_dll, "AHid_Write" );
    return aWrite(pipeId, buffer, bytesToWrite, bytesWritten);
}

