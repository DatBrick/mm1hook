#pragma once

#include "FileSystem.h"

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
