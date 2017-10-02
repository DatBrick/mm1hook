#pragma once

#include "Base.h"

class Stream : public Base
{
public:
    unsigned char *pBuffer;
    unsigned int Offset;
    unsigned int BufferIndex;
    unsigned int BufferSize;
    unsigned int MaxBufferSize;
    class FileSystem *pFileSystem;
    unsigned char Flags;
    unsigned char SwapEndian;
    unsigned char IsLittleEndian;
    unsigned char byte1F;

    virtual void * GetMapping(void) = 0;
    virtual unsigned int GetPagerHandle(void) = 0;
    virtual int GetPagingInfo(unsigned int & handleOut, unsigned int & offsetOut, unsigned int & sizeOut) = 0;
    virtual int RawRead(void * output, int outputSize) = 0;
    virtual int RawWrite(void * input, int inputSize) = 0;
    virtual int RawSeek(int offset) = 0;
    virtual int RawTell(void) = 0;
    virtual int RawSize(void) = 0;
    virtual void RawDebug(void) = 0;
    virtual int AlignSize(void) = 0;
    virtual int GetError(char * outputBuffer, int outputSize) = 0;
};

