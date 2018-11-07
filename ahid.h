#ifndef AHID_H
#define AHID_H

#include <windows.h>

// Report types
#define AHID_REPTYPE_INT_IN				0
#define AHID_REPTYPE_INT_OUT			1
#define AHID_REPTYPE_FEATURE			2

class AHid
{

public:
    AHid();

    int start();
    int release();

    int Init();
    int Register(int * pipeId, unsigned int vendorId, unsigned int productId, int interfaceId, unsigned char reportId, unsigned char reportSize, unsigned char reportType);
    int Deregister(int pipeId);
    int Identify(int pipeId, unsigned char * buffer, unsigned int bufferSize);
    int Find(int pipeId);
    int Read(int pipeId, unsigned char * buffer, unsigned int bytesToRead, unsigned int * bytesRead);
    int Write(int pipeId, unsigned char * buffer, unsigned int bytesToWrite, unsigned int * bytesWritten);
    int Request(int pipeId);
    int Info(void);


private:

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
};

#endif // AHID_H
