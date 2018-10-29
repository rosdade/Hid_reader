#include <windows.h>
#include "ahid.h"

AHid::AHid()
{

}

int AHid::start() {
    int result = 0;
    AHid_dll = LoadLibrary(L"AHid.dll");
    if (AHid_dll != nullptr) {
        result = 0;
    }
    else {
        result = -1;
    }
    return result;
}

int AHid::release() {
    int result = 0;
    FreeLibrary( AHid_dll );
    if (AHid_dll == nullptr) {
        result = 0;
    }
    else {
        result = -1;
    }
    return result;
}

int AHid::Init() {
    AHid_Init aInit = (AHid_Init) GetProcAddress( AHid_dll, "AHid_Init" );
    unsigned char* sn = (unsigned char*)("ciao");
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


