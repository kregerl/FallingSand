#include "fire.h"


Fire::Fire(glm::vec2 offset) : super(offset) {
    this->color = glm::vec3(1.0f, 0.17254902f, 0.180392157f);
    this->type = Entity::FIRE;
}

Fire::Fire(Entity *entity) : Fire(entity->offset) {}

Fire::~Fire() {}

void Fire::StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) {


}