#include "Buffer.h"

#include <iostream>

Buffer::Buffer(Viewport viewport) :
   m_data(viewport.row1, std::vector<Sprite::Frame>(viewport.col1)),
   m_viewport(viewport)
{
}

std::ostream& operator<<(std::ostream & os, const Buffer& buffer)
{
   for (const auto& row : buffer)
   {
      for (const auto& frame : row)
      {
         os << frame.color << frame.glyph;
      }
      os << std::endl;
   }
   return os;
}

bool Buffer::operator==(const Buffer& other) const
{
   if (m_data.size() != other.m_data.size()) return false;

   for (RenderUnit i = 0; i < m_data.size(); ++i)
   {
      if (m_data[i] != other.m_data[i])
         return false;
   }
   return true;
}

void Buffer::SetFrame(RenderUnit row, RenderUnit col, const Sprite::Frame& frame)
{
   if (InBounds(row, col))
      m_data[row][col] = frame;
}

Sprite::Frame Buffer::GetFrame(RenderUnit row, RenderUnit col)
{
   if (InBounds(row, col))
      return m_data[row][col];
   return Sprite::Frame('?');
}

const Sprite::Frame Buffer::GetFrame(RenderUnit row, RenderUnit col) const
{
   if (InBounds(row, col))
      return m_data[row][col];
   return Sprite::Frame('?');
}