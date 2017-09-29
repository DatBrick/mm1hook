#pragma once

#include "agiRefreshable.h"

class agiRasterizer : public agiRefreshable
{
public:
    virtual void BeginGroup(void) = 0;
    virtual void EndGroup(void) = 0;
    virtual void Verts(enum agiVtxType,union agiVtx *,int) = 0;
    virtual void Points(enum agiVtxType,union agiVtx *,int) = 0;
    virtual void SetVertCount(int) = 0;
    virtual void Triangle(int,int,int) = 0;
    virtual void Quad(int,int,int,int) = 0;
    virtual void Poly(int *,int) = 0;
    virtual void Line(int,int) = 0;
    virtual void Card(int,int) = 0;
    virtual void Mesh(enum agiVtxType,union agiVtx *,int,unsigned short *,int) = 0;
    virtual void Mesh2(struct agiScreenVtx2 *,int,unsigned short *,int) = 0;
    virtual void LineList(enum agiVtxType,union agiVtx *,int) = 0;
};
