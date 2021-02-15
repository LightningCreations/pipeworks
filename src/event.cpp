#include <event.hpp>

namespace pipeworks {

Event::Event(EventType type, void(*callback)(void*,void*), void *data): m_data(data), m_callback(callback), m_type(type) {}

void Event::call(void *eventdata) {
    m_callback(m_data, eventdata);
}

} // namespace pipeworks
