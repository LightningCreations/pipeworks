#ifndef PW_AUDIOPLAYER_HPP
#define PW_AUDIOPLAYER_HPP

#include <cstdint>

namespace pipeworks {

/// \brief An audio player
class AudioPlayer {
  public:
    /// \brief Set the callback for audio generation.
    /// \pre This is expected to be run from the Engine on initialization, running any other time is undefined behavior.
    ///
    /// There is no guarantee on what thread will call the callback function.
    ///
    /// The parameters to the callback are, in order, the userdata passed to the function, a buffer to hold audio data, and the number of samples to store.
    virtual void set_callback(void(*callback)(void*,uint8_t*,int), void *userdata) = 0;
    /// \brief Tick the audio player.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    ///
    /// This function may be empty. If it has an implementation, it is likely to call the callback set by set_callback.
    virtual void tick() = 0;
    virtual ~AudioPlayer();
};

}

#endif // PW_AUDIOPLAYER_HPP
