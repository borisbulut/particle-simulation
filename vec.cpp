#include "vec.h"

// generate fonksiyonları (Header'da deklarasyonu varsa burada static yazma)
float generate(float range0, float range1) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_real_distribution<float> dist(range0, range1);
    return dist(gen);
}

float generate() {
    return generate(-1.0f, 1.0f);
}

// --- Vec2 Uygulamaları ---

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& vec) {
    return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator-(const Vec2& vec) {
    return Vec2(x - vec.x, y - vec.y);
}

void Vec2::operator=(const Vec2& vec) {
    x = vec.x;
    y = vec.y;
}

float Vec2::operator*(const Vec2& vec) {
    return x * vec.x + y * vec.y;
}

Vec2 Vec2::operator*(const float num) {
    return Vec2(x * num, y * num);
}

float Vec2::magnitude() const {
    return std::sqrtf(x * x + y * y);
}

float Vec2::magnitudes() const {
    return (x * x + y * y);
}

float Vec2::angle() const {
    return std::atan2(y, x); // atan yerine atan2 daha güvenlidir (x=0 hatasını önler)
}

// Sınıf dışı operatör (Scalar * Vector)
Vec2 operator*(float lhs, const Vec2& vec) {
    // Burada vec'i const referans yapmak daha iyidir
    return Vec2(vec.x * lhs, vec.y * lhs);
}

// --- Vec3 Uygulamaları ---

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& vec) {
    return Vec3(x + vec.x, y + vec.y, z + vec.z);
}

Vec3 Vec3::operator-(const Vec3& vec) {
    return Vec3(x - vec.x, y - vec.y, z - vec.z);
}

void Vec3::operator=(const Vec3& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

float Vec3::operator*(const Vec3& vec) {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vec3 Vec3::operator*(const float num) {
    return Vec3(x * num, y * num, z * num);
}

float Vec3::magnitude() const {
    return std::sqrtf(x * x + y * y + z * z);
}

float Vec3::magnitudes() const {
    return (x * x + y * y + z * z);
}

// Sınıf dışı operatör (Scalar * Vector)
Vec3 operator*(float lhs, const Vec3& vec) {
    return Vec3(vec.x * lhs, vec.y * lhs, vec.z * lhs);
}