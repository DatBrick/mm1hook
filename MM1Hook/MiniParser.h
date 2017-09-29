#pragma once

#include "FileSystem.h"

class MiniParser
{
public:
    char NameBuffer[256];
    unsigned int dword104;
    const char *Name;
    unsigned int CurrentToken;
    unsigned int Identation;
    unsigned int LastError;
    unsigned int PutBack;

    virtual int RawGetCh(void) = 0;
    virtual void RawPutCh(int) = 0;
};

struct StreamMiniParser : public MiniParser
{
    Stream *pStream;
};
