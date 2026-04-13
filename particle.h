#include "vec.h"

struct Particle{
    vec2 pos, v;
    float size= 0.01;
    float dt = 0.01;
    float mass;
    int history = 0;

    Particle(float x, float y, float vx, float vy) : pos(x,y), v(vx,vy), mass(generate(2.0f,10.0f)) {}
    

    
    void velocity(){
        pos = pos + v*dt;
    }
   
    void collision(Particle& p2){
        
        vec2 r = (pos-p2.pos);
        vec2 r2 = (p2.pos-pos);

        vec2 v1 = v;
        vec2 v2 = p2.v;

        float R = r.magnitude();
        float sizes = size + p2.size;

        if( R < sizes ) {
   
            //ELASTIC MOMENTUM TRANSFER EQUATIONS
            v = v1 - r*((v1-v2)*r)*(2*p2.mass/(mass+p2.mass)/r.magnitudes());
            p2.v = v2 - r2*((v2-v1)*r2)*(2*mass/(mass+p2.mass)/r2.magnitudes());
        
            //SET NEW POSITIONS WITHOUT CONTACT
            //_______________________________
            // ===
            //=    = /
            // ===  / === 
            //     /_     =
            //        ===
            //_______________________________

            pos = pos + (p2.mass/(p2.mass+mass))*((sizes-R)/R)*r;
            p2.pos = p2.pos - (mass/(p2.mass+mass))*((sizes-R)/R)*r;

        }

    }

    void collision(){

    // LEFT WALL
    if (pos.x < -1.0)
    {   
        v.x = -v.x;
        pos.x = -1.0; 
    }

    // RIGHT WALL
    if (pos.x > 1.0)
    {   
        v.x = -v.x;
        pos.x = 1.0;
    }

    // BOTTOM WALL
    if (pos.y < -1.0)
    {   
        v.y = -v.y;   
        pos.y = -1.0;     
    }

    // TOP WALL
    if (pos.y > 1.0)
    {   
        v.y = -v.y; 
        pos.y = 1.0;  
    }
    
}
      
};