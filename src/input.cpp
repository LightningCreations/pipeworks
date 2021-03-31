#include <input.hpp>
#include <engine.hpp>
#include <event.hpp>
#include <memory>

namespace pipeworks {
    InputManager::InputManager(Engine &e) {
        e.register_event(std::make_unique<Event>(EventType::KeyUp | EventType::KeyDown,
            [](void *udata, void *event, EventType t, Engine &engine) {
                static_cast<void>(&engine);
                auto self = (InputManager*) udata;
                auto key = (KeyCode*) event;
                if(t != EventType::KeyUp)
                    self->keys.insert(*key);
                else
                    self->keys.erase(*key);
            }, this));
    }

    bool InputManager::is_key_pressed(KeyCode k) {
        return this->keys.contains(k);
    }
} // namespace pipeworks
