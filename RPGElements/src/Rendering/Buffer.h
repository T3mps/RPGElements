#pragma once

#include "Sprite.h"

#include <string>
#include <vector>

class Buffer
{
public:
   Buffer() = default;
   Buffer(size_t rows, size_t cols);

   void SetFrame(size_t row, size_t col, const Sprite::Frame& frame);
   Sprite::Frame GetFrame(size_t row, size_t col);
   const Sprite::Frame GetFrame(size_t row, size_t col) const;

   size_t GetRows() const { return m_data.size(); }
   size_t GetCols() const { return m_data.empty() ? 0 : m_data[0].size(); }

   bool IsEmpty() const { return m_data.empty(); }

private:
   inline bool InBounds(size_t row, size_t col) const { return row >= 0 && row < GetRows() && col >= 0 && col < GetCols(); }

   std::vector<std::vector<Sprite::Frame>> m_data;
};
