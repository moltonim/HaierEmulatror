



#include "Unit1.h"
#include <dateutils.hpp>


void UpdateLog(int read, String note, int opt)
{
    if (!Form1->LogCkb->Checked)
        return;

    String s = ExtractFilePath( Application->ExeName );
    String s2 = DateToStr(Now());

    //AnsiString

    int n = s2.Pos("/");
    while ( n)
    {
        s2[n] = '_';
        n = s2.Pos("/");
    }

    s += s2+".log";

    int h;
    if (!FileExists(s))
        h = FileCreate(s);
    else
        h = FileOpen(s, fmOpenWrite);

    //FileWrite(h, "Ciao", 4);

    int len = FileSeek(h, 0, 2);    //is len interesting to someone?
    s = TimeToStr(Now());
    s2.sprintf(".%03d", MilliSecondOfTheSecond(Now()) );
    s += s2;

    if (note != "")
    {
        s += note + "\n";
        FileWrite(h, s.c_str(), s.Length());
        FileClose(h);
        return;
    }

    char* p;
    int cmd = 0;
    if (read == 1)
    {
        p = SerialVar.Readen;
        len = SerialVar.LenReaden;
        s += " R";
        cmd = SerialVar.Readen[2];
        cmd = cmd;      //for future use!
    }
    else
    {
        p = SerialVar.ToWrite;
        len = SerialVar.LenToWrite;
        s += " W";
    }
    s += " => ";
    for (n = 0; n < len-2; n++)
        s += IntToHex((unsigned char)(*(p++)), 2) + " ";
    
    s += "\n";
    FileWrite(h, s.c_str(), s.Length());
    FileClose(h);
}
 