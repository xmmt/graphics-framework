#include <TriangleComponent.hpp>

using namespace GraphicsFramework;

TriangleComponent::TriangleComponent(
  Renderer& renderer,
  Buffer<Vertex> vertices,
  Buffer<Color> colors,
  Material& material)
    : GameComponent{ renderer }
    , vertices_{ std::move(vertices) }
    , colors_{ std::move(colors) }
    , indices_{ 0, 1, 2 }
    , material_{ material } {
}

TriangleComponent::~TriangleComponent() {
}

void TriangleComponent::destroyResources() {
}

void TriangleComponent::draw() {
    renderer_.draw(vertices_, colors_, indices_, material_);
}

void TriangleComponent::initialize() {
}

void TriangleComponent::reload() {
}

void TriangleComponent::update() {
}