#include <windows.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

typedef int (WINAPI *AHid_Init) (HWND, UCHAR*);
typedef int (WINAPI *AHid_Info) (VOID);


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    HMODULE Ahid_dll = LoadLibrary(L"AHid.dll");
    if (Ahid_dll != NULL) {
        //QMessageBox::information(0,"info","dll loaded");
        AHid_Init aInit = (AHid_Init) GetProcAddress( Ahid_dll, "AHid_Init" );
        AHid_Info aInfo = (AHid_Info) GetProcAddress( Ahid_dll, "AHid_Info" );
        aInit(NULL, NULL);
        aInfo();
    }
    else {
        //QMessageBox::warning(0,"Error","dll not loaded");
    }


    FreeLibrary( Ahid_dll );
    return app.exec();
}
