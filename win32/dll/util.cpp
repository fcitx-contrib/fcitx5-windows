#include "util.h"
#include <format>

namespace fcitx {
// {FC3869BA-51E3-4078-8EE2-5FE49493A1F4}
const GUID FCITX_CLSID = {0xfc3869ba,
                          0x51e3,
                          0x4078,
                          {0x8e, 0xe2, 0x5f, 0xe4, 0x94, 0x93, 0xa1, 0xf4}};

// {9A92B895-29B9-4F19-9627-9F626C9490F2}
const GUID PROFILE_GUID{0x9a92b895,
                        0x29b9,
                        0x4f19,
                        {0x96, 0x27, 0x9f, 0x62, 0x6c, 0x94, 0x90, 0xf2}};

std::string guidToString(REFGUID guid) {
    const auto *p = reinterpret_cast<const unsigned char *>(&guid);
    return std::format("{{{:02X}{:02X}{:02X}{:02X}-{:02X}{:02X}-{:02X}{:02X}-{:"
                       "02X}{:02X}-{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}}}",
                       p[3], p[2], p[1], p[0], p[5], p[4], p[7], p[6], p[8],
                       p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
}

std::wstring stringToWString(const std::string &str, int codePage) {
    int len =
        MultiByteToWideChar(codePage, 0, str.c_str(), str.size(), nullptr, 0);
    WCHAR *buf = new WCHAR[len + 1];
    MultiByteToWideChar(codePage, 0, str.c_str(), str.size(), buf, len);
    buf[len] = '\0';
    std::wstring wstr;
    wstr.append(buf);
    delete[] buf;
    return wstr;
}
} // namespace fcitx
