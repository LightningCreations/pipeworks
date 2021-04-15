#include "blaster.hpp"

namespace fotc {

Blaster::Blaster(float x, float y, float z): GameObject(x, y, z) {
    m_cur_laser = 0;
    for(int i = 0; i < 128; i++) m_laser_active[i] = false;
}

void Blaster::render(pipeworks::Renderer &renderer) {
    (void) renderer;
}

void Blaster::set_vx(float vx) {
    m_vx = vx;
}

void Blaster::set_vy(float vy) {
    m_vy = vy;
}

void Blaster::fire() {
    m_laser_active[m_cur_laser] = true;
    m_laser_x[m_cur_laser] = m_x;
    m_laser_y[m_cur_laser] = m_y;
    m_laser_vx[m_cur_laser] = m_vx;
    m_laser_vy[m_cur_laser] = m_vy;
    ++m_cur_laser;
}

}
