#ifndef OPENGLGOL_WORLD_H
#define OPENGLGOL_WORLD_H

#include "entity/entity.h"
#include <GLFW/glfw3.h>
#include <cstring>
#include <ctime>
#include <vector>
#include "util/util.h"
#include "entity/sand.h"
#include "entity/water.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800


class World {
private:


    const static int amount = (SCREEN_WIDTH / ENTITY_SIZE) * (SCREEN_HEIGHT / ENTITY_SIZE);

    struct RenderData {
        glm::vec2 translations[World::amount];
        glm::vec3 colors[World::amount];
    };
    Entity::EntityType m_activeType;
    RenderData m_data;
    Point m_mousePos = Point(-1, -1), m_prevMousePos = Point(-1, -1);
    Shader m_shader;
    GLFWwindow *m_window;
    unsigned int m_VAO, m_offsetVBO, m_colorVBO;
    bool m_mousePressed;

    const int gravity = 3;

    void InitRenderData();

    // Gets the render data from the entity vector
    void UpdateRenderData();

    // Calls UpdateRenderData and maps it to VBO (only colors for now)
    void UpdateAndMapRenderData();

public:

    std::vector<std::vector<Entity *>> entities;

    World(Shader shader);

    ~World();

    void Draw(glm::mat4 *projectionMat);

    void InitWorld();

    void Step();

    void MouseButtonClicked(GLFWwindow *window, int button, int action, int mods);

    void PlaceEntity(int row, int col);

    void SwapEntity(Point p1, Point p2);

    void PlaceActiveType(int x, int y);
};


#endif //OPENGLGOL_WORLD_H
