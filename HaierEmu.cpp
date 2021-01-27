//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("SendCustomMsgForm.cpp", Form2);
USEFORM("AlarmPanel.cpp", Form3);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    HWND hwnd = FindWindow("TForm1", NULL);
    HANDLE hMutex = CreateMutex(NULL, false, "HaierEmu");
    if (hMutex == NULL)
        ShowMessage(GetLastError());
    else
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            ShowMessage("Application already running!");
            SetForegroundWindow(hwnd);
            return -1;
        }                             

    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TForm2), &Form2);
         //Application->CreateForm(__classid(TForm2), &Form2);
         Application->CreateForm(__classid(TForm3), &Form3);
         //Application->CreateForm(__classid(TForm3), &Form3);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
