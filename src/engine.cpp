#include <engine.hpp>
#include <resourcemanager.hpp>

#include <stb_image.h>
#include <whereami.h>

namespace pipeworks {

struct EventBuffer{
    EventType type;
    void* udata;
};

Engine::Engine(std::unique_ptr<Renderer> renderer): m_renderer(std::move(renderer)), m_active_load_threads(0), m_eventQueue{64*sizeof(EventBuffer)} {
    m_renderer->set_active_scene_list(&m_active_scenes);
    m_renderer->set_active_engine(this);
    m_renderer->set_width(1280);
    m_renderer->set_height(720);
}

void Engine::set_init_scene(std::unique_ptr<Scene> scene) {
    m_init_scene = std::move(scene);
}

void Engine::start0() {
    m_renderer->open_window();
    while(m_running) {
        fire_event(EventType::Frame, nullptr); // No data for start-of-frame yet
        EventBuffer buff;
        while(this->m_eventQueue.get(buff))
            this->fire_event0(buff.type,buff.udata);
        if(m_pending_scene) {
            if(m_load_tasks.empty() && !m_active_load_threads) {
                for(GameObject *obj : m_pending_scene->objects()) {
                    obj->finished_loading();
                }
                activate_scene(*m_pending_scene);
                m_pending_scene = nullptr;
            } else { // This method does add an extra frame of lag on loading, but oh well
                for(; m_active_load_threads < 4 && !m_load_tasks.empty(); m_active_load_threads++) {
                    std::thread load_thread(&Engine::load_resource, this, m_load_tasks.top());
                    load_thread.detach();
                    m_load_tasks.pop();
                }
            }
        }
        fire_event(EventType::FrameEnd, nullptr); // No data for end-of-frame yet
        m_renderer->render_poll();
        if(m_renderer->is_close_requested()) m_running = false;
        m_renderer->sync(60); // 60 FPS default
    }
    m_renderer->close_window();
}

void Engine::load_resource(std::string resource) {
    // TODO: Not all resources are images.
    // ... but right now, they are.
    if(g_resourcemanager.is_image_data_loaded(resource)) {
        m_active_load_threads--;
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
    m_active_load_threads--;
}

void Engine::start() {
    activate_scene(*m_init_scene);
    m_engine_thread = std::thread(&Engine::start0, this);
    m_running = true;
}

void Engine::stop() {
    m_running = false;
}

void Engine::join() {
    m_engine_thread.join();
}

bool Engine::is_running() {
    return m_running;
}

void Engine::activate_scene(Scene &scene) {
    if(scene.is_loaded()) {
        deactivate_scene0(scene); // Deactivate the scene (without notification) if it already exists; otherwise do nothing
        m_active_scenes.push_back(scene);
        scene.activate();
    } else {
        if(m_load_scene) activate_scene(*m_load_scene);
        for(GameObject *object : scene.objects()) {
            for(std::string resource : object->loadable_resources()) {
                m_load_tasks.push(resource);
            }
        }
        m_pending_scene = &scene;
    }
}

void Engine::deactivate_scene(Scene &scene) {
    deactivate_scene0(scene);
    scene.deactivate();
}

void Engine::deactivate_scene0(Scene &scene) {
    for(auto it = m_active_scenes.begin(); it != m_active_scenes.end(); it++) {
        if((*it).id() == scene.id()) {
            m_active_scenes.erase(it);
            break;
        }
    }
}

void Engine::register_event(std::unique_ptr<Event> event) {
    m_events.push_back(*event);
}

void Engine::fire_event0(EventType type, void *data) {
    for(Event e : m_events) {
        if((type & e.m_type)!=EventType{}) e.call(data,type,*this);
    }
}

void Engine::fire_event(EventType type,void *data){
    this->m_eventQueue.put(EventBuffer{type,data});
}


Renderer& Engine::renderer() {
    return *m_renderer;
}
InputManager& Engine::input_manager(){
    if(!this->m_inputMan){
        this->m_inputMan.emplace(*this,pipeworks::_token{});
    }
    return *this->m_inputMan;
}

}
