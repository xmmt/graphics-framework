#pragma once

#include <GameComponent.hpp>
#include <Material.hpp>

namespace GraphicsFramework {

class TriangleComponent : public GameComponent {
public:
    TriangleComponent(
      Renderer& renderer,
      Buffer<Vertex> vertices,
      Buffer<Color> colors,
      Material& material);
    ~TriangleComponent() override;

public:
    void destroyResources() override;
    void draw() override;
    void initialize() override;
    void reload() override;
    void update() override;

private:
    Buffer<Vertex> vertices_;
    Buffer<Color> colors_;
    Buffer<int> indices_{ 0, 1, 2 };
    Material& material_;
};

} // namespace GraphicsFramework