#pragma once

#include <map>
#include <vector>

#include "Sprite.h"

struct RenderItem
{
   Sprite::Frame frame;
   size_t row;
   size_t col;
};

using RenderBatch = std::vector<RenderItem>;

enum class RenderLayer : uint8_t
{
   Background = 0x01,
   Foreground = 0x02,
   UI = 0x04
};

using RenderSublayer = std::map<uint16_t, RenderBatch>;

class RenderList
{
public:
   using iterator = std::map<RenderLayer, RenderSublayer>::iterator;
   using const_iterator = std::map<RenderLayer, RenderSublayer>::const_iterator;

   RenderList() = default;
   ~RenderList() = default;

   void Push(const RenderItem& item, RenderLayer layer, uint16_t zIndex) { m_layers[layer][zIndex].push_back(item); }
   
   void ReserveBatchSpace(size_t estimatedSize)
   {
      for (auto& [_, sublayer] : m_layers)
      {
         for (auto& [_, batch] : sublayer)
         {
            batch.reserve(estimatedSize);
         }
      }
   }

   inline void Swap(RenderList& other) { m_layers.swap(other.m_layers); }

   void Clear()
   {
      for (auto& layer : m_layers)
      {
         for (auto& sublayer : layer.second)
         {
            sublayer.second.clear();
         }
      }
   }

   size_t Size() const
   {
      size_t totalSize = 0;
      for (const auto& layer : m_layers)
      {
         for (const auto& sublayer : layer.second)
         {
            totalSize += sublayer.second.size();
         }
      }
      return totalSize;
   }

   iterator begin() { return m_layers.begin(); }
   const_iterator begin() const { return m_layers.begin(); }
   iterator end() { return m_layers.end(); }
   const_iterator end() const { return m_layers.end(); }

private:
   std::map<RenderLayer, RenderSublayer> m_layers;
};
