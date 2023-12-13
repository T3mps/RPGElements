#pragma once

#include <vector>

#include "Sprite.h"

class RenderList
{
public:
   struct Item
   {
      Sprite::Frame frame;
      size_t row;
      size_t col;
   };

   using iterator = std::vector<Item>::iterator;
   using const_iterator = std::vector<Item>::const_iterator;

   explicit RenderList(size_t viewportDimension = 0)
   {
      m_items.reserve(viewportDimension);
   }

   Item& operator[](size_t index) { return m_items[index]; }
   const Item& operator[](size_t index) const { return m_items[index]; }

   void Push(const Item& item) { m_items.push_back(item); }
   void Push(Sprite::Frame frame, size_t row, size_t col) { m_items.emplace_back(Item{ std::move(frame), row, col }); }
   
   void Swap(RenderList& other) { m_items.swap(other.m_items); }

   void Clear() { m_items.clear(); }
   size_t Size() const { return m_items.size(); }

   iterator begin() { return m_items.begin(); }
   const_iterator begin() const { return m_items.begin(); }
   iterator end() { return m_items.end(); }
   const_iterator end() const { return m_items.end(); }

private:
   std::vector<Item> m_items;
};
