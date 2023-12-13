#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Buffer.h"
#include "../GameTelemetry.h"
#include "RenderList.h"
#include "Viewport.h"

class TextRenderer
{
public:
   TextRenderer() = default;
   explicit TextRenderer(const Viewport& viewport);

   void PreRender();
   void Render();
   void PostRender();
   
   inline void SubmitRenderList(RenderList& renderList) { m_renderList.Swap(renderList); }

   inline void SendTelemetry(std::shared_ptr<GameTelemetry> telemetry) { m_telemetry = telemetry; }

private:
   void RenderUI() const;

   struct RenderItemComparator
   {
      bool operator()(const RenderItem& a, const RenderItem& b) const
      {
         if (a.row == b.row)
            return a.col < b.col;
         return a.row < b.row;
      }
   };

  /* bool InFogOfWarRadius(int playerRow, int playerCol, int itemRow, int itemCol, int radius)
   {
      int dx = playerCol - itemCol;
      int dy = playerRow - itemRow;
      return dx * dx + dy * dy <= radius * radius;
   }*/

   Viewport m_viewport;
   RenderList m_renderList;
   Buffer m_frontBuffer;
   Buffer m_backBuffer;
   std::shared_ptr<GameTelemetry> m_telemetry;
};
