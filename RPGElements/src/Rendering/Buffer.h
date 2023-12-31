#pragma once

#include <string>
#include <vector>

#include "Defines.h"
#include "Sprite.h"
#include "Viewport.h"

class Buffer
{
public:
   using iterator = std::vector<std::vector<Sprite::Frame>>::iterator;
   using const_iterator = std::vector<std::vector<Sprite::Frame>>::const_iterator;

   Buffer() = default;
   Buffer(Viewport viewport);

   template<typename T>
   class ProxyTemplate
   {
   public:
      auto& operator[](RenderUnit col) { return m_row[col]; }

   private:
      ProxyTemplate(T& row) : m_row(row) {}
      
      T& m_row;

      friend Buffer;
   };

   using Proxy = ProxyTemplate<std::vector<Sprite::Frame>>;
   using ConstProxy = ProxyTemplate<const std::vector<Sprite::Frame>>;

   Proxy operator[](RenderUnit row) { return Proxy(m_data[row]); }
   ConstProxy operator[](RenderUnit row) const { return ConstProxy(m_data[row]); }

   friend std::ostream& operator<<(std::ostream& os, const Buffer& buffer);

   bool operator==(const Buffer& other) const;

   void SetFrame(RenderUnit row, RenderUnit col, const Sprite::Frame& frame);
   Sprite::Frame GetFrame(RenderUnit row, RenderUnit col);
   const Sprite::Frame GetFrame(RenderUnit row, RenderUnit col) const;

   RenderUnit GetRows() const { return m_data.size(); }
   RenderUnit GetCols() const { return m_data.empty() ? 0 : m_data[0].size(); }

   bool IsEmpty() const { return m_data.empty(); }

   iterator begin() { return m_data.begin(); }
   const_iterator begin() const { return m_data.begin(); }
   iterator end() { return m_data.end(); }
   const_iterator end() const { return m_data.end(); }

private:
   inline bool InBounds(RenderUnit row, RenderUnit col) const { return row >= 0 && row < GetRows() && col >= 0 && col < GetCols(); }

   std::vector<std::vector<Sprite::Frame>> m_data;
   Viewport m_viewport;
};
