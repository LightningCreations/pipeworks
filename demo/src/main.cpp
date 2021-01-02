#include <memory>
#include <engine.hpp>
#include <renderer.hpp>
#include <sdlrenderer.hpp>

using namespace pipeworks;

int main() {
    std::unique_ptr<Renderer> renderer{new SDLRenderer()};
    Engine engine{std::move(renderer)};
}
