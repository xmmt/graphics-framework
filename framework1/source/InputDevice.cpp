#include <InputDevice.hpp>

using namespace GraphicsFramework;

void InputDevice::addOnKeyPressedCallback(Key key, std::function<void()> callback) {
    onKeyPressedCallbacks_.emplace(key, std::move(callback));
}

void InputDevice::addOnKeyReleasedCallback(Key key, std::function<void()> callback) {
    onKeyReleasedCallbacks_.emplace(key, std::move(callback));
}

void InputDevice::addOnMouseMoveCallback(std::function<void(MousePosition)> callback) {
    onMouseMove_ = std::move(callback);
}

void InputDevice::setKeyStateGetter(std::function<bool(Key)> callback) {
    keyStateGetter_ = std::move(callback);
}

void InputDevice::setMousePositionGetter(std::function<std::tuple<int, int>()> callback) {
    mousePositionGetter_ = std::move(callback);
}

void InputDevice::onKeyPressed(Key key) const {
    auto r = onKeyPressedCallbacks_.equal_range(key);
    for (auto it = r.first; it != r.second; std::advance(it, 1)) {
        it->second();
    }
}

void InputDevice::onKeyReleased(Key key) const {
    auto r = onKeyReleasedCallbacks_.equal_range(key);
    for (auto it = r.first; it != r.second; std::advance(it, 1)) {
        it->second();
    }
}

void InputDevice::onMouseMove(MousePosition position) const {
    if (onMouseMove_) {
        onMouseMove_(std::move(position));
    }
}

bool InputDevice::isKeyPressed(Key key) const {
    if (keyStateGetter_) {
        return keyStateGetter_(key);
    }
    throw std::runtime_error("onKeyState callback is not set");
}

std::tuple<int, int> InputDevice::getMousePosition() const {
    if (mousePositionGetter_) {
        return mousePositionGetter_();
    }
    throw std::runtime_error("onMousePosition callback is not set");
}