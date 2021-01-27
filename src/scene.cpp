#include <scene.hpp>

namespace pipeworks {

Scene::Scene() {
    static uint32_t max_scene_id = 0;
    max_scene_id++;
    id = max_scene_id;
}

uint32_t Scene::get_id() {
    return id; // Thread safety later
}

void Scene::activate() {}

void Scene::deactivate() {}

std::vector<GameObject*> Scene::get_objects() {
    return objects;
}

void Scene::add_object(GameObject *object) {
    objects.push_back(object);
}

bool Scene::is_loaded() {
    for(GameObject *object : objects) {
        if(!object->is_loaded()) return false;
    }
    return true;
}

}

