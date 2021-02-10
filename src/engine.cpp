#include <engine.hpp>
#include <resourcemanager.hpp>

extern "C" {

#include <stb_image.h>

}

#include <whereami.h>

namespace pipeworks {

Engine::Engine(std::unique_ptr<Renderer> renderer): renderer(std::move(renderer)), active_load_threads(0) {
    this->renderer->set_active_scene_list(&active_scenes);
    this->renderer->set_width(1280);
    this->renderer->set_height(720);
}

void Engine::set_init_scene(std::unique_ptr<Scene> scene) {
    init_scene = std::move(scene);
}

void Engine::start0() {
    renderer->open_window();
    while(running) {
        if(pending_scene) {
            if(load_tasks.empty() && !active_load_threads) {
                for(GameObject *obj : pending_scene->get_objects()) {
                    obj->finished_loading();
                }
                activate_scene(*pending_scene);
                pending_scene = nullptr;
            } else { // This method does add an extra frame of lag on loading, but oh well
                for(; active_load_threads < 4 && !load_tasks.empty(); active_load_threads++) {
                    std::thread load_thread(&Engine::load_resource, this, load_tasks.top());
                    load_thread.detach();
                    load_tasks.pop();
                }
            }
        }
        renderer->render_poll();
        if(renderer->is_close_requested()) running = false;
        renderer->sync(60); // 60 FPS default
    }
    renderer->close_window();
}

void Engine::load_resource(std::string resource) {
    // TODO: Not all resources are images.
    // ... but right now, they are.
    if(g_resourcemanager.is_image_data_loaded(resource)) {
        active_load_threads--;
        return;
    }

    // TODO: Support additional loading locations (currently only supports "assets/<resource>")
    // TODO: Cache executable path
    int pathlen, dirnamelen;
    char *path = new char[pathlen = wai_getExecutablePath(nullptr, 0, nullptr)];
    wai_getExecutablePath(path, pathlen, &dirnamelen);
    path[dirnamelen] = '\0';
    // TODO: Support images that aren't 32bpp more efficiently
    int x, y, _n;
    uint8_t *data = stbi_load((std::string(path) + "/assets/" + resource).c_str(), &x, &y, &_n, 4);
    g_resourcemanager.put_image_data(resource, new ImageData(x, y, data));
    // FIXME: Resource leak: data is never freed (needs `stbi_free(data)`)

    delete[] path;
    active_load_threads--;
}

void Engine::start() {
    activate_scene(*init_scene);
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
    if(scene.is_loaded()) {
        deactivate_scene0(scene); // Deactivate the scene (without notification) if it already exists; otherwise do nothing
        active_scenes.push_back(scene);
        scene.activate();
    } else {
        if(load_scene) activate_scene(*load_scene);
        for(GameObject *object : scene.get_objects()) {
            for(std::string resource : object->get_loadable_resources()) {
                load_tasks.push(resource);
            }
        }
        pending_scene = &scene;
    }
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
