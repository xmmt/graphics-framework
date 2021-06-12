#include <Game.hpp>

using namespace GraphicsFramework;

Game::Game(Renderer const& renderer, InputDevice const& inputDevice)
    : initialized_{ false }
    , renderer_{ renderer }
    , inputDevice_{ inputDevice } {
}

void Game::run() {
    if (!initialized_) {
        throw std::runtime_error("game is not initialized");
    }
    run_();
    renderer_.runLoop([this](float delta) { runFrame_(delta); });
}

void Game::init() {
    if (initialized_) {
        throw std::runtime_error("game is already initialized");
    }
    init_();
    initialized_ = true;
}

void Game::destroy() {
    if (!initialized_) {
        throw std::runtime_error("game is not initialized");
    }
    destroy_();
    initialized_ = false;
}