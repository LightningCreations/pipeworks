#include <memory>

#include <engine.hpp>
#include <renderer.hpp>
#include <scene.hpp>
#include <objects/sprite.hpp>

#include "starfieldbackground.hpp"

#include <sdlrenderer.hpp>

using namespace pipeworks;
using namespace fotc;

int main(int argc, char *argv[]) {
    std::unique_ptr<Renderer> renderer{new SDLRenderer()};
    Engine engine{std::move(renderer)};

    Scene title_scene{};
    title_scene.add_object(new StarfieldBackground(0, 0, 100000)); // farthest back
    title_scene.add_object(new Sprite(-0.2f, -0.2f, 1, 0.4f, 0.4f, std::vector<std::string>{std::string("ship090.png")})); // C++ boilerplate.
    engine.set_init_scene(std::make_unique<Scene>(title_scene));

    engine.start();
    engine.join(); // Wait for stop
}
