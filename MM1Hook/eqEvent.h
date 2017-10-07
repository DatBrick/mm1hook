#pragma once

class eqEventMonitor;

class eqEventHandler
{
public:
    unsigned int Debug;
    unsigned int dword8;
    unsigned int dwordC;
    eqEventMonitor *EventMonitors[8];
    unsigned int dword30;
    unsigned int dword34;
    unsigned int dword38;
    unsigned int dword3C;
    unsigned int CursorX;
    unsigned int CursorY;
    unsigned int dword48;
    char buffer4C[256];

    virtual void * Destructor(unsigned int)= 0;
    virtual int BeginGfx(int width, int height, int windowed) = 0;
    virtual void EndGfx(void) = 0;
    virtual void Update(int) = 0;
    virtual void BeginTracking(void) = 0;
    virtual void EndTracking(void) = 0;
    virtual char * GKeyName(int) = 0;
};

class eqEventMonitor
{
public:
    eqEventHandler *pHandler;
    unsigned int dword8;
    unsigned int Index;
    unsigned int dword10;

    virtual void * Destructor(unsigned int) = 0;
    virtual void Redraw(void *,int,int,int,int) = 0;
    virtual void Refocus(void *,int) = 0;
    virtual void Mouse(void *,int,int,int,int,int,int,int) = 0;
    virtual void Keyboard(void *,int,int,int,int) = 0;
    virtual void Destroy(void *) = 0;
    virtual void Activate(void *,int) = 0;
};

// unions are fun *sarcasm*
union eqEvent
{
    struct
    {
        void* Context;
        unsigned int Type;
        unsigned int Flags;
        unsigned int KeyCode;
        unsigned int Ascii;
        unsigned int dword14;
        unsigned int dword18;
        unsigned int dword1C;
        unsigned int dword20;
    } Keyboard;
};

class eqEventQ : public eqEventMonitor
{
public:
    eqEvent *pEvents;
    unsigned int dword18;
    unsigned int MaxEvents;
    unsigned int CurrentEventCount;
    unsigned int EventIndex;
    unsigned int InSuperQ;
};

class Dispatchable
{
public:
    virtual long WindowProc(struct HWND__ *,unsigned int,unsigned int,long) { }
};

class WINEventHandler : public eqEventHandler
{
public:
    float CenterX;
    float CenterY;
    float ScaleX;
    float ScaleY;
    unsigned int dword15C;
    unsigned int dword160;
    Dispatchable WindowProc;
    unsigned int WindowFlags;
};

class eqReplayChannel
{
public:
    unsigned int Magic;
    eqReplayChannel *Next;

    virtual void InitRecord(void) = 0;
    virtual void InitPlayback(void) = 0;
    virtual void DoRecord(class Stream *) = 0;
    virtual void DoPlayback(class Stream *) = 0;
    virtual void ShutdownRecord(void) = 0;
    virtual void ShutdownPlayback(void) = 0;
};