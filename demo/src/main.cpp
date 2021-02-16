#include <cmath>
#include <memory>

#include <engine.hpp>
#include <renderer.hpp>
#include <scene.hpp>
#include <objects/sprite.hpp>

#include "starfieldbackground.hpp"

#include <sdlrenderer.hpp>

using namespace pipeworks;
using namespace fotc;

Engine *enginep;
StarfieldBackground *bgp;

float shipx = 0, shipy = 0;
float shipvx = 0, shipvy = 0; // Velocity X, velocity Y
int16_t shiprot = 90;

const float DEG_TO_RAD = 180.0f / 3.1415926536f;

void move_player_ship(void *obj, void *data,EventType,Engine& e) {
    Renderer &renderer = enginep->renderer();
    Sprite &ship = *((Sprite*) obj);
    StarfieldBackground &bg = *bgp;

    float accel = (renderer.key_down('d') - renderer.key_down('a')) * 0.001f;
    int8_t rot = renderer.key_down('s') - renderer.key_down('w');
    shiprot += rot;
    if(shiprot < 0) shiprot = 0;
    if(shiprot > 180) shiprot = 180;
    ship.set_frame(shiprot);

    float angle = shiprot * DEG_TO_RAD;
    float ax = sin(angle) * accel;
    float ay = cos(angle) * accel;

    shipvx += ax;
    shipvy += ay;

    shipx += shipvx;
    shipy += shipvy;

    bg.set_x(-shipx);
    bg.set_y(-shipy);
}

int main(int argc, char *argv[]) {
    SDLRenderer renderer;
    Engine engine{std::unique_ptr<Renderer>(&renderer)};
    enginep = &engine;

    Scene title_scene{};

    std::vector<std::string> ship_frames;
    Sprite ship(-0.2f, -0.2f, 1, 0.4f, 0.4f, ship_frames);
    engine.register_event(std::unique_ptr<Event>(new Event(EventType::Frame, &move_player_ship, &ship)));
    title_scene.add_object(&ship);

    StarfieldBackground bg(100000, engine); // farthest back
    title_scene.add_object(&bg);

    engine.set_init_scene(std::make_unique<Scene>(title_scene));

    engine.start();
    engine.join(); // Wait for stop
}
