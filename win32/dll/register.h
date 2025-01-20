#pragma once

#include <Windows.h>

namespace fcitx {
extern HINSTANCE dllInstance;

BOOL RegisterServer();
void UnregisterServer();
BOOL RegisterProfiles();
BOOL RegisterCategories();
void UnregisterCategoriesAndProfiles();
} // namespace fcitx
