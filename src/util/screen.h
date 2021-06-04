#ifndef GLPARTICLES_SCREEN_H
#define GLPARTICLES_SCREEN_H

// Glad needs to be included before glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../world.h"

class Screen {
private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void window_resize_callback(GLFWwindow *window, int height, int width);

//    static void mouse_pressed_callback(GLFWwindow *util, int button, int action, int mods);

public:
    const char *title;
    unsigned int width, height;
    GLFWwindow *window;

    Screen(const char *title, unsigned int width, unsigned int height);

    ~Screen();

    void start();

    void processInput();

    bool isRunning();

    void SetMouseCallback(World *world);

};

#endif //GLPARTICLES_SCREEN_H
