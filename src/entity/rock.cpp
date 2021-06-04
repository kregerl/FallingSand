#include "rock.h"

Rock::Rock(glm::vec2 offset) : super(offset) {
    this->color = glm::vec3(0.164705882f, 0.17254902f, 0.180392157f);
    this->type = Entity::ROCK;
}

Rock::Rock(Entity *entity) : Rock(entity->offset) {}

Rock::~Rock() {}

void Rock::StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) {

}