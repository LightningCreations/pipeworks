#include "gameobject.hpp"

namespace pipeworks {

std::vector<std::string> GameObject::empty_resource_list;

GameObject::GameObject(float x, float y, float z): m_x(x), m_y(y), m_scene(nullptr) {
    (void) z;
}

GameObject::~GameObject() {}

float GameObject::x() const {
    if(!m_scene) return m_x;
    return m_x + m_scene->camera_x();
}

float GameObject::y() const {
    if(!m_scene) return m_y;
    return m_y + m_scene->camera_y();
}

void GameObject::set_x(float x) {
    m_x = x;
}

void GameObject::set_y(float y) {
    m_y = y;
}

void GameObject::bind_scene(const Scene &scene) {
    m_scene = &scene;
}

} // namespace pipeworks
