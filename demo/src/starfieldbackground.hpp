#ifndef FOTC_STARFIELDBACKGROUND_HPP
#define FOTC_STARFIELDBACKGROUND_HPP

#include <gameobject.hpp>

#define STARFIELD_NUM_STARS 1000

using namespace pipeworks;

namespace fotc {

class StarfieldBackground: public GameObject {
  private:
    float x;
    float y;
    // float z;
    float starx[STARFIELD_NUM_STARS];
    float stary[STARFIELD_NUM_STARS];
    float starz[STARFIELD_NUM_STARS];
  public:
    StarfieldBackground(float x, float y, float z) noexcept;
    void render(Renderer&);
};

}

#endif // FOTC_STARFIELDBACKGROUND_HPP
