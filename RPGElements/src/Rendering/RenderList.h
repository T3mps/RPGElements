#pragma once

#include <map>
#include <vector>

#include "Sprite.h"

struct RenderItem
{
   Sprite::Frame frame;
   size_t row;
   size_t col;
   bool isDirty = true;

   bool UpdateFrame(const Sprite::Frame& newFrame, size_t newRow, size_t newCol);
};

using RenderBatch = std::vector<RenderItem>;

enum class RenderLayer : uint8_t
{
   Background = 0x01,
   Foreground = 0x02,
   UI = 0x04
};

using RenderSublayer = std::map<uint16_t, RenderBatch>;

using RenderGrid = std::vector<std::vector<RenderItem>>;

class RenderList
{
public:
   using LayerMap = std::map<RenderLayer, std::map<uint16_t, RenderGrid>>;

   using iterator = LayerMap::iterator;
   using const_iterator = LayerMap::const_iterator;

   RenderList();
   ~RenderList() = default;

   void SetItem(const Sprite::Frame& frame, size_t row, size_t col, RenderLayer layer, uint16_t zIndex);
   
   void Reserve(size_t estimatedSize);
   void Swap(RenderList& other);

   void Clear();
   size_t Size() const;

   inline void ClearDirtyFlag() { m_isDirty = false; }
   inline bool IsDirty() const { return m_isDirty; }

   iterator begin() { return m_layers.begin(); }
   const_iterator begin() const { return m_layers.begin(); }
   iterator end() { return m_layers.end(); }
   const_iterator end() const { return m_layers.end(); }

private:
   void EnsureGridSize(RenderLayer layer, uint16_t zIndex, size_t row, size_t col);

   LayerMap m_layers;
   bool m_isDirty;
};
