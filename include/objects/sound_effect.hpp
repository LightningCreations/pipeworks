#ifndef PW_OBJECTS_SOUND_EFFECT_HPP
#define PW_OBJECTS_SOUND_EFFECT_HPP

#include "../audiodata.hpp"
#include "../gameobject.hpp"

namespace pipeworks {

class SoundEffect : public GameObject {
  private:
    const AudioData &m_data;
    std::string m_resource;
    bool m_loaded;
  public:
    SoundEffect(const AudioData &data);
    SoundEffect(std::string resource);
    void finished_loading();
    bool is_loading();
    std::vector<std::string>& loadable_resources();
    void play();
};

}

#endif // PW_OBJECTS_SOUND_EFFECT_HPP
