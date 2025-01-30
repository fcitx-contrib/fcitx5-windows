#include <fcitx-utils/event.h>
#include <fcitx-utils/eventdispatcher.h>
#include <fcitx/instance.h>

namespace fcitx {
std::unique_ptr<Instance> instance;
std::unique_ptr<fcitx::EventDispatcher> dispatcher;

void start() {
    instance = std::make_unique<Instance>(0, nullptr);
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
