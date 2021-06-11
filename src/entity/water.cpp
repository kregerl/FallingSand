#include "water.h"


Water::Water(glm::vec2 offset) : super(offset), m_gravity(5), m_spreadFactor(5) {
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
    this->m_density = 0;
}

Water::Water(Entity *entity) : Water(entity->offset) {}

Water::~Water() {}

glm::vec3 Water::GetColor() {
    return this->color;
}

void Water::StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) {
    Point lastValidPos = this->TraverseMatrix(entities, Point(i, j), Point(i, j + this->m_gravity));

    if (lastValidPos.x == i && lastValidPos.y == j) {
//        int random = (rand() % 2) + 1;
//        if (random == 1) {
//            // Down-Right
//            lastValidPos = this->TraverseMatrix(entities, lastValidPos,
//                                                Point(i + this->m_spreadFactor, j + this->m_gravity));
//        } else if (random == 2) {
//            // Down-Left
//            lastValidPos = this->TraverseMatrix(entities, lastValidPos,
//                                                Point(i - this->m_spreadFactor, j + this->m_gravity));
//        }
//        if (lastValidPos.x == i && lastValidPos.y == j) {
            //Determines which side to move to
            int random2 = (rand() % 2) + 1;
            if (random2 == 1) {
                // Right
                lastValidPos = this->TraverseMatrix(entities, lastValidPos, Point(i + this->m_spreadFactor, j));
            } else if (random2 == 2) {
                // Left
                lastValidPos = this->TraverseMatrix(entities, lastValidPos, Point(i - this->m_spreadFactor, j));
            }
//        }

    }

    if (lastValidPos.x != i || lastValidPos.y != j) {
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