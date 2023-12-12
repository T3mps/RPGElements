#include "Buffer.h"

Buffer::Buffer(size_t rows, size_t cols) : m_data(rows, std::vector<Sprite::Frame>(cols))
{
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