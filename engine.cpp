#include "engine.h"


Engine::Engine(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    window = glfwCreateWindow(WIDTH, HEIGHT, "OPENGL", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetScrollCallback(window, Engine::scroll_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);    
    cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
    glfwSetCursor(window, cursor);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
}  

void Engine::run() {
    glEnable(GL_DEPTH_TEST); 
    keyboard_inputs(window);
    mouse_button_inputs(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      
}

void Engine::keyboard_inputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Engine::mouse_button_inputs(GLFWwindow *window)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        true;
}

void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->fov -= (float)yoffset;
        if (engine->fov < 1.0f) engine->fov = 1.0f;
        if (engine->fov > 100.0f) engine->fov = 100.0f;
    }
}

bool Engine::inside_screen(float x, float y){
   return  x < 1.0f && y < 1.0f && x > -1.0 && y > -1.0;
}
void Engine::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Engine::~Engine() {
    
    glfwDestroyCursor(cursor);

    if (window != nullptr)
        glfwDestroyWindow(window);

    glfwTerminate();
}

