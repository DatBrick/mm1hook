#include "stdafx.h"
#include "Hooking.h"

#include "FileSystem.h"

#include "MM1Hook.h"

#include "Vector.h"

#include "MetaClass.h"

#include "asNode.h"

namespace MM1
{
    auto OpenFile = get_as<class Stream* (*)(const char *name, const char *folder, const char *extension, int a4, int a5, const char *type)>(0x5418E0);
    auto fgets = get_as<int (*)(char *, int, class Stream *)>(0x540F60);

    auto malloc = get_as<void*(*)(unsigned int)>(0x50F560);
    auto free   = get_as<void(*)(void*)>(0x50F580);

    auto Displayf = get_as<void (*)(const char *, ...)>(0x5585E0);
}

class WArray
{
public:
    void Read(const char* name)
    {
        auto WArray__AddWidgetData = get_as<void (WArray::*)(int, int, const Vector4 &, char *)>(0x4A1100);

        if (Stream* pStream = MM1::OpenFile(name, "tune", ".csv", 0, 0, "widget file"))
        {
            char line[128];

            MM1::fgets(line, 128, pStream);

            while ( MM1::fgets(line, 128, pStream) )
            {
#pragma warning(push)
#pragma warning(disable : 4996)

                auto menuName = strtok(line, ",");
                auto menuID = atoi(strtok(0, ","));

                auto widgetName = strtok(0, ",");
                auto widgetID = atoi(strtok(0, ","));

                Vector4 dimensions;
                dimensions.w = (float) atoi(strtok(0, ",")) / 640;
                dimensions.x = (float) atoi(strtok(0, ",")) / 480;
                dimensions.y = (float) atoi(strtok(0, ",")) / 640;
                dimensions.z = (float) atoi(strtok(0, ",")) / 480;

                auto description = strtok(0, "\r\n");

#pragma warning(pop)

                (this->*WArray__AddWidgetData)(menuID, widgetID, dimensions, description);
            }

            pStream->Destructor(1);
        }
        else
        {
            // Errorf("Can't open widget data file '%s'", name);
        }
    }
};


FunctionHook<void (WArray::*)(const char*)> Read(0x4A0F20, &WArray::Read);

bool dumped = false;

decltype(Hook_ChangeDisplaySettingsA) Hook_ChangeDisplaySettingsA((std::uintptr_t) &ChangeDisplaySettingsA, [ ] (DEVMODEA* lpDevMode, DWORD dwFlags) -> LONG
{
    if (!dumped)
    {
        dumped = true;

        DumpMetaInfo();
    }

    if (lpDevMode)
    {
        lpDevMode->dmPelsWidth = 0;
        lpDevMode->dmPelsHeight = 0;
    }

    return Hook_ChangeDisplaySettingsA(lpDevMode, dwFlags);
});

#include <fstream>
#include <algorithm>
#include <string>

std::string GetMetaTypeName(MetaType* pType, MetaField* pField, MetaField** pFields, std::size_t nFields)
{
    switch (*(std::uintptr_t*)(pType))
    {
        case 0x596218: return "Vector2";        // Vector2Type
        case 0x5960C8: return "Vector3";        // Vector3Type
        case 0x5960F8: return "Vector4";        // Vector4Type
        case 0x5962D8: return "char";           // CharType
        case 0x5962F0: return "signed char";    // SignedCharType
        case 0x596308: return "unsigned char";  // UnsignedCharType
        case 0x596320: return "short";          // SignedShortType
        case 0x596338: return "unsigned short"; // UnsignedShortType
        case 0x596350: return "int";            // SignedIntType
        case 0x596368: return "long long";      // SignedInt64Type
        case 0x596380: return "unsigned int";   // UnsignedIntType
        case 0x596398: return "float";          // FloatType
        case 0x5963B0: return "string";         // StringType

        case 0x590F58:
        {
            return static_cast<StructType*>(pType)->pMetaClass->Name;
        }

        case 0x590FB8:
        {
            auto* pArrayOfType = static_cast<ArrayOfType*>(pType);
            
            return GetMetaTypeName(pArrayOfType->pType, nullptr, pFields, nFields) + "[" + std::to_string(pArrayOfType->nCount) + "]"; 
        }

        case 0x5942A8:
        {
            auto* pRefToType = static_cast<RefToType*>(pType);

            std::string array_size = std::to_string(pRefToType->RefOffset) + "," + std::to_string(pRefToType->RefSize);

            if (pField)
            {
                auto offset = pField->Offset + pRefToType->RefOffset;

                for (std::size_t i = 0; i < nFields; ++i)
                {
                    if (pFields[i]->Offset == offset && pFields[i]->pType->SizeOf() == pRefToType->RefSize)
                    {
                        array_size = pFields[i]->Name;

                        break;
                    }
                }
            }

            return GetMetaTypeName(pRefToType->pType, nullptr, pFields, nFields) + " [" + array_size + "]";
        }

        case 0x5953E0:
        {
            auto* pPtrToType = static_cast<PtrToType*>(pType);
        
            return GetMetaTypeName(pPtrToType->pType, nullptr, pFields, nFields) + "*";
        }
    }

    return "field";
}

