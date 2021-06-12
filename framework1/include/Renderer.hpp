#pragma once

#include <Display.hpp>
#include <Utils.hpp>
#include <Material.hpp>

#include <DirectXMath.h>

namespace GraphicsFramework {

template <typename T>
using Buffer = std::vector<T>;

// using Vertex = std::array<float, 4>;
using Vertex = DirectX::XMFLOAT4;

// using Color = std::array<float, N>;
using Color = DirectX::XMFLOAT4;

class Renderer {
public:
    Renderer(Display const& display);
    virtual ~Renderer() = default;

public:
    virtual void init();
    virtual void destroy();
    virtual void runLoop(std::function<void(float)> runFrame) const;
    virtual void prepareFrame() const;
    virtual void endFrame() const;
    virtual void draw(
      Buffer<Vertex> const& vertices,
      Buffer<Color> const& colors,
      Buffer<int> const& indices,
      Material& material) const;

protected:
    virtual void init_() = 0;
    virtual void destroy_() = 0;
    virtual void prepareFrame_() const = 0;
    virtual void endFrame_() const = 0;
    virtual void draw_(
      Buffer<Vertex> const& vertices,
      Buffer<Color> const& colors,
      Buffer<int> const& indices,
      Material& material) const = 0;

protected:
    bool initialized_{ false };
    mutable bool frameStarted_{ false };
    Display const& display_;
    Material* currentMaterial_{ nullptr };
    mutable Buffer<Vertex> vertices_;
    mutable Buffer<Color> colors_;
    mutable Buffer<int> indices_;
};

} // namespace GraphicsFramework