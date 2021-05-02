#include "blaster.hpp"

namespace fotc {

Blaster::Blaster(float x, float y, float z): GameObject(x, y, z) {
    m_cur_laser = 0;
    for(int i = 0; i < 128; i++) m_laser_active[i] = false;
}

void Blaster::render(pipeworks::Renderer &renderer) {
    float delta = 1.f/60;
    for(int i = 0; i < 128; i++) {
        if(!m_laser_active[i]) continue;
        float next_sx = x() - m_x + m_laser_x[i];
        float next_sy = y() - m_y + m_laser_y[i];
        if(m_laser_sx[i] != 0 || m_laser_sy[i] != 0) {
            renderer.draw_line(m_laser_sx[i], m_laser_sy[i], next_sx, next_sy, 0.01f, 255, 0, 0, 255);
        }
        m_laser_sx[i] = next_sx;
        m_laser_sy[i] = next_sy;
        m_laser_x[i] += m_laser_vx[i]*delta;
        m_laser_y[i] += m_laser_vy[i]*delta;
    }
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
    m_laser_sx[m_cur_laser] = 0;
    m_laser_sy[m_cur_laser] = 0;
    ++m_cur_laser;
    if(m_cur_laser == 128)
        m_cur_laser = 0;
}

}
