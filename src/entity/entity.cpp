#include <vector>
#include "entity.h"


Entity::Entity(glm::vec2 offset) : type(Entity::NONE), offset(offset), m_numColors(1), m_density(-1) {
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

bool Entity::IsNone(std::vector<std::vector<Entity *>> &entities, int x, int y) {
    if (entities[x][y]->type == NONE) {
        return true;
    }
    return false;
}

Point Entity::TraverseMatrix(std::vector<std::vector<Entity *>> &entities, Point starting, Point ending) {
    float xDiff = starting.x - ending.x;
    float yDiff = starting.y - ending.y;

    bool xDiffLarger = abs(xDiff) > abs(yDiff);

    int xModifier = xDiff < 0 ? 1 : -1;
    int yModifier = yDiff < 0 ? 1 : -1;

    int longerSideLength = std::max(abs(xDiff), abs(yDiff));
    int shorterSideLength = std::min(abs(xDiff), abs(yDiff));
    float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float) (shorterSideLength) /
                                                                           (longerSideLength));
    int shorterSideIncrease;
    Point lastValidPos = starting;
    for (int i = 1; i <= longerSideLength; i++) {
        shorterSideIncrease = round(i * slope);
        int yIncrease, xIncrease;
        if (xDiffLarger) {
            xIncrease = i;
            yIncrease = shorterSideIncrease;
        } else {
            yIncrease = i;
            xIncrease = shorterSideIncrease;
        }
        int currentY = starting.y + (yIncrease * yModifier);
        int currentX = starting.x + (xIncrease * xModifier);

        if (currentX >= 0 && currentX < SCREEN_WIDTH / ENTITY_SIZE && currentY >= 0 &&
            currentY < SCREEN_HEIGHT / ENTITY_SIZE) {
            if (entities[currentX][currentY]->type == NONE ||
                entities[currentX][currentY]->m_density < this->m_density) {
                lastValidPos = Point(currentX, currentY);
            } else {
                break;
            }
        }
    }
    return lastValidPos;

}




