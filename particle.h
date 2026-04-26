#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec.h"

struct Particle{
    Vec3 pos, v;
    float size= 0.01;
    float dt = 0.01;
    float mass;
    int history = 0;

    Particle(float x, float y, float z, float vx, float vy, float vz, float mass) : pos(x,y,z), v(vx,vy,vz), mass(mass) {}
    

    
    void velocity(){
        pos = pos + v*dt;
    }
   
    void collision(Particle& p2){
        
        Vec3 r = (pos-p2.pos);
        Vec3 r2 = (p2.pos-pos);

        Vec3 v1 = v;
        Vec3 v2 = p2.v;

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

    // +Z
    if (pos.z < -1.0)
    {   
        v.z = -v.z;   
        pos.z = -1.0;     
    }

    // -Z
    if (pos.z > 1.0)
    {   
        v.z = -v.z; 
        pos.z = 1.0;  
    }
    
}
      
};

#endif