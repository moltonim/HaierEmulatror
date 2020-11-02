//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SureConnectionThread.h"
#include "TokenThread.h"
#pragma package(smart_init)

extern TokenThread *TaskToken;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SureConnectThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SureConnectThread::SureConnectThread()
    : TThread(false)
{
    FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void __fastcall SureConnectThread::Execute()
{
    //---- Place thread code here ----

    static int n;
    n++;

    while (TaskToken->Suspended)
    {
        TaskToken->Resume();
        Sleep(50);
        if (n++ >= 100)
        {
            n = 0;
            break;
        }
    }

}
//---------------------------------------------------------------------------
