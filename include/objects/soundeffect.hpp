#ifndef PW_OBJECTS_SOUND_EFFECT_HPP
#define PW_OBJECTS_SOUND_EFFECT_HPP

#include "../audiodata.hpp"
#include "../gameobject.hpp"

namespace pipeworks {

class SoundEffect : public GameObject {
  private:
    Engine &m_engine;
    const AudioData *m_data;
    std::vector<std::string> m_resources;
    bool m_loaded;
  public:
    SoundEffect(Engine &engine, const AudioData &data);
    SoundEffect(Engine &engine, std::string resource);
    void finished_loading();
    bool is_loading();
    std::vector<std::string>& loadable_resources();
    void play();
    void render(Renderer &renderer);
};

}

#endif // PW_OBJECTS_SOUND_EFFECT_HPP
