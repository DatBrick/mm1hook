#pragma once

#include "asNode.h"
#include "Timer.h"

class asCullManager : public asNode
{
    unsigned int ColorText;
    unsigned int ColorRed;
    unsigned int ColorGreen;
    unsigned int ColorBlue;
    unsigned int Debug;
    unsigned int nCameras;
    asCamera *pCameras[16];
    asCamera *pCurrentCamera;
    unsigned int nCullables;
    unsigned int MaxCullables;
    unsigned int nCullables2D;
    unsigned int MaxCullables2D;
    asCullable **pCullables;
    asCullable **pCullables2D;
    Matrix34 **pCullableMatrices;
    float LastFrameElapsed;
    float AverageFPS;
    Timer FrameTimer;
    Timer FPSCounter;
    unsigned int FrameCounter;
    HANDLE hMutex;

    virtual void DeclareCamera(class asCamera *) = 0;
    virtual void DeclareCullable(class asCullable *) = 0;
    virtual void DeclareCullable2D(class asCullable *) = 0;
};