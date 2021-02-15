#include <event.hpp>

namespace pipeworks {

Event::Event(EventType type, void(*callback)(void*,void*), void *data): m_data(data), m_type(type), m_callback(callback) {}

} // namespace pipeworks
