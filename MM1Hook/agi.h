#pragma once

class agiColorModel
{
public:
    unsigned int ByteCount;
    unsigned int BitCountR;
    unsigned int BitCountG;
    unsigned int BitCountB;
    unsigned int BitCountA;
    unsigned int MaskR;
    unsigned int MaskG;
    unsigned int MaskB;
    unsigned int MaskA;
    unsigned int RefCount;

    virtual void * Destructor(unsigned int) = 0;
    virtual unsigned int GetColor(struct agiRgba) = 0;
    virtual unsigned int FindColor(struct agiRgba) = 0;
    virtual unsigned int Filter(unsigned int,unsigned int,unsigned int,unsigned int) = 0;
    virtual void SetPixel(class agiSurfaceDesc *,int,int,unsigned int) = 0;
    virtual unsigned int GetPixel(class agiSurfaceDesc *,int,int) = 0;
};
