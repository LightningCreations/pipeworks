#ifndef PW_IMAGEDATA_HPP
#define PW_IMAGEDATA_HPP

#include <cstdint>

namespace pipeworks {

class ImageData {
  private:
    uint32_t width;
    uint32_t height;
    uint8_t *data;
  public:
    ImageData(uint32_t width, uint32_t height, uint8_t *data);
    uint32_t get_width();
    uint32_t get_height();
    uint8_t *get_data();
};

}

#endif // PW_IMAGEDATA_HPP
