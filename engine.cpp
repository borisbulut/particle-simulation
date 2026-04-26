#include "engine.h"


Engine::Engine(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    window = glfwCreateWindow(WIDTH, HEIGHT, "PHYSICS", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);    
    cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
    glfwSetCursor(window, cursor);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    render = new Render();
    camera = new Camera();

    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_PROGRAM_POINT_SIZE);

}  

void Engine::run() {
    
    render->view = camera->GetViewMatrix();
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);

}

void Engine::mouse_button_inputs(GLFWwindow *window)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);
        
}
void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    
    if (engine) {
        
        float xoffset = xpos - engine->lastX;
        float yoffset = engine->lastY - ypos; 
        
        engine->lastX = xpos;
        engine->lastY = ypos;

        engine->camera->ProcessMouseMovement(xoffset, yoffset);
    }
}


void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->fov -= (float)yoffset;
        if (engine->fov < 1.0f) engine->fov = 1.0f;
        if (engine->fov > 100.0f) engine->fov = 100.0f;
    }
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

