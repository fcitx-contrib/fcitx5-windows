#pragma once

#include <Windows.h>
#include <string>

#define TEXTSERVICE_LANGID_HANS                                                \
    MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

namespace fcitx {
extern const GUID FCITX_CLSID;
extern const GUID PROFILE_GUID;
std::string guidToString(REFGUID guid);
std::wstring stringToWString(const std::string &str, int codePage);
} // namespace fcitx
