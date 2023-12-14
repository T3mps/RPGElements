#pragma once

class Camera
{
public:
   Camera() = default;
   ~Camera() = default;

   inline size_t GetRow() { return m_row; }
   inline size_t GetCol() { return m_col; }
   inline void SetRow(size_t row) { m_row = row; }
   inline void SetRow(size_t col) { m_col = col; }

private:
   size_t m_row;
   size_t m_col;
};
