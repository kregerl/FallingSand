#include "world.h"
#include "entity/rock.h"

World::World(Shader shader) : m_shader(shader) {
    this->InitWorld();
    this->InitRenderData();
    this->m_window = nullptr;
    this->m_activeType = Entity::SAND;
}

World::~World() {}


void World::Draw(glm::mat4 *projectionMat) {
    this->m_shader.use();

    glm::mat4 modelMat = glm::mat4(1.0f);

//    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f)); Dont need this

    // Translate half the size of the square to make pivot point top left
    modelMat = glm::translate(modelMat, glm::vec3(0.5f * ENTITY_SIZE, 0.5f * ENTITY_SIZE, 0.0f));
    modelMat = glm::scale(modelMat, glm::vec3(static_cast<float>(ENTITY_SIZE), static_cast<float>(ENTITY_SIZE), 1.0f));

    this->m_shader.setMat4("u_projection", *projectionMat);
    this->m_shader.setMat4("u_model", modelMat);

    glBindVertexArray(this->m_VAO);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, amount);
    glBindVertexArray(0);
}

void World::InitWorld() {
    this->entities.reserve(SCREEN_WIDTH / ENTITY_SIZE); // Not needed, but slight performance increase
    for (int x = 0; x < SCREEN_WIDTH / ENTITY_SIZE; x++) {
        std::vector<Entity *> vec;
        vec.reserve(SCREEN_WIDTH / ENTITY_SIZE); // Not needed, but slight performance increase
        for (int y = 0; y < SCREEN_HEIGHT / ENTITY_SIZE; y++) {
            vec.push_back(new Entity(glm::vec2(x, y)));
        }
        this->entities.push_back(vec);
    }
}


void World::MouseButtonClicked(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        this->m_mousePressed = true;
        this->m_window = window;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        this->m_mousePressed = false;
        this->m_window = nullptr;
        this->m_prevMousePos = Point(-1, -1);
        this->m_mousePos = Point(-1, -1);
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        if (mouseX >= 0 && mouseY >= 0 && mouseX <= SCREEN_WIDTH && mouseY <= SCREEN_HEIGHT) {
            int row = mouseX / ENTITY_SIZE, col = mouseY / ENTITY_SIZE;
            printf("Type: %d r: %f, g:%f, b:%f", this->entities[row][col]->type, this->entities[row][col]->color.r,
                   this->entities[row][col]->color.g,
                   this->entities[row][col]->color.b);
            fflush(stdout);
        }
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if (this->m_activeType == Entity::SAND) {
            this->m_activeType = Entity::WATER;
        } else if (this->m_activeType == Entity::WATER) {
            this->m_activeType = Entity::ROCK;
        } else {
            this->m_activeType = Entity::SAND;
        }
    }

}

void World::PlaceEntity(int row, int col) {
    if ((this->m_prevMousePos.x == this->m_mousePos.x && this->m_prevMousePos.y == this->m_mousePos.y) ||
        (this->m_prevMousePos.x == -1 || this->m_prevMousePos.y == -1 || this->m_mousePos.x == -1 ||
         this->m_mousePos.y == -1)) {
        this->PlaceActiveType(this->m_mousePos.x, this->m_mousePos.y);

        for (int g = 1; g <= this->gravity; g++) {
            if (this->m_mousePos.y - g >= 0) {
                this->PlaceActiveType(this->m_mousePos.x, this->m_mousePos.y + g);
            }
        }
        return;
    }

    float xDiff = this->m_prevMousePos.x - this->m_mousePos.x;
    float yDiff = this->m_prevMousePos.y - this->m_mousePos.y;

    bool xDiffLarger = abs(xDiff) > abs(yDiff);

    int xModifier = xDiff < 0 ? 1 : -1;
    int yModifier = yDiff < 0 ? 1 : -1;

    int longerSideLength = std::max(abs(xDiff), abs(yDiff));
    int shorterSideLength = std::min(abs(xDiff), abs(yDiff));
    float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float) (shorterSideLength) /
                                                                           (longerSideLength));
    int shorterSideIncrease;
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
        int currentY = this->m_prevMousePos.y + (yIncrease * yModifier);
        int currentX = this->m_prevMousePos.x + (xIncrease * xModifier);

        if (currentX >= 0 && currentX < SCREEN_WIDTH / ENTITY_SIZE && currentY >= 0 &&
            currentY < SCREEN_HEIGHT / ENTITY_SIZE) {
            this->PlaceActiveType(currentX, currentY);
        }
    }
}

