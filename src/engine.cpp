#include <engine.hpp>
#include <resourcemanager.hpp>

#include <chrono>
#include <iomanip>
#include <iostream>

#include <dr_flac.h>
#include <stb_image.h>
#include <whereami.h>

#define DISPLAY_FPS true

namespace pipeworks {

// Source: https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
// This would be constexpr, but GCC doesn't support it
static inline bool ends_with(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

struct EventBuffer {
    EventType type;
    void* udata;
};

void engine_audio_callback_wrap(void *userdata, float *data, int len) {
    ((Engine*) userdata)->audio_callback(data, len/4); // Because SDL. I'll fix the SDL side later.
}

Engine::Engine(std::unique_ptr<Renderer> renderer, std::unique_ptr<AudioPlayer> audio_player, std::unique_ptr<AudioMixer> audio_mixer): m_audio_mixer(std::move(audio_mixer)), m_audio_player(std::move(audio_player)), m_renderer(std::move(renderer)), m_active_load_threads(0), m_eventQueue{64*sizeof(EventBuffer)} {
    m_renderer->set_active_scene_list(&m_active_scenes);
    m_renderer->set_active_engine(this);
    m_renderer->set_width(1280);
    m_renderer->set_height(720);
    m_audio_player->set_callback(engine_audio_callback_wrap, (void*) this);
}

void Engine::audio_callback(float *data, int len) {
    if(m_audio_mixer) m_audio_mixer->fill_buffer(data, len);
}

void Engine::set_init_scene(std::unique_ptr<Scene> scene) {
    m_init_scene = std::move(scene);
}

static const auto one_second = std::chrono::seconds(1);

static char *exe_path = nullptr;

void Engine::start0() {
    if(!exe_path) {
        int pathlen, dirnamelen;
        exe_path = new char[pathlen = wai_getExecutablePath(nullptr, 0, nullptr)];
        wai_getExecutablePath(exe_path, pathlen, &dirnamelen);
        exe_path[dirnamelen] = '\0';
    }
    m_renderer->open_window();
    int fc = 0;
    auto start = std::chrono::steady_clock::now();
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
        m_audio_player->tick(); // Get the audio response out ASAP; it *will* be behind video
        m_renderer->render_poll();
        if(m_renderer->is_close_requested()) m_running = false;
        m_renderer->sync(60); // 60 FPS default
        fc++;
        auto cur_time = std::chrono::steady_clock::now();
        auto dur = cur_time - start;
        if(dur >= one_second) {
            if(DISPLAY_FPS) {
                auto dur_ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
                std::cout << "FPS: " << std::setprecision(4) << (fc*1000.0f/dur_ms) << std::endl;
            }
            start = cur_time;
            fc = 0;
        }
    }
    m_renderer->close_window();
    delete[] exe_path;
    exe_path = nullptr;
}

void Engine::load_resource(std::string resource) {
    // TODO: Not all resources are images.
    // ... but right now, they are.
    if(ends_with(resource, ".png")) {
        if(g_resourcemanager.is_image_data_loaded(resource)) {
            m_active_load_threads--;
            return;
        }

        // TODO: Support additional loading locations (currently only supports "assets/<resource>")
        // TODO: Support images that aren't 32bpp more efficiently
        int x, y, _n;
        uint8_t *data = stbi_load((std::string(exe_path) + "/assets/" + resource).c_str(), &x, &y, &_n, 4);
        g_resourcemanager.put_image_data(resource, new ImageData(x, y, data, (const void(*)(void*)) stbi_image_free));

        m_active_load_threads--;
    } else if(ends_with(resource, ".flac")) {
        if(g_resourcemanager.is_audio_data_loaded(resource)) { 
            m_active_load_threads--;
            return;
        }
        unsigned int channels, sample_rate;
        drflac_uint64 frame_count;
        float *data = drflac_open_file_and_read_pcm_frames_f32((std::string(exe_path) + "/assets/" + resource).c_str(),
                        &channels, &sample_rate, &frame_count, nullptr);

        std::vector<float> result_data;
        // For now, we shall ignore sample_rate
        (void) sample_rate;
        // Because it will be painful to convert that.
        for(uint64_t i = 0; i < frame_count; i++) {
            if(channels == 1) {
                result_data.push_back(data[i]);
                result_data.push_back(data[i]);
            } else { // Assuming nobody is giving us 4+ channel FLACs right now
                result_data.push_back(data[i*2]);
                result_data.push_back(data[i*2+1]);
            }
        }

        drflac_free(data, nullptr);
        g_resourcemanager.put_audio_data(resource, new AudioData(result_data));

        m_active_load_threads--;
    } else {
        std::abort();
    }
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

void Engine::set_bgm(const AudioData *data, uint64_t loop_start, uint64_t loop_end) {
    m_audio_mixer->set_bgm(data, loop_start, loop_end);
}

void Engine::add_sfx(const AudioData *data) {
    m_audio_mixer->add_sfx(data);
}

void Engine::play_sfx(const AudioData *data) {
    m_audio_mixer->play_sfx(data);
}

}
