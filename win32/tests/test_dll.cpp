#include "../dll/util.h"
#include <Windows.h>
#include <cassert>

using namespace fcitx;

int main() {
    assert(guidToString(FCITX_CLSID) ==
           "{FC3869BA-51E3-4078-8EE2-5FE49493A1F4}");
    assert(stringToWString("中A", CP_UTF8) == L"中A");
    return 0;
}
