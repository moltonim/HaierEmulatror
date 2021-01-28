//---------------------------------------------------------------------------

#ifndef TokenThreadH
#define TokenThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TokenThread : public TThread
{
private:
protected:
    void __fastcall Execute();
public:
    __fastcall TokenThread(bool CreateSuspended);
    void __fastcall AnalizeRcv(void);
    void __fastcall MessageReceived(void);
    void __fastcall SendRequestTest(void);
    void __fastcall SendStatus(void);
    void __fastcall SendComAnsw(int cmd);
    
    void __fastcall HeartBeat(void);
    void __fastcall CommReceiving(void);
    void __fastcall SendAlarmFrame(void);
    String __fastcall GetStatusStr(char* c);
    int StatusTimer;
    bool Connected;
};

typedef struct _serform
{
    unsigned char   buf[1000];
    unsigned char   msg[100];
    int    rcv_pointer;
    int    rcv_size;
    bool   connect;
}   SERBUF_STRUCT;




//---------------------------------------------------------------------------
#endif
