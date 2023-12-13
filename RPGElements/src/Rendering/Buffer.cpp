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
      os << std::endl;
   }
   return os;
}

bool Buffer::operator==(const Buffer& other) const
{
   if (m_data.size() != other.m_data.size()) return false;

   for (size_t i = 0; i < m_data.size(); ++i)
   {
      if (m_data[i] != other.m_data[i])
         return false;
   }
   return true;
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