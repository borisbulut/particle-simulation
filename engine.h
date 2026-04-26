#ifndef ENGINE_H
#define ENGINE_H

#include "render.h"
#include "camera.h"

class Engine {
public:
    GLuint WIDTH = 1000;
    GLuint HEIGHT = 1000;
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    float fov = 15.0f;

public:
    GLFWwindow* window;
    GLFWcursor* cursor;
    Render* render = nullptr;
    Camera* camera = nullptr;
    float deltaTime = 0;
    float lastX, lastY = 500;
    bool firstMouse = true;

    Engine();
    ~Engine();

    void run();
    void keyboard_inputs(GLFWwindow* window);
    void mouse_button_inputs(GLFWwindow* window);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif