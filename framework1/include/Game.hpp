#pragma once

#include <Utils.hpp>
#include <Renderer.hpp>
#include <InputDevice.hpp>

namespace GraphicsFramework {

class Game {
public:
    Game(Renderer const& renderer, InputDevice const& inputDevice);
    virtual ~Game() = default;

public:
    virtual void run();
    virtual void init();
    virtual void destroy();

protected:
    virtual void runFrame_(float delta) = 0;
    virtual void run_() = 0;
    virtual void init_() = 0;
    virtual void destroy_() = 0;

protected:
    bool initialized_{ false };
    Renderer const& renderer_;
    InputDevice const& inputDevice_;
};

} // namespace GraphicsFramework
