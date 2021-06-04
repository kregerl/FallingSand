#include "screen.h"

Screen::Screen(const char *title, unsigned int width, unsigned int height) : title(title), window(NULL),
                                                                             width(width),
                                                                             height(height) {}

Screen::~Screen() {
}

void Screen::start() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, title, NULL, NULL);

    if (window == NULL) {
        std::cout << "ERROR: Cant open null util." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(this->window, window_resize_callback);


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "ERROR: Failed to load GLAD" << std::endl;
        glfwTerminate();
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
}

void Screen::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

bool Screen::isRunning() {
    return !glfwWindowShouldClose(window);
}

void Screen::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Screen::window_resize_callback(GLFWwindow *window, int height, int width) {

}

void Screen::SetMouseCallback(World *world) {
    glfwSetWindowUserPointer(this->window, world);
    auto worldMouseButtonCallback = [](GLFWwindow *window, int button, int action, int mods) {
        static_cast<World *>(glfwGetWindowUserPointer(window))->MouseButtonClicked(window, button, action, mods);
    };
    glfwSetMouseButtonCallback(this->window, worldMouseButtonCallback);
}

//void Screen::mouse_pressed_callback(GLFWwindow *util, int button, int action, int mods) {
//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//        double mouseX, mouseY;
//        glfwGetCursorPos(util, &mouseX, &mouseY);
//        int x = mouseX / ENTITY_SIZE, y = mouseY / ENTITY_SIZE;
//    }
//}
