#ifndef FOTC_SHIP_HPP
#define FOTC_SHIP_HPP

#include <cstdint>
#include <string>

#include <engine.hpp>
#include <scene.hpp>
#include <objects/emitter.hpp>
#include <objects/sprite.hpp>

using namespace pipeworks;

namespace fotc {

class Ship : public Sprite {
  private:
    float m_vx;
    float m_vy;
    int16_t m_rot;
    Emitter m_rear_thruster;
  public:
    Ship(float x, float y, float z, std::string name, Engine &engine, Scene &scene, bool is_player);
    void move_player_ship(void *data, EventType event_type, Engine &engine);
    float world_x(); // Why these aren't API yet, I don't know.
    float world_y(); // Wait, I do know. It's because it's 9 PM and I need this to work.
};

}

#endif // FOTC_SHIP_HPP
