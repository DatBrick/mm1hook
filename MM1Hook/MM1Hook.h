#pragma once

extern FunctionHook<LONG (WINAPI*)(DEVMODEA *, DWORD)> Hook_ChangeDisplaySettingsA;

void DumpMetaInfo();

class mmGame;
class mmHudMap;

extern FunctionHook<void(mmGame::*)(const char*)> Hook_SendChatMessage;
extern FunctionHook<void (mmHudMap::*)(struct agiBitmap *image, struct Point pos, float a, float  b, float c, float d)> Hook_DrawClipped;