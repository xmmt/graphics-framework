#include <Display.hpp>

using namespace GraphicsFramework;

Display::Display(InputDevice& inputDevice)
    : inputDevice_{ inputDevice } {
}

void Display::addOnSizeUpdatedCallback(std::function<void(Size)> callback) {
    onSizeUpdatedCallbacks_.emplace_back(std::move(callback));
}

void Display::onSizeUpdated_(Size size) const {
    for (auto&& callback : onSizeUpdatedCallbacks_) {
        callback(size);
    }
}
