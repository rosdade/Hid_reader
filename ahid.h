#ifndef AHID_H
#define AHID_H

#include <QObject>
#include <QDebug>
#include <windows.h>

// Report types
#define AHID_REPTYPE_INT_IN				0
#define AHID_REPTYPE_INT_OUT			1
#define AHID_REPTYPE_FEATURE			2

#define VID 0x9999
#define PID 0x1234
#define REPORT_ID 0
#define OUTPUT_REPORT_SIZE 8
#define INPUT_REPORT_SIZE 8

class AHid : public QObject
{
    Q_OBJECT

public:
    explicit AHid(QObject *parent = nullptr);

signals:
    void readedBuffer(QString buffer);
    void writedBuffer(QString buffer);
    void usbConnected(bool status);

public slots:
    void update();

private:

    int hid_status = -1; // stato di funzionamento libreria ahid
    unsigned char readBuffer[INPUT_REPORT_SIZE] = {};
    unsigned char writeBuffer[OUTPUT_REPORT_SIZE] = {};
    unsigned int readed , writtened  = 0;

    typedef int (WINAPI *AHid_Init) (HWND, UCHAR*);
    typedef int (WINAPI *AHid_Info) (VOID);
    typedef int (WINAPI *AHid_Register) (INT*, UINT, UINT, INT, UCHAR, UCHAR, UCHAR);
    typedef int (WINAPI *AHid_Deregister) (INT);
    typedef int (WINAPI *AHid_Identify) (INT, UCHAR*, UINT);
    typedef int (WINAPI *AHid_Read) (INT, UCHAR*, UINT, UINT*);
    typedef int (WINAPI *AHid_Write) (INT, UCHAR*, UINT, UINT*);
    typedef int (WINAPI *AHid_Find) (INT);
    typedef int (WINAPI *AHid_Request) (INT);

    HMODULE AHid_dll;

    int in_pipe, out_pipe = 0;

    void start();

    int Init();
    int Register(int * pipeId, unsigned int vendorId, unsigned int productId, int interfaceId, unsigned char reportId, unsigned char reportSize, unsigned char reportType);
    int Deregister(int pipeId);
    int Identify(int pipeId, unsigned char * buffer, unsigned int bufferSize);
    int Find(int pipeId);
    int Read(int pipeId, unsigned char * buffer, unsigned int bytesToRead, unsigned int * bytesRead);
    int Write(int pipeId, unsigned char * buffer, unsigned int bytesToWrite, unsigned int * bytesWritten);
    int Request(int pipeId);
    int Info(void);
    void release();
    bool isConnected();

    QString toString (unsigned char * buffer, unsigned int buffer_size);
};

#endif // AHID_H
