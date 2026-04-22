#ifndef ENGINE_H
#define ENGINE_H

#include <glad.h>
#include <glfw3.h>

class Engine {
public:
    GLuint WIDTH = 1000;
    GLuint HEIGHT = 1000;
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    float fov = 45.0f; // Start with a 45-degree FOV

public:
    GLFWwindow* window;
    GLFWcursor* cursor;

    Engine();
    ~Engine();

    void run();
    void keyboard_inputs(GLFWwindow* window);
    void mouse_button_inputs(GLFWwindow* window);
    
    bool inside_screen(float x, float y);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif