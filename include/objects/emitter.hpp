#ifndef PW_OBJECTS_EMITTER_HPP
#define PW_OBJECTS_EMITTER_HPP

#include <random>
#include <vector>
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

struct Particle {
    float timer;
    float x;
    float y;
    float v;
    float dv;
    float ddv;
    float t;
    float dt;
    float ddt;
    float r;
    float dr;
    float ddr;
    float g;
    float dg;
    float ddg;
    float b;
    float db;
    float ddb;
};

class Emitter : public GameObject {
  private:
    bool m_enabled;
    float m_lifetime;
    ParticleParameter m_v;
    ParticleParameter m_t;
    ParticleParameter m_r;
    ParticleParameter m_g;
    ParticleParameter m_b;
    std::vector<Particle> m_particles;
    std::minstd_rand m_rng;
  public:
    /// \brief Create a new emitter
    Emitter(float x, float y, float z,
        float lifetime, ParticleParameter v, ParticleParameter t, ParticleParameter r, ParticleParameter g, ParticleParameter b);
    /// \brief Enable or disable the emitter
    void set_enabled(bool enabled);
    void set_v(ParticleParameter);
    void set_t(ParticleParameter);
    void set_r(ParticleParameter);
    void set_g(ParticleParameter);
    void set_b(ParticleParameter);
    void render(Renderer&);
};

} // namespace pipeworks

#endif // PW_OBJECTS_EMITTER_HPP
