#include <memory>

#include <engine.hpp>
#include <renderer.hpp>
#include <scene.hpp>

#include "starfieldbackground.hpp"

#include <sdlrenderer.hpp>

using namespace pipeworks;
using namespace fotc;

int main(int argc, char *argv[]) {
    std::unique_ptr<Renderer> renderer{new SDLRenderer()};
    Engine engine{std::move(renderer)};

    Scene title_scene{};
    title_scene.add_object(new StarfieldBackground(0, 0, 100000)); // farthest back
    engine.set_init_scene(std::make_unique<Scene>(title_scene));

    engine.start();
    engine.join(); // Wait for stop
}