void World::PlaceActiveType(int x, int y) {
    switch (this->m_activeType) {
        case Entity::SAND:
            this->entities[x][y] =
                    new Sand(this->entities[x][y]);
            break;
        case Entity::WATER:
            this->entities[x][y] =
                    new Water(this->entities[x][y]);
            break;
        case Entity::ROCK:
            this->entities[x][y] =
                    new Rock(this->entities[x][y]);
            break;
        case Entity::NONE:
            break;
    }
}

void World::Step() {
    if (this->m_mousePressed && this->m_window != nullptr) {
        double mouseX, mouseY;
        glfwGetCursorPos(this->m_window, &mouseX, &mouseY);
        if (mouseX >= 0 && mouseY >= 0 && mouseX < SCREEN_WIDTH && mouseY < SCREEN_HEIGHT) {
            int row = mouseX / ENTITY_SIZE, col = mouseY / ENTITY_SIZE;
            if (this->m_mousePos.x != -1 && this->m_mousePos.y != -1) {
                this->m_prevMousePos = this->m_mousePos;
            }
            this->m_mousePos = Point(row, col);

            if (this->entities[row][col]->type == Entity::NONE) {
                this->PlaceEntity(row, col);
            }
        }
    }


    for (int i = this->entities.size() - 1; i >= 0; i--) {
        for (int j = this->entities[i].size() - 1; j >= 0; j--) {
            switch (this->entities[i][j]->type) {
                case Entity::SAND:
                    static_cast<Sand>(this->entities[i][j]).StepEntity(this->entities, i, j);
                    break;
                case Entity::WATER:
                    static_cast<Water>(this->entities[i][j]).StepEntity(this->entities, i, j);
                    break;
                case Entity::ROCK:
                    static_cast<Rock>(this->entities[i][j]).StepEntity(this->entities, i, j);
                    break;
                case Entity::NONE:
                    break;
                default:
                    break;
            }
        }
    }
    this->UpdateAndMapRenderData();
}


void World::InitRenderData() {
    this->UpdateRenderData();

    glGenBuffers(1, &this->m_offsetVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_offsetVBO);
    glBufferData(GL_ARRAY_BUFFER, this->amount * sizeof(glm::vec2), this->m_data.translations, GL_STATIC_DRAW);

    glGenBuffers(1, &this->m_colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorVBO);
    glBufferData(GL_ARRAY_BUFFER, this->amount * sizeof(glm::vec3), this->m_data.colors, GL_STATIC_DRAW);

    unsigned int vertexVBO;
    float vertices[] = {
            -0.5f, 0.5f,
            -0.5f, -0.5f,
            0.5f, 0.5f,
            0.5f, -0.5f
    };
    glGenVertexArrays(1, &this->m_VAO);
    glGenBuffers(1, &vertexVBO);
    glBindVertexArray(this->m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);


    //Verticies
    glEnableVertexAttribArray(0);
    GLint vertexStepSize = 2;
    glVertexAttribPointer(0, vertexStepSize, GL_FLOAT, GL_FALSE, vertexStepSize * sizeof(float), (void *) 0);

    //Offsets
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_offsetVBO);
    GLint offsetStepSize = 2;
    glVertexAttribPointer(1, offsetStepSize, GL_FLOAT, GL_FALSE, offsetStepSize * sizeof(float), (void *) 0);
    glVertexAttribDivisor(1, 1);

    //Colors
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorVBO);
    GLint colorStepSize = 3;
    glVertexAttribPointer(2, colorStepSize, GL_FLOAT, GL_FALSE, colorStepSize * sizeof(float), (void *) 0);
    glVertexAttribDivisor(2, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void World::UpdateRenderData() {
    for (int i = 0; i < std::sqrt(amount); i++) {
        for (int j = 0; j < std::sqrt(amount); j++) {
            this->m_data.translations[i * static_cast<int>(std::sqrt(amount)) + j] = entities[i][j]->offset;
            this->m_data.colors[i * static_cast<int>(std::sqrt(amount)) + j] = entities[i][j]->color;
        }
    }
}

void World::UpdateAndMapRenderData() {
    this->UpdateRenderData();
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorVBO);
    void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(ptr, this->m_data.colors, sizeof(this->m_data.colors));
    glUnmapBuffer(GL_ARRAY_BUFFER);
}


