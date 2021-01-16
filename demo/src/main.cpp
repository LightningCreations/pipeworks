#include <memory>

#include <engine.hpp>
#include <renderer.hpp>
#include <scene.hpp>

#include <objects/background.hpp>

#include <sdlrenderer.hpp>

using namespace pipeworks;

int main(int argc, char *argv[]) {
    std::unique_ptr<Renderer> renderer{new SDLRenderer()};
    Engine engine{std::move(renderer)};

    Scene title_scene{};
    title_scene.add_object(new Background(0, 0, 1)); // never give something a Z of 0
    engine.set_init_scene(std::make_unique<Scene>(title_scene));

    engine.start();
    engine.join(); // Wait for stop
}
