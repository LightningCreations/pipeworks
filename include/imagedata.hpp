#ifndef PW_IMAGEDATA_HPP
#define PW_IMAGEDATA_HPP

#include <cstdint>

namespace pipeworks {

/// \brief Implementation defined image data format
class ImageData {
  private:
    const uint32_t m_width;
    const uint32_t m_height;
    const uint8_t *m_data;
  public:
    /// \brief Create new ImageData.
    /// \param width The width of the image.
    /// \param height The height of the image.
    /// \param data A representation of the image in an implementation-defined format.
    ImageData(const uint32_t width, const uint32_t height, const uint8_t *data);
    /// \brief Get the width of the image.
    /// \return The width of the image in pixels.
    const uint32_t width() const;
    /// \brief Get the height of the image.
    /// \return The height of the image in pixels.
    const uint32_t height() const;
    /// \brief Get the internal representation of the image.
    /// \return The internal representation of the image in an implementation-defined format.
    ///
    /// The internal representation of images may be stabilized eventually; currently, there are many improvements that can be made.
    const uint8_t *data() const;
    /// \brief Get the size of the data array.
    /// \return The size of the data array in bytes.
    const uint32_t size() const;
};

}

#endif // PW_IMAGEDATA_HPP
