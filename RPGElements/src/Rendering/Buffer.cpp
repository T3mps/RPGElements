#include "Buffer.h"

#include <iostream>

Buffer::Buffer(size_t rows, size_t cols) : m_data(rows, std::vector<Sprite::Frame>(cols))
{
}

std::ostream& operator<<(std::ostream & os, const Buffer& buffer)
{
   for (const auto& row : buffer)
   {
      for (const auto& frame : row)
      {
         os << frame.color << frame.character;
      }
      os << '\n';
   }
   return os;
}

void Buffer::SetFrame(size_t row, size_t col, const Sprite::Frame& frame)
{
   if (InBounds(row, col))
      m_data[row][col] = frame;
}

Sprite::Frame Buffer::GetFrame(size_t row, size_t col)
{
   if (InBounds(row, col))
      return m_data[row][col];
   return Sprite::Frame('?');
}

const Sprite::Frame Buffer::GetFrame(size_t row, size_t col) const
{
   if (InBounds(row, col))
      return m_data[row][col];
   return Sprite::Frame('?');
}