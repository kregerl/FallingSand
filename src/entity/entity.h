#ifndef OPENGLGOL_ENTITY_H
#define OPENGLGOL_ENTITY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include <vector>
#include "../util/util.h"
#include "../util/shader.h"


#define ENTITY_SIZE 2
const static glm::vec3 enumColors[3] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
};


class Entity {
protected:


public:
    enum EntityType {
        NONE = 0, SAND = 1, WATER = 2, ROCK = 3
    };

    // <Color, Weight>
    std::vector<std::pair<glm::vec3, int>> m_colorWeights;
    int m_numColors;
    EntityType type;
    glm::vec2 offset;
    glm::vec3 color;

    Entity(glm::vec2 offset);

    ~Entity();

    virtual glm::vec3 GetColor();

    virtual void StepEntity(std::vector<std::vector<Entity *>> &entities, int i, int j);

    void SwapEntity(std::vector<std::vector<Entity *>> &entities, Point p1, Point p2);

    bool IsNone(std::vector<std::vector<Entity *>> &entities, int x, int y);
};


#endif //OPENGLGOL_ENTITY_H
