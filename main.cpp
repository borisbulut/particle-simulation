#include "engine.h"


// INITIALIZE VARIABLES
//________________________
Engine engine;

int N = 100;
std::vector<Particle> particles;

float lastFrame = 0.0f;
void init_particles() {
    for(int i = 0; i < N ; ++i) {
        particles.emplace_back(generate(),generate(),generate(),generate(-2,2),generate(-2,2),generate(-2,2),generate(1.0,5.0));
    }
}

void init_field() {
    for(float i = -1.0f ; i < 1.0f; i+=0.1f ) {
        for(float j = -1.0f ; j < 1.0f; j+=0.1f) {
            for(float k = -1.0f ; k < 1.0f; k+=0.1f) {
                particles.emplace_back(i,j,k,0,0,0,3.0f);
            }
        }
    }

}

//_____END OF INITIALIZATION____________________

int main(){
    
    init_field();
    //engine.render->update();
    while(!glfwWindowShouldClose(engine.window)){
        float currentFrame = static_cast<float>(glfwGetTime());
        engine.deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        engine.run();
        glfwSetScrollCallback(engine.window, engine.scroll_callback);

    // HANDLE MOVEMENT
    for (auto& p : particles) {
        //p.velocity();
    }
    

    // HANDLE COLLISIONS HERE
    for (size_t i = 0; i < particles.size(); i++) {

        //Boundry collisions here
        //particles[i].collision();

        // particle particle collisions
        for (size_t j = i + 1; j < particles.size(); j++) {
            //particles[i].collision(particles[j]);
        }
    }    
      
    // DRAW
    
    engine.render->draw(particles);
    
}
}