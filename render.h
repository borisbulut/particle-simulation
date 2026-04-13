#include <glad.h>
#include "shader.h"
#include "particle.h"

class Render{
    public:
    GLuint VBO;
    GLuint VAO;
    Shader shader;
    int colorLoc;
    std::vector<float> vertices;
    int max_particle = 5000;
    

    Render() : 
        shader("vertexShader.vert","fragmentShader.frag"),
        colorLoc(glGetUniformLocation(shader.ID, "ourColor"))
     {
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        vertices.resize(max_particle * 7);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,
             vertices.size() * sizeof(float),
             vertices.data(),
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
        
        
        for (size_t i = 0; i < particles.size(); i++) {
            float speed = particles[i].v.magnitude();

            vertices[i*7 + 0] = particles[i].pos.x;
            vertices[i*7 + 1] = particles[i].pos.y;
            vertices[i*7 + 2] = 0.0f;
                   
            vertices[i*7 + 3] = speed;          // red
            vertices[i*7 + 4] = 0.3f;           // green
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