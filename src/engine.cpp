#include <engine.hpp>

namespace pipeworks {

Engine::Engine(std::unique_ptr<Renderer> renderer): renderer(std::move(renderer)) {

}

void Engine::activate_scene(Scene &scene) {
    active_scenes.push_back(scene);
}

void Engine::deactivate_scene(Scene &scene) {
    for(auto it = active_scenes.begin(); it != active_scenes.end(); it++) {
        if((*it).get_id() == scene.get_id()) {
            active_scenes.erase(it);
            break;
        }
    }
}

void Engine::set_init_scene(std::unique_ptr<Scene> scene) {
    init_scene = std::move(scene);
}

void Engine::start() {
    // TODO: Start engine thread
    running = true;
}

}
