#include <engine.hpp>

namespace pipeworks {

Engine::Engine(std::unique_ptr<Renderer> renderer): renderer(std::move(renderer)) {}

}
