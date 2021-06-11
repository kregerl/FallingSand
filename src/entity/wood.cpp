#include "wood.h"

Wood::Wood(glm::vec2 offset) : super(offset) {
    this->color = glm::vec3(0.501960784f, 0.298039216f, 0.211764706f);
    this->m_density = 2;
    this->type = Entity::WOOD;
}

Wood::Wood(Entity *entity) : Wood(entity->offset) {}

Wood::~Wood() {}

void Wood::StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) {

}
