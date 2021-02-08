#include <imagedata.hpp>

namespace pipeworks {

ImageData::ImageData(const uint32_t width, const uint32_t height, const uint8_t *data): m_width(width), m_height(height), m_data(data) {}

const uint32_t ImageData::width() const {
    return m_width;
}

const uint32_t ImageData::height() const {
    return m_height;
}

const uint8_t *ImageData::data() const {
    return m_data;
}

const uint32_t ImageData::size() const {
    return m_width * m_height * 4;
}

}
