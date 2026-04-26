#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <random>

float generate(float range0, float range1);
float generate();


class Vec2{
    public:
    float x, y;
        
    public:
    Vec2(float x, float y);
    Vec2 operator+(const Vec2& vec);
    Vec2 operator-(const Vec2& vec);
    void operator=(const Vec2& vec);
    float operator*(const Vec2& vec);
    Vec2 operator*(const float num);
    float magnitude() const;
    float magnitudes() const;
    float angle() const;
};

Vec2 operator*(float lhs, Vec2& vec);


class Vec3{
    public:
    float x, y, z;
    
    public:
    Vec3(float x, float y, float z);
    Vec3 operator+(const Vec3& vec);
    Vec3 operator-(const Vec3& vec);
    void operator=(const Vec3& vec);
    float operator*(const Vec3& vec);
    Vec3 operator*(const float num);
    float magnitude() const;
    float magnitudes() const;
};
Vec3 operator*(float lhs, Vec3& vec);

#endif