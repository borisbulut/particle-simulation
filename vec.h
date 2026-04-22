#include <cmath>
#include <random>

static float generate(float range0, float range1){
        static std::random_device rd;
        static std::mt19937 gen(rd());  // Mersenne Twister engine
        std::uniform_real_distribution<float> dist(range0, range1);
        return dist(gen);
    };
static float generate(){
        return generate(-1.0f,1.0f);
    };


class vec2{
    public:
    float x, y;
    
    public:
    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator+(const vec2& vec) {
        return vec2(x+vec.x, y+vec.y);
    }

    vec2 operator-(const vec2& vec) {
        return vec2(x-vec.x, y-vec.y);
    }

    void operator=(const vec2& vec) {
        x = vec.x;
        y = vec.y;
    }

    float operator*(const vec2& vec) {
        return x*vec.x+y*vec.y;
    }
    

    vec2 operator*(const float num) {
        return vec2(x*num,y*num);
    }

    float magnitude() const {
        return std::sqrtf(x*x+y*y);
    }

    float magnitudes() const {
        return (x*x+y*y);
    }

    float angle() const {
        return std::atan(y/x);
    }

   
};

vec2 operator*(float lhs, vec2& vec){
    return vec*lhs;
}


class vec3{
    public:
    float x, y, z;
    
    public:
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& vec) {
        return vec3(x+vec.x, y+vec.y, z+vec.z);
    }

    vec3 operator-(const vec3& vec) {
        return vec3(x-vec.x, y-vec.y, z-vec.z);
    }

    void operator=(const vec3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    float operator*(const vec3& vec) {
        return x*vec.x+y*vec.y+z*vec.z;
    }
    

    vec3 operator*(const float num) {
        return vec3(x*num,y*num,z*num);
    }

    float magnitude() const {
        return std::sqrtf(x*x+y*y+z*z);
    }

    float magnitudes() const {
        return (x*x+y*y+z*z);
    }

};

vec3 operator*(float lhs, vec3& vec){
    return vec*lhs;
}