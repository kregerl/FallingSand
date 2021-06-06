#include "water.h"


Water::Water(glm::vec2 offset) : super(offset), m_gravity(3) {
    this->m_numColors = 6;
    this->m_colorWeights.clear();
    this->m_colorWeights = {
            std::pair<glm::vec3, int>(glm::vec3(0.058823529f, 0.368627451f, 0.611764706f), 45),
            std::pair<glm::vec3, int>(glm::vec3(0.137254902f, 0.537254902f, 0.854901961f), 25),
            std::pair<glm::vec3, int>(glm::vec3(0.109803922f, 0.639215686f, 0.811765f), 0.75 * offset.y),
            std::pair<glm::vec3, int>(glm::vec3(0.352941176f, 0.737254902f, 0.847058824f), 0.5 * offset.y),
            std::pair<glm::vec3, int>(glm::vec3(0.454901961f, 0.8f, 0.956862745f), 0.25 * offset.y),
            std::pair<glm::vec3, int>(glm::vec3(0.058823529f, 0.368627451f, 0.847058824f), 25 * offset.y)
    };
    this->type = Entity::WATER;
    this->InitColor();
}

Water::Water(Entity *entity) : Water(entity->offset) {}

Water::~Water() {}

glm::vec3 Water::GetColor() {
    return this->color;
}

void Water::StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) {
    Point lastValidPos = Point(-1, -1);
    // Gravity
    for (int g = 1; g <= this->m_gravity; g++) {
        // Sideways random movement
        for (int f = 1; f <= rand() % 10 + 1; f++) {
            // Whether or not a piece of sand should try moving left or right
            int rando = rand() % 2 + 1;
            if (j + g < SCREEN_HEIGHT / ENTITY_SIZE) {
                if (entities[i][j + g]->type == Entity::NONE) {
                    lastValidPos = Point(i, j + g);
                } else if (i + f < SCREEN_WIDTH / ENTITY_SIZE &&
                           entities[i + f][j + g]->type == Entity::NONE && rando == 1) {
                    lastValidPos = Point(i + f, j + g);
                } else if (i - f < SCREEN_WIDTH / ENTITY_SIZE && i - f >= 0 &&
                           entities[i - f][j + g]->type == Entity::NONE &&
                           rando == 2) {
                    lastValidPos = Point(i - f, j + g);
                } else if (i - f < SCREEN_WIDTH / ENTITY_SIZE && i - f >= 0 &&
                           entities[i - f][j]->type == Entity::NONE &&
                           rando == 2) {
                    // Left
                    lastValidPos = Point(i - f, j);
                } else if (i + f < SCREEN_WIDTH / ENTITY_SIZE &&
                           entities[i + f][j]->type == Entity::NONE && rando == 1) {
                    // Right
                    lastValidPos = Point(i + f, j);
                } else {
                    break;
                }
            }
        }
    }
    if (lastValidPos.x != -1 && lastValidPos.y != -1) {
        SwapEntity(entities, Point(i, j), lastValidPos);
    }
}

void Water::InitColor() {
    int index = 0, sum = 0;
    std::vector<int> csum(this->m_numColors);
    for (int i = 0; i < this->m_numColors; i++) {
        sum += this->m_colorWeights[i].second;
        csum[i] = sum;
    }
    double random = (rand() % sum);
    for (int i = 0; i < this->m_numColors; i++) {
        if (csum[i] > random) {
            this->color = this->m_colorWeights[i].first;
            break;
        }
    }

}