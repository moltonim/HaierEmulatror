//---------------------------------------------------------------------------

#ifndef SureConnectionThreadH
#define SureConnectionThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class SureConnectThread : public TThread
{            
private:
protected:
    void __fastcall Execute();
public:
    __fastcall SureConnectThread();
};
//---------------------------------------------------------------------------
#endif
