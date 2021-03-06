#include <memory>

#include <engine.hpp>
#include <renderer.hpp>
#include <scene.hpp>
#include <objects/bgm.hpp>
#include <objects/sprite.hpp>

#include "starfieldbackground.hpp"
#include "ship.hpp"

#include <defaultaudiomixer.hpp>
#include <sdlaudioplayer.hpp>
#include <sdlrenderer.hpp>

using namespace pipeworks;
using namespace fotc;

Ship *player_shipp;

void update_camera(void *obj, void *data, EventType event_type, Engine &engine) {
    Scene &scene = *((Scene*) obj);
    scene.set_camera_x(-player_shipp->world_x());
    scene.set_camera_y(-player_shipp->world_y());
}

int main(int argc, char *argv[]) {
    Engine engine{std::make_unique<SDLRenderer>(), std::make_unique<SDLAudioPlayer>(), std::make_unique<DefaultAudioMixer>()};
    Scene scene{};

    std::vector<std::string> ship_frames;

    StarfieldBackground bg(100000, engine); // farthest back
    scene.add_object(&bg);

    Ship player_ship(0, 0, 1, "ship", engine, scene, true);
    player_shipp = &player_ship;
    scene.add_object(&player_ship);

    BGM lvl1(engine, "lvl1.flac", 460800, 2304000);
    scene.add_object(&lvl1);

    engine.register_event(std::make_unique<Event>(Event(EventType::Frame, &update_camera, &scene)));

    engine.set_init_scene(std::make_unique<Scene>(scene));

    engine.start();
    engine.join(); // Wait for stop
}
