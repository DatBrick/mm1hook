#pragma once

class Base
{
public:
    virtual void * Destructor(unsigned int shouldDelete) = 0;
    virtual class MetaClass * GetClass(void) = 0;
    virtual char * GetTypeNameV(void) = 0;
    virtual void BeforeSave(void) = 0;
    virtual void AfterLoad(void) = 0;
};