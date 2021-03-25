#ifndef PW_EVENT_HPP
#define PW_EVENT_HPP

namespace pipeworks {

class Engine;

/// \brief Specifies what particular event is being listened to. (used by Event)
enum class EventType {
    /// \brief Beginning of frame, called after \ref Renderer::render_poll "render_poll"
    Frame = 1,
    /// \brief End of frame, called before \ref Renderer::render_poll "render_poll"
    FrameEnd = 2,
    /// \brief Key has just been pressed, or is being repeated by the OS
    KeyDown = 4,
    /// \brief Key has just been released
    KeyUp = 8,
    /// \brief (Virtual) Key has just been pressed, or is being repeated by the OS
    VKeyDown = 0x10,
    /// \brief (Virtual) Key has just been released
    VKeyUp = 0x20,
    /// \brief Listen to all events
    All = 0xF
};

constexpr EventType operator|(EventType a,EventType b)noexcept{
  return EventType{static_cast<int>(a)|static_cast<int>(b)};
}
constexpr EventType operator&(EventType a,EventType b)noexcept{
  return EventType{static_cast<int>(a)&static_cast<int>(b)};
}
constexpr EventType operator~(EventType a)noexcept{
  return EventType{~static_cast<int>(a)}&EventType::All;
}

/// \brief Defines a response to a particular event.
struct Event {
  private:
    void *m_data;
    void(*m_callback)(void*,void*,EventType,Engine&); // Gosh darn function pointers.
    EventType m_type;
    friend class Engine;
  public:
    /// \brief Create a new event listener.
    /// \param type The type(s) of event to react to.
    /// \param callback The function to be called upon the event triggering.
    /// \param data User-defined data to be passed as the first parameter. This will often be a class.
    ///
    /// Multiple events can be reacted to with the same function by ORing together multiple values of EventType
    ///
    /// The callback takes two `void*` as parameters. The first is the user-defined data, while the second is an event-specific data structure.
    /// The other two fields should be self-explanatory: The EventType field passes the event type to repond to, and the Engine& field passes a copy of the Engine.
    ///
    /// The data shall be destructed after the Event has been processed, assuming data isn't a `nullptr`.
    Event(EventType type, void(*callback)(void*,void*,EventType,Engine&), void *data);
    /// \brief Call the event listener.
    /// \param eventdata The event-specific data.
    /// \param type The type of event to react to (useful for handlers that repond to multiple events).
    /// \param engine The running engine.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void call(void *eventdata, EventType type, Engine &engine);
};

} // namespace pipeworks

#endif // PW_EVENT_HPP
