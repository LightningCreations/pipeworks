#include <scene.hpp>

namespace pipeworks {

Scene::Scene() {
    static uint32_t s_max_scene_id = 0;
    s_max_scene_id++;
    m_id = s_max_scene_id;
}

uint32_t Scene::id() {
    return m_id; // Thread safety later
}

void Scene::activate() {}

void Scene::deactivate() {}

std::vector<GameObject*> Scene::objects() {
    return m_objects;
}

void Scene::add_object(GameObject *object) {
    m_objects.push_back(object);
}

bool Scene::loaded() {
    for(GameObject *object : m_objects) {
        if(!object->loaded()) return false;
    }
    return true;
}

}
