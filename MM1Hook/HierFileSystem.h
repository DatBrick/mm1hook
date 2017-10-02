#pragma once

#include "FileSystem.h"

struct HierFileSystem : public FileSystem
{
    // Nothing to see here
};

struct HierFileEntry
{
    HANDLE hFindFile;
    WIN32_FIND_DATAA FindData;
};
