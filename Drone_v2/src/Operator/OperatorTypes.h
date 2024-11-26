#pragma once
#include "stdint.h"
#include <cstdint>
#include <Arduino.h>

// 2D Vector structure
typedef struct vec2D {
    int32_t x, y;

    // Overload the + operator for vec2D addition
    vec2D operator+(const vec2D& v) const {
        return {x + v.x, y + v.y};
    }

    // Overload the - operator for vec2D subtraction
    vec2D operator-(const vec2D& v) const {
        return {x - v.x, y - v.y};
    }

    // Overload the * operator for scalar multiplication
    vec2D operator*(int32_t scalar) const {
        return {x * scalar, y * scalar};
    }

    // Overload the == operator for comparison
    bool operator==(const vec2D& v) const {
        return (x == v.x && y == v.y);
    }
} vec2D;

// 3D Vector structure
typedef struct vec3D {
    int32_t x, y, z;
    vec3D(): x(0), y(0), z(0) {}
    vec3D(int32_t _x, int32_t _y, int32_t _z): x(_x), y(_y), z(_z) {}
    // print
    void print(Print& out) const {
        out.printf("(%d, %d, %d)",  x, y, z);
    }

    // Overload the + operator for vec3D addition
    vec3D operator+(const vec3D& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    // Overload the - operator for vec3D subtraction
    vec3D operator-(const vec3D& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    // Overload the * operator for scalar multiplication
    vec3D operator*(int32_t scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    // Overload the == operator for comparison
    bool operator==(const vec3D& v) const {
        return (x == v.x && y == v.y && z == v.z);
    }

    vec3D operator=(const vec3D& t){
        x = t.x;
        y = t.y;
        z = t.z;
        return *this;
    }

    vec3D& operator+=(const vec3D& t) {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
} vec3D;

// Twist structure
typedef struct Twist {
    vec3D v; // linear velocity
    int32_t w; // angular velocity

    // Default constructor
    Twist(): v(), w(0) {}

    // Constructor with parameters
    Twist(const vec3D& _v, int32_t _w): v(_v), w(_w) {}

    // print
    void print(Print& out) const {
        v.print(out);
        out.print(",");
        out.print(w);
    }

    // Overload the + operator for Twist addition
    Twist operator+(const Twist& t) const {
        return {v + t.v, w + t.w};
    }

    // Overload the - operator for Twist subtraction
    Twist operator-(const Twist& t) const {
        return {v - t.v, w - t.w};
    }

    // Overload the = operator for assignment
    Twist& operator=(const Twist& t) {
        if (this != &t) {    // Check for self-assignment
            v = t.v;
            w = t.w;
        }
        return *this;  // Return reference to current object
    }

    // Overload the += operator for Twist addition and assignment
    Twist& operator+=(const Twist& t) {
        v += t.v;  // Add the v components (assuming vec3D supports +=)
        w += t.w;  // Add the w components
        return *this;  // Return reference to current object
    }

} Twist;

