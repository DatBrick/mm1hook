#pragma once

#include "Base.h"
#include "Stream.h"

struct FileInfo
{
    char Path[1024];
    BOOL IsDirectory;
    void *pContext;
};

struct PagerInfo_t
{
    unsigned int PagerHandle;
    unsigned int Offset;
    unsigned int Size;
};

class FileSystem : public Base
{
public:
    unsigned int Index;

    virtual int ValidPath(const char * path) = 0;
    virtual int QueryOn(const char * path) = 0;
    virtual class Stream * OpenOn(const char * path, int readonly, void * buffer, int bufferSize) = 0;
    virtual class Stream * CreateOn(const char * path, void * buffer, int bufferSize) = 0;
    virtual int PagerInfo(const char * path, struct PagerInfo_t & infoOut) = 0;
    virtual int ChangeDir(const char * path) = 0;
    virtual int GetDir(const char * path, int) = 0;
    virtual struct FileInfo * FirstEntry(const char * path) = 0;
    virtual struct FileInfo * NextEntry(struct FileInfo * fileInfo) = 0;
    virtual void NotifyDelete(void) = 0;
};