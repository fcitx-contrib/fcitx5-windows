#include <fcitx-utils/environ.h>
#include <fcitx-utils/event.h>
#include <fcitx-utils/eventdispatcher.h>
#include <fcitx/addonmanager.h>
#include <fcitx/instance.h>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

namespace fcitx {
std::unique_ptr<Instance> instance;
std::unique_ptr<fcitx::EventDispatcher> dispatcher;

void setenv(const char *name, const std::string &value) {
    setEnvironment(name, value.c_str());
}

void setupEnv() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    auto rootPath = ::fs::path(path).parent_path().parent_path();
    auto fcitx_addon_dirs = rootPath / "lib" / "fcitx5";
    setenv("FCITX_ADDON_DIRS", fcitx_addon_dirs.string());
    auto xdg_data_dirs = rootPath / "share";
    auto fcitx_data_dirs = xdg_data_dirs / "fcitx5";
    setenv("XDG_DATA_DIRS", xdg_data_dirs.string());
    setenv("FCITX_DATA_DIRS", fcitx_data_dirs.string());
}

void start() {
    Log::setLogRule("*=5,notimedate");
    setupEnv();
    instance = std::make_unique<Instance>(0, nullptr);
    auto &addonMgr = instance->addonManager();
    addonMgr.registerDefaultLoader(nullptr);
    instance->initialize();
    dispatcher = std::make_unique<fcitx::EventDispatcher>();
    dispatcher->attach(&instance->eventLoop());
    instance->eventLoop().exec();
}
} // namespace fcitx

int main() {
    fcitx::start();
    return 0;
}
