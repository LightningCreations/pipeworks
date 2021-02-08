#include <imagedata.hpp>

namespace pipeworks {

ImageData::ImageData(uint32_t width, uint32_t height, uint8_t *data): width(width), height(height), data(data) {}

uint32_t ImageData::get_width() {
    return width;
}

uint32_t ImageData::get_height() {
    return height;
}

uint8_t *ImageData::get_data() {
    return data;
}

}
