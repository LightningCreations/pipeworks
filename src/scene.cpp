#include <scene.hpp>

namespace pipeworks {

Scene::Scene(): m_camera_x(0), m_camera_y(0) {
    static uint32_t s_max_scene_id = 0;
    s_max_scene_id++;
    m_id = s_max_scene_id;
}

uint32_t Scene::id() const {
    return m_id; // Thread safety later
}

void Scene::activate() {}

void Scene::deactivate() {}

std::vector<GameObject*> Scene::objects() const {
    return m_objects;
}

void Scene::add_object(GameObject *object) {
    m_objects.push_back(object);
    object->bind_scene(*this);
}

bool Scene::is_loaded() const {
    for(GameObject *object : m_objects) {
        if(!object->is_loaded()) return false;
    }
    return true;
}

float Scene::camera_x() const {
    return m_camera_x;
}

float Scene::camera_y() const {
    return m_camera_y;
}

void Scene::set_camera_x(float x) {
    m_camera_x = x;
}

void Scene::set_camera_y(float y) {
    m_camera_y = y;
}

}
