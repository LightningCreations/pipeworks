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

}
