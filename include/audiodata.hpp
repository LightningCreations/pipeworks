#ifndef PW_AUDIODATA_HPP
#define PW_AUDIODATA_HPP

#include <vector>

namespace pipeworks {

class AudioData {
  private:
    const std::vector<float> m_data;
  public:
    AudioData(std::vector<float> data): m_data(data) {}

    const std::vector<float>& data() { return m_data; }
};

}

#endif // PW_AUDIODATA_HPP
