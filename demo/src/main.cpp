#include <memory>

#include <engine.hpp>
#include <renderer.hpp>
#include <scene.hpp>

#include <sdlrenderer.hpp>

using namespace pipeworks;

int main(int argc, char *argv[]) {
    std::unique_ptr<Renderer> renderer{new SDLRenderer()};
    Engine engine{std::move(renderer)};

    Scene title_scene{};
    // TODO: Set up scene
    engine.set_init_scene(std::make_unique<Scene>(title_scene));

    engine.start();
    engine.join(); // Wait for stop
}
