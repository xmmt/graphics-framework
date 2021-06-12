#pragma once

#include <Utils.hpp>

namespace GraphicsFramework {

class InputDevice {
public:
    enum class Key : size_t {
        LEFT_MOUSE_BUTTON = 0,
        RIGHT_MOUSE_BUTTON,
        W,
        A,
        S,
        D,
        SPACEBAR,
        ESCAPE,
        ENTER,
        LEFT_SHIFT,
        LEFT_CTRL,
        _COUNT,
    };
    enum class EventType {
        PRESSED,
        RELEASED,
    };
    struct MousePosition {
        int x;
        int y;
    };

public:
    void addOnKeyPressedCallback(Key key, std::function<void()> callback);
    void addOnKeyReleasedCallback(Key key, std::function<void()> callback);
    void addOnMouseMoveCallback(std::function<void(MousePosition)> callback);
    void setKeyStateGetter(std::function<bool(Key)> callback);
    void setMousePositionGetter(std::function<std::tuple<int, int>()> callback);

public:
    void onKeyPressed(Key key) const;
    void onKeyReleased(Key key) const;
    void onMouseMove(MousePosition position) const;

public:
    bool isKeyPressed(Key key) const;
    std::tuple<int, int> getMousePosition() const;

private:
    std::unordered_multimap<Key, std::function<void()>> onKeyPressedCallbacks_;
    std::unordered_multimap<Key, std::function<void()>> onKeyReleasedCallbacks_;
    std::function<void(MousePosition)> onMouseMove_;
    std::function<bool(Key)> keyStateGetter_;
    std::function<std::tuple<int, int>()> mousePositionGetter_;
};

} // namespace GraphicsFramework