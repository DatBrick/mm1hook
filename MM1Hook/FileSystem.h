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

struct VirtualStream : public Stream
{
    Stream *pDataStream;
    unsigned int DataOffset;
    unsigned int FileSize;
    HANDLE hMutex;
    unsigned int dword30;
    unsigned int dword34;
};

struct VirtualFileInode
{
    unsigned int DataOffset;
    unsigned int Size : 23;
    unsigned int ExtensionOffset : 9;
    bool IsDirectory : 1;
    unsigned int NameInteger : 13;
    unsigned int NameOffset : 18;
};

struct VirtualFileEntry
{
    VirtualFileInode *pNodes;
    unsigned int FilesLeft;
};

struct VirtualFileSystem : public FileSystem
{
    Stream *pFileStream;
    unsigned int Magic;
    unsigned int NodeCount;
    unsigned int DirectoryCount;
    unsigned int NameDataSize;
    VirtualFileInode *pNodes;
    const char *pNameData;
};

struct HierFileSystem : public FileSystem
{
    // Nothing to see here
};

struct HeirFileEntry
{
    HANDLE hFindFile;
    WIN32_FIND_DATAA FindData;
};
