#include "register.h"
#include "util.h"
#include <atlcomcli.h>
#include <filesystem>
#include <msctf.h>

namespace fs = std::filesystem;

#define FCITX5 "Fcitx5"
#define THREADING_MODEL "ThreadingModel"
#define APARTMENT "Apartment"

namespace fcitx {
HINSTANCE dllInstance; // Set by DllMain.

// HKEY_CLASSES_ROOT\CLSID\{FC3869BA-51E3-4078-8EE2-5FE49493A1F4} Fcitx5
// - InprocServer32 C:\Windows\system32
BOOL RegisterServer() {
    DWORD dw;
    HKEY hKey = nullptr;
    HKEY hSubKey = nullptr;
    WCHAR dllPath[MAX_PATH];
    auto achIMEKey = "CLSID\\" + guidToString(FCITX_CLSID);
    BOOL ret = RegCreateKeyExA(HKEY_CLASSES_ROOT, achIMEKey.c_str(), 0, nullptr,
                               REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr,
                               &hKey, &dw);
    ret |=
        RegSetValueExA(hKey, nullptr, 0, REG_SZ,
                       reinterpret_cast<const BYTE *>(FCITX5), sizeof FCITX5);
    ret |= RegCreateKeyExA(hKey, "InprocServer32", 0, nullptr,
                           REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr,
                           &hSubKey, &dw);
    auto hr = GetModuleFileNameW(dllInstance, dllPath, MAX_PATH);
    ret |= RegSetValueExW(hSubKey, nullptr, 0, REG_SZ,
                          reinterpret_cast<const BYTE *>(dllPath),
                          hr * sizeof(WCHAR));
    ret |= RegSetValueExA(hSubKey, THREADING_MODEL, 0, REG_SZ,
                          reinterpret_cast<const BYTE *>(APARTMENT),
                          sizeof APARTMENT);
    RegCloseKey(hSubKey);
    RegCloseKey(hKey);
    return ret == ERROR_SUCCESS;
}

void UnregisterServer() {}

BOOL RegisterProfiles() {
    std::wstring pchDesc = stringToWString(FCITX5);
    WCHAR dllPath[MAX_PATH];
    GetModuleFileNameW(dllInstance, dllPath, MAX_PATH);
    fs::path path = dllPath;
    path = path.remove_filename().append("penguin.ico");
    CComPtr<ITfInputProcessorProfileMgr> mgr;
    mgr.CoCreateInstance(CLSID_TF_InputProcessorProfiles, nullptr, CLSCTX_ALL);
    auto hr = mgr->RegisterProfile(
        FCITX_CLSID, TEXTSERVICE_LANGID_HANS, PROFILE_GUID, pchDesc.c_str(),
        pchDesc.size() * sizeof(WCHAR), path.c_str(),
        path.wstring().size() * sizeof(WCHAR), 0, nullptr, 0, 1, 0);
    mgr.Release();
    return hr == S_OK;
}

void UnregisterProfiles() {}

// No documentation about what they means.
const GUID Categories[] = {GUID_TFCAT_CATEGORY_OF_TIP,
                           GUID_TFCAT_TIP_KEYBOARD,
                           GUID_TFCAT_TIPCAP_SECUREMODE,
                           GUID_TFCAT_TIPCAP_UIELEMENTENABLED,
                           GUID_TFCAT_TIPCAP_INPUTMODECOMPARTMENT,
                           GUID_TFCAT_TIPCAP_COMLESS,
                           GUID_TFCAT_TIPCAP_WOW16,
                           GUID_TFCAT_TIPCAP_IMMERSIVESUPPORT,
                           GUID_TFCAT_TIPCAP_SYSTRAYSUPPORT,
                           GUID_TFCAT_PROP_AUDIODATA,
                           GUID_TFCAT_PROP_INKDATA,
                           GUID_TFCAT_PROPSTYLE_CUSTOM,
                           GUID_TFCAT_PROPSTYLE_STATIC,
                           GUID_TFCAT_PROPSTYLE_STATICCOMPACT,
                           GUID_TFCAT_DISPLAYATTRIBUTEPROVIDER,
                           GUID_TFCAT_DISPLAYATTRIBUTEPROPERTY};

BOOL RegisterCategories() {
    ITfCategoryMgr *mgr;
    CoCreateInstance(CLSID_TF_CategoryMgr, nullptr, CLSCTX_INPROC_SERVER,
                     IID_ITfCategoryMgr, reinterpret_cast<void **>(&mgr));
    HRESULT hr = S_OK;
    for (const auto &guid : Categories) {
        hr |= mgr->RegisterCategory(FCITX_CLSID, guid, FCITX_CLSID);
    }
    mgr->Release();
    return hr == S_OK;
}

void UnregisterCategories() {}
} // namespace fcitx
