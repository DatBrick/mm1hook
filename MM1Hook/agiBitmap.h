#pragma once

#include "agi.h"
#include "agiRefreshable.h"

#include <ddraw.h>

struct agiBitmap : public agiRefreshable
{
    const char *Name;
    struct agiSurfaceDesc *pSurfaceDesc;
    unsigned int Transparency;
    unsigned int Width;
    unsigned int Height;
    float dword2C;
    float dword30;
    unsigned int Is3D;
    unsigned int dword38;
    IDirectDrawSurface4 *pSurface;
};

struct agiSWBitmap : public agiBitmap
{ };

struct agiDDBitmap : public agiBitmap
{ };