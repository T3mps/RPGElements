#include "RenderList.h"

bool RenderItem::UpdateFrame(const Sprite::Frame& newFrame, RenderUnit newRow, RenderUnit newCol)
{
   if (frame != newFrame || row != newRow || col != newCol)
   {
      frame = newFrame;
      row = newRow;
      col = newCol;
      isDirty = true;
   }
   return isDirty;
}

RenderList::RenderList() : m_isDirty(false) {}

void RenderList::SetItem(const Sprite::Frame& frame, RenderUnit row, RenderUnit col, RenderLayer layer, uint16_t zIndex)
{
   EnsureGridSize(layer, zIndex, row, col);
   if (m_layers[layer][zIndex][row][col].UpdateFrame(frame, row, col))
      m_isDirty = true;
}

void RenderList::Reserve(RenderUnit estimatedSize)
{
   for (auto& [_, sublayer] : m_layers)
   {
      for (auto& [_, batch] : sublayer)
      {
         batch.reserve(estimatedSize);
      }
   }
}

void RenderList::Swap(RenderList& other)
{
   m_layers.swap(other.m_layers);
   const bool tmpIsDirty = m_isDirty;
   m_isDirty = other.IsDirty();
   other.m_isDirty = tmpIsDirty;
}

void RenderList::Clear()
{
   for (auto& layer : m_layers)
   {
      for (auto& sublayer : layer.second)
      {
         sublayer.second.clear();
      }
   }
}

RenderUnit RenderList::Size() const
{
   RenderUnit totalSize = 0;
   for (const auto& layer : m_layers)
   {
      for (const auto& sublayer : layer.second)
      {
         totalSize += sublayer.second.size();
      }
   }
   return totalSize;
}

void RenderList::EnsureGridSize(RenderLayer layer, uint16_t zIndex, RenderUnit row, RenderUnit col)
{
   auto& grid = m_layers[layer][zIndex];
   if (grid.size() <= row)
      grid.resize(row + 1);
   if (grid[row].size() <= col)
      grid[row].resize(col + 1);
}
