#ifndef PW_EVENT_HPP
#define PW_EVENT_HPP

namespace pipeworks {

/// \brief Specifies what particular event is being listened to. (used by Event)
enum EventType {
    /// \brief Beginning of frame, called after \ref Renderer::render_poll "render_poll"
    FRAME = 1,
    /// \brief End of frame, called before \ref Renderer::render_poll "render_poll"
    FRAMEEND = 2,
    /// \brief Key has just been pressed, or is being repeated by the OS
    KEYDOWN = 4,
    /// \brief Key has just been released
    KEYUP = 8,
    /// \brief Listen to all events
    ALL = 0xF
};

/// \brief Defines a response to a particular event.
struct Event {
  private:
    void *m_data;
    void(*m_callback)(void*,void*); // Gosh darn function pointers.
  public:
    /// \brief All events that can be responded to, as a bitmask.
    EventType m_type;
    /// \brief Create a new event listener.
    /// \param type The type(s) of event to react to.
    /// \param callback The function to be called upon the event triggering.
    /// \param data User-defined data to be passed as the first parameter. This will often be a class.
    ///
    /// Multiple events can be reacted to with the same function by ORing together multiple values of EventType
    ///
    /// The callback takes two `void*` as parameters. The first is the user-defined data, while the second is an event-specific data structure.
    Event(EventType type, void(*callback)(void*,void*), void *data);
    /// \brief Call the event listener.
    /// \param eventdata The event-specific data.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void call(void *eventdata);
};

} // namespace pipeworks

#endif // PW_EVENT_HPP
