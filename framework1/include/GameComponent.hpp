#pragma once

#include <Utils.hpp>
#include <Renderer.hpp>

namespace GraphicsFramework {

class GameComponent {
public:
    GameComponent(Renderer& renderer);
    virtual ~GameComponent() = default;

public:
    virtual void destroyResources() = 0;
    virtual void draw() = 0;
    virtual void initialize() = 0;
    virtual void reload() = 0;
    virtual void update() = 0;

protected:
    Renderer& renderer_;
};

} // namespace GraphicsFramework