void DumpMetaInfo()
{
    std::FILE* output = std::fopen("meta.txt", "w");

    auto& classes = get_ref<MetaClass*[256]>(0x711B44);
    auto& count   = get_ref<int>(0x711B38);

    auto& pCurrent = get_ref<MetaClass*>(0x711F40);
    auto& ppField  = get_ref<MetaField**>(0x711F44);

    std::fprintf(output, "Total: %i\n", count);

    std::fflush(output);

    for (int i = 0; i < count; ++i)
    {
        auto* pClass = classes[i];

        std::fputs(pClass->Name, output);

        if (pClass->Parent)
        {
            std::fprintf(output, " : %s (%u, %u)", pClass->Parent->Name, pClass->Size - pClass->Parent->Size, pClass->Size);
        }
        else
        {
            std::fprintf(output, " (%u)", pClass->Size);
        }


        if (pClass->DeclareFields)
        {
            if (!pClass->pFields)
            {
                pCurrent = pClass;
                ppField = &pClass->pFields;

                pClass->DeclareFields();
            }

            MetaField* fields[256];
            std::size_t field_count = 0;

            for (auto* pField = pClass->pFields; pField; pField = pField->Next)
            {
                if (pClass->Parent && (pField->Offset < pClass->Parent->Size))
                    continue;

                fields[field_count++] = pField;
            }

            if (field_count)
            {
                std::fputs(" {\n", output);

                std::sort(fields, fields + field_count, [ ] (MetaField* lhs, MetaField* rhs)
                {
                    return lhs->Offset < rhs->Offset;
                });

                for (std::size_t j = 0; j < field_count; ++j)
                {
                    auto* pField = fields[j];
                    auto* pType  = pField->pType;

                    std::fprintf(output, "    %s %s @ 0x%X\n", GetMetaTypeName(pType, pField, fields, field_count).c_str(), pField->Name, pField->Offset);
                }

                std::fputs("}\n", output);
            }
            else
            {
                std::fputs(";\n", output);
            }
        }

        std::fputs("\n", output);

        std::fflush(output);
    }

    std::fflush(output);
    std::fclose(output);
}

/*
BOOL IsQuadCoplanar(struct Vector3 *a1, struct Vector3 *a2, struct Vector3 *a3, struct Vector3 *a4)
{
    Vector3 v0, v1, v2, v3;

    v0.x = a1->x - a2->x;
    v0.y = a1->y - a2->y;
    v0.z = a1->z - a2->z;

    v1.x = a3->x - a2->x;
    v1.y = a3->y - a2->y;
    v1.z = a3->z - a2->z;

    v2.x = v0.z * v1.y - v0.y * v1.z;
    v2.y = v0.x * v1.z - v0.z * v1.x;
    v2.z = v0.y * v1.x - v0.x * v1.y;

    float f0 = Vector3::InvMag(&v2);

    v3.x = f0 * v2.x;
    v3.y = f0 * v2.y;
    v3.z = f0 * v2.z;

    v2.x = a4->x - a2->x;
    v2.y = a4->y - a2->y;
    v2.z = a4->z - a2->z;

    return QuadCoplanarTolerance > fabs((v3.x * v2.x + v3.y * v2.y + v3.z * v2.z) / sqrt(Vector3::Area(a2, a1, a3) + Vector3::Area(a4, a1, a3)));
}
*/

class mmGame : public asNode
{
public:
    char _buffer[124236];

    virtual void InitGameStrings(void) = 0;
    virtual void InitMyPlayer(void) = 0;
    virtual void InitOtherPlayers(void) = 0;
    virtual void InitGameObjects(void) = 0;
    virtual void InitHUD(void) = 0;
    virtual void UpdateGameInput(int) = 0;
    virtual void UpdateDebugInput(void) = 0;
    virtual void UpdateDebugKeyInput(int) = 0;
    virtual void UpdateGame(void) = 0;
    virtual void NextRace(void) = 0;
    virtual void HitWaterHandler(void) = 0;
    virtual void DropThruCityHandler(void) = 0;

    virtual void SendChatMessage(const char * message)
    {
        // IDK, Have fun...

        MM1::Displayf("Chat Message: %s", message);

        Hook_SendChatMessage(this, message);
    }

    virtual void BeDone(void) = 0;
    virtual class mmWaypoints * GetWaypoints(void) = 0;
};

FunctionHook<void(mmGame::*)(const char*)> Hook_SendChatMessage(0x40DD20, &mmGame::SendChatMessage);

#include "agiBitmap.h"

class mmHudMap : public asNode
{
public:
    char _buffer[684];

    void DrawOrientatedBitmap(Matrix34* pos, agiBitmap* image)
    {
        auto mmHudMap_WorldToBitmap = get_as<Point (mmHudMap::*)(Vector3*)>(0x420D30);
        auto mmHudMap_DrawClipped = get_as<void (mmHudMap::*)(agiBitmap *, int, int, float, float, float, float)>(0x420240);

        Point value = (this->*mmHudMap_WorldToBitmap)(&pos->m3);

        MM1::Displayf("HELP!!! { %X, %X }", value.x, value.y);

        (this->*mmHudMap_DrawClipped)(image, value.x, value.y, (float) image->Width, (float) image->Height / 8.0f, 0.0f, 0.0f);
    }

    void DrawClipped(struct agiBitmap *image, struct Point pos, float a, float  b, float c, float d)
    {
        MM1::Displayf("DrawClipped: %s: { %u, %u } - %f, %f, %f, %f", image->Name, pos.x, pos.y, a, b, c, d);

        Hook_DrawClipped(this, image, pos, a, b, c, d);
    }
};

FunctionHook<decltype(&mmHudMap::DrawOrientatedBitmap)> Hook_DrawOrientatedBitmap(0x4203E0, &mmHudMap::DrawOrientatedBitmap);
FunctionHook<decltype(&mmHudMap::DrawClipped)> Hook_DrawClipped(0x420240, &mmHudMap::DrawClipped);