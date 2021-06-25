#ifndef PW_OBJECTS_BGM_HPP
#define PW_OBJECTS_BGM_HPP

#include "../audiodata.hpp"
#include "../gameobject.hpp"

namespace pipeworks {

class BGM : public GameObject {
  private:
    Engine &m_engine;
    const AudioData *m_data;
    std::vector<std::string> m_resources;
    uint64_t m_loop_start;
    uint64_t m_loop_end;
    bool m_loaded;
  public:
    BGM(Engine &engine, const AudioData &data, uint64_t loop_start, uint64_t loop_end);
    BGM(Engine &engine, std::string resource, uint64_t loop_start, uint64_t loop_end);
    void finished_loading();
    bool is_loading();
    std::vector<std::string>& loadable_resources();
    void play();
    void render(Renderer &renderer);
};

}

#endif // PW_OBJECTS_BGM_HPP
