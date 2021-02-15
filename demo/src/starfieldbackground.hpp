#ifndef FOTC_STARFIELDBACKGROUND_HPP
#define FOTC_STARFIELDBACKGROUND_HPP

#include <engine.hpp>
#include <gameobject.hpp>

#define STARFIELD_NUM_STARS 1000

using namespace pipeworks;

namespace fotc {

class StarfieldBackground: public GameObject {
  private:
    float prev_x;
    float prev_y;
    float x;
    float y;
    // float z;
    float starx[STARFIELD_NUM_STARS];
    float stary[STARFIELD_NUM_STARS];
    float starz[STARFIELD_NUM_STARS];
    Renderer *renderer;
  public:
    StarfieldBackground(float z, Engine &engine) noexcept;
    void render(Renderer&);
    void scroll(void*);
    void set_x(float x);
    void set_y(float y);
};

}

#endif // FOTC_STARFIELDBACKGROUND_HPP
