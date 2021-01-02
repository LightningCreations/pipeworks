#ifndef PW_ENGINE_HPP
#define PW_ENGINE_HPP

#include <memory>
#include "renderer.hpp"

namespace pipeworks {

class Engine {
  private:
    std::unique_ptr<Renderer> renderer;
  public:
    Engine(std::unique_ptr<Renderer> renderer);
};

}

#endif // PW_ENGINE_HPP
