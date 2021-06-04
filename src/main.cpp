#include "main.h"
#include <string>
#include <unistd.h>

Screen *screen;
const std::string title = "Falling Sand";

int main() {
    screen = new Screen(title.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);
    screen->start();

    Shader shader("/home/loucas/CLionProjects/OpenGLFallingSand/src/shaders/vertexShader.glsl",
                  "/home/loucas/CLionProjects/OpenGLFallingSand/src/shaders/fragmentShader.glsl");
//    Entity entity(Entity::NONE);
    World world(shader);
    screen->SetMouseCallback(&world);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f,
                                      -1.0f, 1.0f);


    while (screen->isRunning()) {

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        world.Draw(&projection);
        world.Step();
        glfwPollEvents();

        screen->processInput();
        glfwSwapBuffers(screen->window);
        usleep(10);
    }

    glfwTerminate();
    return 0;
}
