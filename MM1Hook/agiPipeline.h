#pragma once

#include "agiColorModel.h"
#include "agiRefreshable.h"
#include "agiLight.h"

#include <ddraw.h>

class agiPipeline
{
public:
    const char *Name;
    unsigned int dword8;
    unsigned int dwordC;
    unsigned int Width;
    unsigned int Height;
    unsigned int Depth;
    unsigned int dword1C;
    unsigned int dword20;
    unsigned int dword24;
    HWND hWnd;
    int HorzRes;
    int VertRes;
    float dword34;
    unsigned int dword38;
    unsigned int Lightmask;
    BYTE gap40[264];
    DDSURFACEDESC2 SurfaceDesc;
    BYTE gap1C4[248];
    agiColorModel *ColorModel0;
    agiColorModel *ColorModel1;
    agiColorModel *ColorModel2;
    agiColorModel *UIColorModel;
    struct agiRenderer *pRenderer;
    unsigned int dword2D0;
    unsigned int MaxTextureWidth;
    unsigned int MaxTextureHeight;
    agiRefreshable *pRefreshables;
    unsigned int dword2E0;
    unsigned int dword2E4;
    unsigned int dword2E8;
    unsigned int SceneCount;

    virtual void * Destructor(unsigned int) = 0;
    virtual int Validate(void) = 0;
    virtual int BeginGfx(void) = 0;
    virtual void EndGfx(void) = 0;
    virtual void BeginFrame(void) = 0;
    virtual void BeginScene(void) = 0;
    virtual void EndScene(void) = 0;
    virtual void EndFrame(void) = 0;
    virtual class agiTexDef * CreateTexDef(void) = 0;
    virtual class agiTexLut * CreateTexLut(void) = 0;
    virtual class agiMtlDef * CreateMtlDef(void) = 0;
    virtual class DLP * CreateDLP(void) = 0;
    virtual class agiViewport * CreateViewport(void) = 0;
    virtual class agiLight * CreateLight(void) = 0;
    virtual class agiLightModel * CreateLightModel(void) = 0;
    virtual class agiBitmap * CreateBitmap(void) = 0;
    virtual void CopyBitmap(int,int,class agiBitmap *,int,int,int,int) = 0;
    virtual void ClearAll(int) = 0;
    virtual void ClearRect(int,int,int,int,unsigned int) = 0;
    virtual void Print(int,int,int,char const *) = 0;
    virtual int PrintIs3D(void) = 0;
    virtual void PrintInit(void) = 0;
    virtual void PrintShutdown(void) = 0;
    virtual void Defragment(void) = 0;
    virtual int LockFrameBuffer(class agiSurfaceDesc &) = 0;
    virtual void UnlockFrameBuffer(void) = 0;
    virtual void DumpStatus(struct agiMemStatus &) = 0;
};