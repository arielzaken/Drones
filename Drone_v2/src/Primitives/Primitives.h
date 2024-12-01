#pragma once

#include <Arduino.h>

template <typename T, size_t N>
class MathVector {
protected:
    T data[N]; // Replace std::array with raw array

public:
    // Default constructor
    MathVector() {
        for (size_t i = 0; i < N; ++i)
            data[i] = T();
    }

    // Initialize with an initializer list
    MathVector(std::initializer_list<T> init) {
        size_t i = 0;
        for (auto val : init) {
            if (i < N) data[i++] = val;
        }
    }

    // Access element
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    // Assignment
    MathVector& operator=(const MathVector& other) {
        for (size_t i = 0; i < N; ++i)
            data[i] = other.data[i];
        return *this;
    }

    // Addition
    MathVector operator+(const MathVector& other) const {
        MathVector result;
        for (size_t i = 0; i < N; ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Subtraction
    MathVector operator-(const MathVector& other) const {
        MathVector result;
        for (size_t i = 0; i < N; ++i)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    // Scalar multiplication
    MathVector operator*(T scalar) const {
        MathVector result;
        for (size_t i = 0; i < N; ++i)
            result.data[i] = data[i] * scalar;
        return result;
    }

    // Dot product
    T operator*(const MathVector& other) const {
        T result = T();
        for (size_t i = 0; i < N; ++i)
            result += data[i] * other.data[i];
        return result;
    }

    // In-place addition
    MathVector& operator+=(const MathVector& other) {
        for (size_t i = 0; i < N; ++i)
            data[i] += other.data[i];
        return *this;
    }

    // Equality check
    bool operator==(const MathVector& other) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    // Debug print
    void print(Print& out) const {
        out.print("[");
        for (size_t i = 0; i < N; ++i) {
            out.print(data[i]);
            if (i < N - 1)
                out.print(", ");
        }
        out.println("]");
    }

    void print(){
        print(Serial);
    }
};

enum {X, Y, Z, W};

template <typename T>
using Vec3D = MathVector<T, 3>;

template <typename T>
using Vec2D = MathVector<T, 2>;

template <typename T>
using Twist = MathVector<T, 4>;

using IntTwist = Twist<int32_t>;

using Pos = MathVector<float, 4>;

using Velocity = Pos;


