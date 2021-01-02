#include <memory>

#include <engine.hpp>
#include <renderer.hpp>
#include <scene.hpp>

#include <sdlrenderer.hpp>

using namespace pipeworks;

int main() {
    std::unique_ptr<Renderer> renderer{new SDLRenderer()};
    Engine engine{std::move(renderer)};

    Scene title_scene{};
    engine.activate_scene(title_scene);

    engine.deactivate_scene(title_scene);
}
