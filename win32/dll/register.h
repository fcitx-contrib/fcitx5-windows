#pragma once

#include <Windows.h>

namespace fcitx {
extern HINSTANCE dllInstance;

BOOL RegisterServer();
void UnregisterServer();
BOOL RegisterProfiles();
void UnregisterProfiles();
BOOL RegisterCategories();
void UnregisterCategories();
} // namespace fcitx
