#include <engine.hpp>

namespace pipeworks {

Engine::Engine(std::unique_ptr<Renderer> renderer): renderer(std::move(renderer)) {

}

void Engine::set_init_scene(std::unique_ptr<Scene> scene) {
    init_scene = std::move(scene);
}

void Engine::start0() {
    renderer->open_window();
    while(running) {
        if(renderer->is_close_requested()) running = false;
        // FIXME: BUSY LOOP
    }
    renderer->close_window();
}

void Engine::start() {
    engine_thread = std::thread(&Engine::start0, this);
    running = true;
}

void Engine::stop() {
    running = false;
}

void Engine::join() {
    engine_thread.join();
}

bool Engine::is_running() {
    return running;
}

void Engine::activate_scene(Scene &scene) {
    deactivate_scene0(scene); // Deactivate the scene (without notification) if it already exists; otherwise do nothing
    active_scenes.push_back(scene);
    scene.activate();
}

void Engine::deactivate_scene(Scene &scene) {
    deactivate_scene0(scene);
    scene.deactivate();
}

void Engine::deactivate_scene0(Scene &scene) {
    for(auto it = active_scenes.begin(); it != active_scenes.end(); it++) {
        if((*it).get_id() == scene.get_id()) {
            active_scenes.erase(it);
            break;
        }
    }
}

}
