#pragma once
#include <string>
#include <sstream>
#include <atomic>
#include <cmath>
#include "defines.h"

namespace FW {

    class API Vector {
    public:
        float x, y, z = 0.f;

        Vector& zero() { x = y = z = 0; return (*this); }
        Vector& set(float r) { x = y = z = r; return (*this); }
        Vector& set(float x, float y, float z) { this->x = x, this->y = y, this->z = z; return (*this); }
        float length() { return (float)sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)); }
        const char* asText() {
            std::stringstream result(std::stringstream::in | std::stringstream::out);
            result << "X: " << x << " Y: " << y << " Z: " << z;
            return result.str().c_str();
        }

        Vector& operator+=(float r) { x += r; y += r; z += r; return (*this); }
        Vector& operator-=(float r) { x -= r; y -= r; z -= r; return (*this); }
        Vector& operator*=(float r) { x *= r; y *= r; z *= r; return (*this); }
        Vector& operator/=(float r) { x /= r; y /= r; z /= r; return (*this); }
        Vector& operator+=(const Vector& v) { x += v.x; y += v.y; z += v.z; return (*this); }
        Vector& operator-=(const Vector& v) { x -= v.x; y -= v.y; z -= v.z; return (*this); }
        Vector& operator*=(const Vector& v) { x *= v.x; y *= v.y; z *= v.z; return (*this); }
        Vector& operator/=(const Vector& v) { x /= v.x; y /= v.y; z /= v.z; return (*this); }
        bool operator==(const Vector& v) const {
            if (x == v.x && y == v.y && z == v.z) return true;
            return false;
        }
        bool operator!=(const Vector& v) const {
            if (x != v.x || y != v.y || z != v.z) return true;
            return false;
        }

        friend Vector  operator+ (const	Vector& v, float      r) { return Vector(v.x + r, v.y + r, v.z + r); }
        friend Vector  operator- (const	Vector& v, float      r) { return Vector(v.x - r, v.y - r, v.z - r); }
        friend Vector  operator* (const	Vector& v, float      r) { return Vector(v.x * r, v.y * r, v.z * r); }
        friend Vector  operator/ (const	Vector& v, float      r) { return Vector(v.x / r, v.y / r, v.z / r); }
        friend Vector  operator+ (float      r, const Vector& v) { return Vector(r + v.x, r + v.y, r + v.z); }
        friend Vector  operator- (float      r, const Vector& v) { return Vector(r - v.x, r - v.y, r - v.z); }
        friend Vector  operator* (float      r, const Vector& v) { return Vector(r * v.x, r * v.y, r * v.z); }
        friend Vector  operator/ (float      r, const Vector& v) { return Vector(r / v.x, r / v.y, r / v.z); }
        friend Vector  operator+ (const	Vector& a, const Vector& b) { return Vector(a.x + b.x, a.y + b.y, a.z + b.z); }
        friend Vector  operator- (const	Vector& a, const Vector& b) { return Vector(a.x - b.x, a.y - b.y, a.z - b.z); }
        friend Vector  operator* (const	Vector& a, const Vector& b) { return Vector(a.x * b.x, a.y * b.y, a.z * b.z); }
        friend Vector  operator/ (const	Vector& a, const Vector& b) { return Vector(a.x / b.x, a.y / b.y, a.z / b.z); }

        Vector() : x(0.f), y(0.f), z(0.f) {}
        Vector(const Vector& v) {x=v.x; y=v.y; z=v.z;}
        Vector(float r) { set(r); }
        Vector(float x, float y, float z) { set(x, y, z); }
    };
}