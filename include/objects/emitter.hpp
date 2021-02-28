#ifndef PW_OBJECTS_EMITTER_HPP
#define PW_OBJECTS_EMITTER_HPP

#include "gameobject.hpp"

namespace pipeworks {

struct ParticleParameter {
    /// \brief Starting value
    float v;
    /// \brief Spread of v
    float sv;
    /// \brief Change in v over time (velocity)
    float dv;
    /// \brief Spread of dv
    float sdv;
    /// \brief Change in dv over time (acceleration)
    float ddv;
    /// \brief Spread of ddv
    float sddv;
};

class Emitter : public GameObject {
  private:
    bool m_enabled;
    float m_lifetime;
    ParticleParameter m_posx;
    ParticleParameter m_posy;
    ParticleParameter m_r;
    ParticleParameter m_g;
    ParticleParameter m_b;
  public:
    /// \brief Create a new emitter
    Emitter(float x, float y, float z,
        float lifetime, ParticleParameter posx, ParticleParameter posy, ParticleParameter r, ParticleParameter g, ParticleParameter b);
    /// \brief Enable or disable the emitter
    void set_enabled(bool enabled);
};

} // namespace pipeworks

#endif // PW_OBJECTS_EMITTER_HPP
