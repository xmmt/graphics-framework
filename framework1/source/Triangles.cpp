#include <Triangles.hpp>

using namespace GraphicsFramework;

Triangles::Triangles(Renderer const& renderer, InputDevice const& inputDevice)
    : Game{ renderer, inputDevice } {
}

void Triangles::runFrame_(float delta) {
    renderer_.prepareFrame();
    renderer_.endFrame();
}

void Triangles::run_() {
    // renderer_.prepareFrame();
    // renderer_.endFrame();
}

void Triangles::init_() {
}

void Triangles::destroy_() {
}