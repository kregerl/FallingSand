#include "sand.h"

Sand::Sand(glm::vec2 offset) : super(offset), m_gravity(3) {
    this->m_numColors = 4;
    this->m_colorWeights.clear();
    this->m_colorWeights = {
            std::pair<glm::vec3, int>(glm::vec3(1.0f, 0.878431373f, 0.670588235f), 9),
            std::pair<glm::vec3, int>(glm::vec3(0.952941176f, 0.807843137f, 0.576470588f), 7),
            std::pair<glm::vec3, int>(glm::vec3(0.854901961f, 0.725490196f, 0.529411765f), 3),
            std::pair<glm::vec3, int>(glm::vec3(0.933333333f, 0.71372549f, 0.374509804f), 1),
    };
    this->type = Entity::SAND;
    this->InitColor();
}

Sand::Sand(Entity *entity) : Sand(entity->offset) {}

Sand::~Sand() {}

glm::vec3 Sand::GetColor() {
    return this->color;
}


void Sand::StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j) {
    Point lastValidPos = Point(i, j);
    // Gravity
    for (int g = 1; g <= this->m_gravity; g++) {
        // Sideways random movement
        for (int f = 1; f <= rand() % 4 + 1; f++) {
            // Whether or not a piece of sand should try moving left or right
            int rando = rand() % 2 + 1;
            if (j + g < SCREEN_HEIGHT / ENTITY_SIZE) {
                if (entities[i][j + g]->type != Entity::SAND && entities[i][j + g]->type != Entity::ROCK) {
                    lastValidPos = Point(i, j + g);
                } else if (i + f < SCREEN_WIDTH / ENTITY_SIZE &&
                           entities[i + f][j + g]->type != Entity::SAND &&
                           entities[i + f][j + g]->type != Entity::ROCK && rando == 1) {
                    lastValidPos = Point(i + f, j + g);
                } else if (i - f < SCREEN_WIDTH / ENTITY_SIZE && i - f >= 0 &&
                           entities[i - f][j + g]->type != Entity::SAND &&
                           entities[i - f][j + g]->type != Entity::ROCK &&
                           rando == 2) {
                    lastValidPos = Point(i - f, j + g);
                } else {
                    break;
                }
            }
        }
    }
    if (lastValidPos.x != i || lastValidPos.y != j) {
        SwapEntity(entities, Point(i, j), lastValidPos);
    }
}


void Sand::InitColor() {
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