#include "ship.hpp"

#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>

namespace fotc {

static const float DEG_TO_RAD = 3.1415926536f / 180.0f;

static void mps_wrap(void *obj, void *data, EventType event_type, Engine &engine) {
    ((Ship*) obj)->move_player_ship(data, event_type, engine);
}

static void fire_wrap(void *obj, void *data, EventType event_type, Engine &engine) {
    (void) event_type;
    (void) engine;
    if(*((KeyCode*) data) == KeyCode::Space)
        ((Ship*) obj)->fire();
}

static inline float maxf(float a, float b) {
    return (a > b) ? a : b;
}

void Ship::move_player_ship(void *data, EventType event_type, Engine &engine) {
    float delta = 1.0f/60; // Temporary
    InputManager &input_manager = engine.input_manager();

    float accel = (input_manager.is_key_pressed(KeyCode::LetterD) - input_manager.is_key_pressed(KeyCode::LetterA)) * 4;
    int8_t rot = input_manager.is_key_pressed(KeyCode::LetterS) - input_manager.is_key_pressed(KeyCode::LetterW);
    m_rot += rot;
    if(m_rot < 0) m_rot = 0;
    if(m_rot > 180) m_rot = 180;
    set_frame(m_rot);

    float angle = m_rot * DEG_TO_RAD;
    float ax = sin(angle) * accel;
    float ay = cos(angle) * accel;

    m_vx += ax*delta;
    m_vy += ay*delta;

    float speed = sqrt(m_vx*m_vx+m_vy*m_vy);

    if(speed > 4) {
        m_vx /= speed / 4;
        m_vy /= speed / 4;
        speed = 4;
    }

    m_x += m_vx*delta;
    m_y += m_vy*delta;

    m_rear_thruster.set_enabled(input_manager.is_key_pressed(KeyCode::LetterD));
    m_rear_thruster.set_x(m_x-0.14f*sin(angle));
    m_rear_thruster.set_y(m_y-0.14f*cos(angle));
    m_rear_thruster.set_v(ParticleParameter{     -0.30f+speed, 0.10f, 0, 0, 0, 0});
    m_rear_thruster.set_t(ParticleParameter{atan2f(m_vy,m_vx), 0.02f, 0, 0, 0, 0});

    m_blaster.set_x(m_x+m_vx*delta+sin(angle)*0.08f);
    m_blaster.set_y(m_y+m_vy*delta+cos(angle)*0.08f);
    m_blaster.set_vx(m_vx+sin(angle)*6);
    m_blaster.set_vy(m_vy+cos(angle)*6);
}

static std::vector<std::string> get_frames_from_name(std::string name) {
    std::vector<std::string> ship_frames;
    for(int i = 0; i <= 180; i++) {
        // Please let std::format be implemented soon...
        // ship_frames.push_back(std::format("ship{:03}.png", i));
        // Instead, we have to do this:
        std::ostringstream formatter;
        formatter << name << std::setw(3) << std::setfill('0') << i << ".png";
        ship_frames.push_back(formatter.str());
    }
    return ship_frames;
}

Ship::Ship(float x, float y, float z, std::string name, Engine &engine, Scene &scene, bool is_player):
    Sprite(x, y, 1, 0.4f, 0.4f, get_frames_from_name(name)), m_vx(0), m_vy(0), m_rot(90),
    m_rear_thruster(
        x-0.14f, y, z, 0.2f,
        ParticleParameter{-0.30f, 0.10f,      0,      0,      0, 0},
        ParticleParameter{     0, 0.02f,      0,      0,      0, 0},
        ParticleParameter{  0.8f,  0.1f,  -2.0f,  0.04f, -0.32f, 0},
        ParticleParameter{  0.4f, 0.05f,  -1.0f,  0.02f, -0.16f, 0},
        ParticleParameter{  0.1f, 0.01f,  -0.3f, 0.005f, -0.04f, 0},
        32
    ), m_blaster(x, y, z) {
    if(is_player) {
	engine.register_event(std::make_unique<Event>(Event(EventType::Frame, &mps_wrap, this)));
        engine.register_event(std::make_unique<Event>(Event(EventType::KeyDown, &fire_wrap, this)));
    } else {
       // TODO
    }
    scene.add_object(&m_rear_thruster);
    scene.add_object(&m_blaster);
}

float Ship::world_x() {
    return m_x;
}

float Ship::world_y() {
    return m_y;
}

void Ship::fire() {
    m_blaster.fire();
}

}
