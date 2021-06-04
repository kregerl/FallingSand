#include <vector>
#include "entity.h"

Entity::Entity(glm::vec2 offset) : type(Entity::NONE), offset(offset), m_numColors(1) {
    this->color = enumColors[this->type];
}

Entity::~Entity() {}


glm::vec3 Entity::GetColor() {
    return this->color;
}

void Entity::StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) {}

void Entity::SwapEntity(std::vector<std::vector<Entity *>> &entities, Point p1, Point p2) {
    Entity *temp = entities[p1.x][p1.y];
    entities[p1.x][p1.y] = entities[p2.x][p2.y];
    entities[p2.x][p2.y] = temp;
}




