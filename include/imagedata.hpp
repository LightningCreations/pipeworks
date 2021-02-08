#ifndef PW_IMAGEDATA_HPP
#define PW_IMAGEDATA_HPP

#include <cstdint>

namespace pipeworks {

class ImageData {
  private:
    const uint32_t m_width;
    const uint32_t m_height;
    const uint8_t *m_data;
  public:
    ImageData(const uint32_t width, const uint32_t height, const uint8_t *data);
    const uint32_t width() const;
    const uint32_t height() const;
    const uint8_t *data() const;
    const uint32_t size() const;
};

}

#endif // PW_IMAGEDATA_HPP
