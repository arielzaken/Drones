#pragma once

#include <array>

enum { X, Y, Z, W };

template <typename T>
using Vec3D = std::array<T, 3>;

template <typename T>
using Vec2D = std::array<T, 2>;

template <typename T>
using Twist = std::array<T, 4>;

using Pos = std::array<float, 4>;


