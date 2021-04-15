#ifndef FOTC_BLASTER_HPP
#define FOTC_BLASTER_HPP

#include <gameobject.hpp>

namespace fotc {

class Blaster : public pipeworks::GameObject {
  private:
    int m_cur_laser;
    float m_laser_x[128];
    float m_laser_y[128];
    float m_laser_vx[128];
    float m_laser_vy[128];
    bool m_laser_active[128];
    float m_vx;
    float m_vy;
  public:
    Blaster(float x, float y, float z);
    void render(pipeworks::Renderer &renderer) override;
    void fire();
    void set_vx(float vx);
    void set_vy(float vy);
};

}

#endif // FOTC_BLASTER_HPP
