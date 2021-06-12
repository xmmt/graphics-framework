#include <Renderer.hpp>

using namespace GraphicsFramework;

Renderer::Renderer(Display const& display)
    : initialized_{ false }
    , frameStarted_{ false }
    , display_{ display }
    , currentMaterial_{ nullptr } {
}

void Renderer::init() {
    if (initialized_) {
        throw std::runtime_error("renderer is already initialized");
    }
    init_();
    initialized_ = true;
}

void Renderer::destroy() {
    if (!initialized_) {
        throw std::runtime_error("renderer is not initialized");
    }
    destroy_();
    initialized_ = false;
}

void Renderer::runLoop(std::function<void(float)> runFrame) const {
    if (!initialized_) {
        throw std::runtime_error("renderer is not initialized");

    }
    display_.runLoop(runFrame);
}

void Renderer::prepareFrame() const {
    if (!initialized_) {
        throw std::runtime_error("renderer is not initialized");
    }
    if (frameStarted_) {
        throw std::runtime_error("frame is already started");
    }
    prepareFrame_();
    frameStarted_ = true;
}

void Renderer::endFrame() const {
    if (!initialized_) {
        throw std::runtime_error("renderer is not initialized");
    }
    if (!frameStarted_) {
        throw std::runtime_error("frame is not started");
    }

    if (!vertices_.empty()) {
        draw_(vertices_, colors_, indices_, *currentMaterial_);
        vertices_.clear();
        colors_.clear();
        indices_.clear();
    }

    endFrame_();
    frameStarted_ = false;
}

void Renderer::draw(
  Buffer<Vertex> const& vertices,
  Buffer<Color> const& colors,
  Buffer<int> const& indices,
  Material& material) const {
    if (!initialized_) {
        throw std::runtime_error("renderer is not initialized");
    }
    if (!frameStarted_) {
        throw std::runtime_error("frame is not started");
    }

    if (currentMaterial_ != &material) {
        draw_(vertices_, colors_, indices_, material);
        vertices_.clear();
        colors_.clear();
        indices_.clear();
    }

    std::copy(vertices.begin(), vertices.end(), std::back_inserter(vertices_));
    std::copy(colors.begin(), colors.end(), std::back_inserter(colors_));
    std::copy(indices.begin(), indices.end(), std::back_inserter(indices_));
}