#pragma once

class agiColorModel
{
public:
    virtual void * Destructor(unsigned int) = 0;
    virtual unsigned int GetColor(struct agiRgba) = 0;
    virtual unsigned int FindColor(struct agiRgba) = 0;
    virtual unsigned int Filter(unsigned int,unsigned int,unsigned int,unsigned int) = 0;
    virtual void SetPixel(class agiSurfaceDesc *,int,int,unsigned int) = 0;
    virtual unsigned int GetPixel(class agiSurfaceDesc *,int,int) = 0;
};
