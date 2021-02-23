#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>

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

const float DEG_TO_RAD = 3.1415926536f / 180.0f;

void move_player_ship(void *obj, void *data,EventType,Engine& e) {
    Renderer &renderer = enginep->renderer();
    Sprite &ship = *((Sprite*) obj);
    StarfieldBackground &bg = *bgp;

    float accel = (renderer.is_key_down('d') - renderer.is_key_down('a')) * 0.02f;
    int8_t rot = renderer.is_key_down('s') - renderer.is_key_down('w');
    shiprot += rot;
    if(shiprot < 0) shiprot = 0;
    if(shiprot > 180) shiprot = 180;
    ship.set_frame(shiprot);

    float angle = shiprot * DEG_TO_RAD;
    float ax = sin(angle) * accel;
    float ay = cos(angle) * accel;

    shipvx += ax;
    shipvy += ay;

    float speedsq = shipvx*shipvx+shipvy*shipvy;
    if(speedsq > 1) {
        shipvx /= sqrt(speedsq);
        shipvy /= sqrt(speedsq);
    }

    shipx += shipvx;
    shipy += shipvy;

    bg.set_x(-shipx);
    bg.set_y(-shipy);
}

int main(int argc, char *argv[]) {
    SDLRenderer renderer;
    Engine engine{std::make_unique<SDLRenderer>(renderer)};
    enginep = &engine;

    Scene title_scene{};

    std::vector<std::string> ship_frames;

    for(int i = 0; i <= 180; i++) {
        // Please let std::format be implemented soon...
        // ship_frames.push_back(std::format("ship{:03}.png", i));
        // Instead, we have to do this:
        std::ostringstream formatter;
        formatter << "ship" << std::setw(3) << std::setfill('0') << i << ".png";
        ship_frames.push_back(formatter.str());
    }

    StarfieldBackground bg(100000, engine); // farthest back
    bgp = &bg;
    title_scene.add_object(&bg);

    Sprite ship(-0.2f, 0.2f, 1, 0.4f, 0.4f, ship_frames);
    engine.register_event(std::unique_ptr<Event>(new Event(EventType::Frame, &move_player_ship, &ship)));
    title_scene.add_object(&ship);

    engine.set_init_scene(std::make_unique<Scene>(title_scene));

    engine.start();
    engine.join(); // Wait for stop
}
