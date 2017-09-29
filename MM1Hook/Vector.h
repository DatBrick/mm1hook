#pragma once

struct Vector3
{
    float x;
    float y;
    float z;
};

struct Vector4
{
    float x;
    float y;
    float z;
    float w;
};

struct Matrix34
{
    Vector3 m0;
    Vector3 m1;
    Vector3 m2;
    Vector3 m3;
};
