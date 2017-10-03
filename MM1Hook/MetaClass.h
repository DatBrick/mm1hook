#pragma once

class MetaField;
class MetaType;

class MetaClass
{
public:
    const char *Name;
    unsigned int Size;
    void*(*Alloc)(int);
    void(*Free)(void*, int);
    void(*DeclareFields)(void);
    MetaClass *Parent;
    MetaClass *Child;
    MetaClass *Next;
    MetaField *pFields;
    unsigned int Index;
};

class MetaField
{
public:
    MetaField *Next;
    const char *Name;
    unsigned int Offset;
    MetaType *pType;
};

class MetaType
{
public:
    virtual void Save(class MiniParser *,void *) = 0;
    virtual void Load(class MiniParser *,void *) = 0;
    virtual unsigned int SizeOf(void) = 0;
    virtual void * New(int) = 0;
    virtual void Delete(void *,int) = 0;
};

class StructType : public MetaType
{
public:
    MetaClass *pMetaClass;
};

class ArrayOfType : public MetaType
{
public:
    MetaType *pType;
    int nCount;
};

class RefToType : public MetaType
{
public:
    MetaType *pType;
    int RefOffset;
    unsigned int RefSize;
};

class PtrToType : public MetaType
{
public:
    MetaType *pType;
};