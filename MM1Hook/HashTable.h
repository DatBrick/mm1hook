#pragma once

struct HashEntry;
struct HashIterator;

struct HashTable
{
    int MaxEntries;
    int EntryCount;
    HashEntry **pEntries;
};

struct HashEntry
{
    const char *pName;
    void *pData;
    HashEntry *pNext;
};

struct HashIterator
{
    HashTable *pTable;
    int Index;
    HashEntry *pEntry;
};