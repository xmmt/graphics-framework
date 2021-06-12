#pragma once

#include <Game.hpp>
#include <GameComponent.hpp>

namespace GraphicsFramework {

class Triangles : public Game {
public:
    Triangles(Renderer const& renderer, InputDevice const& inputDevice);
    ~Triangles() override = default;

private:
    void runFrame_(float delta) override;
    void run_() override;
    void init_() override;
    void destroy_() override;

private:
    std::vector<std::shared_ptr<GameComponent>> components_;
};

} // namespace GraphicsFramework