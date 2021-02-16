#include <event.hpp>

namespace pipeworks {

Event::Event(EventType type, void(*callback)(void*,void*,EventType,Engine&), void *data): m_data(data), m_callback(callback), m_type(type) {}

void Event::call(void *eventdata,EventType t,Engine& e) {
    m_callback(m_data, eventdata,t,e);
}

} // namespace pipeworks
