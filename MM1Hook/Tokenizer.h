#pragma once

#include "FileSystem.h"

struct Tokenizer
{
    const char *Name;
    unsigned int CurrentLine;
    Stream *pStream;
    unsigned int CurrentChar;
};
