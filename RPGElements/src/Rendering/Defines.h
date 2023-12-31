#pragma once

#include <cmath>
#include <cstdint>

using RenderUnit = size_t;

template <typename V>
struct Vector
{
   Vector() = default;
};

template <typename V>
struct Vector2 : public Vector<V>
{
   V row;
   V col;

   Vector2() : row(V()), col(V()) {}
   Vector2(V r, V c) : row(r), col(c) {}

   bool operator==(const Vector2& other) const { return row == other.row && col == other.col; }
   bool operator!=(const Vector2& other) const { return !(*this == other); }

   Vector2 operator+(const Vector2& other) const { return { row + other.row, col + other.col }; }
   Vector2 operator-(const Vector2& other) const { return { row - other.row, col - other.col }; }
   Vector2 operator*(V scalar) const { return { row * scalar, col * scalar }; }
   Vector2 operator/(V scalar) const { return { row / scalar, col / scalar }; }

   Vector2& operator+=(const Vector2& other)
   {
      row += other.row;
      col += other.col;
      return *this;
   }

   Vector2& operator-=(const Vector2& other)
   {
      row -= other.row;
      col -= other.col;
      return *this;
   }

   Vector2& operator*=(V scalar)
   {
      row *= scalar;
      col *= scalar;
      return *this;
   }

   Vector2& operator/=(V scalar)
   {
      row /= scalar;
      col /= scalar;
      return *this;
   }

   V Dot(const Vector2& other) const { return row * other.row + col * other.col; }
   V Cross(const Vector2& other) const { return row * other.col - col * other.row; }

   V Magnitude() const
   {
#ifdef __cpp_lib_hypot
      return std::hypot(row, col);
#else
      return std::sqrt(row * row + col * col);
#endif
   }

   Vector2 Normalize() const
   {
      V mag = Magnitude();
      if (mag == 0)
         return *this;
      return { row / mag, col / mag };
   }
};

using Vector2i = Vector2<int32_t>;
using Vector2u = Vector2<uint32_t>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2r = Vector2<RenderUnit>;
