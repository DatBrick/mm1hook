#pragma once

class MetaClass
{
public:
    const char *Name;
    unsigned int Index;
    void*(*Allocator)(int);
    void(*Deallocator)(void*, int);
    void(*Declarer)(void);
    MetaClass *Parent;
    MetaClass *Child;
    MetaClass *Next;
    MetaField *pFields;
    unsigned int SerialIndex;
};

class MetaField
{
public:
    MetaField *Next;
    const char *Name;
    unsigned int Offset;
    MetaType *pType;
};

class StructType
{
public:
    MetaClass *pMetaClass;

    virtual void Save(class MiniParser *,void *) = 0;
    virtual void Load(class MiniParser *,void *) = 0;
    virtual unsigned int SizeOf(void) = 0;
    virtual void * New(int) = 0;
    virtual void Delete(void *,int) = 0;
};

class MetaType : public StructType
{
public:
    // Nothing to see here
};