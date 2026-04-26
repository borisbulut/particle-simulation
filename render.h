#ifndef RENDER_H
#define RENDER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "particle.h"


class Render{
    
    public:
    GLuint VBO, VAO;
    Shader shader;
    unsigned int modelLoc, viewLoc, projLoc;
    std::vector<float> vertices;
    int max_particle = 10000;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);
     
    public:
    Render() : 
        shader("vertexShader.vert","fragmentShader.frag"),
      
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

  
    void draw(const std::vector<Particle>& particles) {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        for (size_t i = 0; i < particles.size(); i++) {
            float speed = particles[i].v.magnitude();

            vertices[i*7 + 0] = particles[i].pos.x;
            vertices[i*7 + 1] = particles[i].pos.y;
            vertices[i*7 + 2] = particles[i].pos.z;
                   
            vertices[i*7 + 3] = speed;          // red
            vertices[i*7 + 4] = 0.2f;           // green
            vertices[i*7 + 5] = 1.0f - speed;   // blue
                   
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

#endif