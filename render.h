#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "particle.h"

class Render{
    public:
    GLuint VBO;
    GLuint VAO;
    Shader shader;
    int colorLoc;
    unsigned int modelLoc;
    unsigned int viewLoc;
    unsigned int projLoc;
    std::vector<float> vertices;
    int max_particle = 2000;
    float radius = 4.0f;
    float camX;
    float camZ;
    glm::mat4 model = glm::mat4(1.0f); // Identity matrix
     
    // You can also rotate: model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

    glm::mat4 view = glm::mat4(1.0f);
    // Move the "camera" back 5 units so we can see the center (0,0,0)
    

    glm::mat4 projection;
    
    

    Render() : 
        shader("vertexShader.vert","fragmentShader.frag"),
        colorLoc(glGetUniformLocation(shader.ID, "ourColor")),              
        modelLoc(glGetUniformLocation(shader.ID, "model")),
        viewLoc(glGetUniformLocation(shader.ID, "view")),
        projLoc(glGetUniformLocation(shader.ID, "projection"))
     {
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        vertices.resize(max_particle * 7);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,
             vertices.size() * sizeof(float),
             NULL,
             GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 7*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    };

    
    void update() {
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);
    }
    void zoom(float fov) {
        projection = glm::perspective(glm::radians(fov), (float)1000 / (float)1000, 0.1f, 100.0f);
    }
    void rotate() {
         // How far away the camera is
        camX = sin(glfwGetTime()) * radius;
        camZ = cos(glfwGetTime()) * radius;

        
        view = glm::lookAt(
            glm::vec3(camX, 0.0f, camZ), // Camera position (moving in a circle)
            glm::vec3(0.0f, 0.0f, 0.0f), // Target: The point we are looking at (the origin)
            glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector: Usually (0, 1, 0)
);
    }
    void draw(const std::vector<Particle>& particles) {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        for (size_t i = 0; i < particles.size(); i++) {
            float speed = particles[i].v.magnitude();

            vertices[i*7 + 0] = particles[i].pos.x;
            vertices[i*7 + 1] = particles[i].pos.y;
            vertices[i*7 + 2] = particles[i].pos.z;
                   
            vertices[i*7 + 3] = sin(speed);          // red
            vertices[i*7 + 4] = 0.3f;           // green
            vertices[i*7 + 5] = 1.0f - sin(speed);   // blue
                   
            vertices[i*7 + 6] = particles[i].mass;
        }
        shader.program();

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS,0, particles.size());
    }

    ~Render() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
};