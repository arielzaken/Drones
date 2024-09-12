#pragma once
#include "stdint.h"

#include <iostream>
#include <cstdint>

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
} vec3D;

// Twist structure
typedef struct Twist {
    vec3D v; // linear velocity
    vec3D w; // angular velocity

    // Overload the + operator for Twist addition
    Twist operator+(const Twist& t) const {
        return {v + t.v, w + t.w};
    }

    // Overload the - operator for Twist subtraction
    Twist operator-(const Twist& t) const {
        return {v - t.v, w - t.w};
    }
} Twist;