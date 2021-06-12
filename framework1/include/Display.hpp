#pragma once

#include <InputDevice.hpp>
#include <Utils.hpp>
#include <functional>

namespace GraphicsFramework {

class Display {
public:
    struct Size {
        std::uint32_t width;
        std::uint32_t height;
    };

public:
    Display(InputDevice& inputDevice);
    virtual ~Display() = default;

public:
    virtual void runLoop(std::function<void(float)> runFrame) const = 0;

public:
    virtual Size size() const = 0;
    virtual void show() = 0;
    virtual void setTitle(std::string title) = 0;

public:
    virtual void addOnSizeUpdatedCallback(std::function<void(Size)> callback);

protected:
    void onSizeUpdated_(Size size) const;


protected:
    InputDevice& inputDevice_;
    std::list<std::function<void(Size)>> onSizeUpdatedCallbacks_;
};

} // namespace GraphicsFramework