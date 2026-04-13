#include "server.h"
#include "engine.h"
#include "render.h"


// INITIALIZE VARIABLES
//________________________
Engine engine;
Render render;


std::vector<float> speeds;
std::vector<float> positions;
int N = 100;
std::vector<Particle> particles;
void init_particles() {
    for(int i = 0; i < N ; ++i) {
    particles.emplace_back(generate(),generate(),generate(-2,2),generate(-2,2));
}
}

//_____END OF INITIALIZATION____________________

int main(){

    init_particles();
    glEnable(GL_PROGRAM_POINT_SIZE);
    while(!glfwWindowShouldClose(engine.window)){
        
        engine.run();
    
    // HANDLE MOVEMENT
    for (auto& p : particles) {
        p.velocity();
    }
    

    // HANDLE COLLISIONS HERE
    for (size_t i = 0; i < particles.size(); i++) {

        // Boundry collisions here
        particles[i].collision();

        // particle particle collisions
        for (size_t j = i + 1; j < particles.size(); j++) {
            particles[i].collision(particles[j]);
        }
    }    
      
    // DRAW
    render.draw(particles);
    // SEND DATA TO PYTHON
    send_data(speeds);
}
}