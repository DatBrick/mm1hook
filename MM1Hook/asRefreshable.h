#pragma once

class agiRefreshable
{
public:
    agiRefreshable *pPrev;
    agiRefreshable *pNext;
    class agiPipeline *pPipeline;
    unsigned int ErrorCode;
    unsigned int RefCount;

    virtual void EndGfx(void) = 0;
    virtual void Restore(void) = 0;
    virtual char * GetName(void) = 0;
    virtual void * Destructor(unsigned int) = 0;
    virtual int BeginGfx(void) = 0;
    virtual int IsTexture(void) = 0;
};
