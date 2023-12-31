#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../Core/Console.h"
#include "../GameTelemetry.h"
#include "Buffer.h"
#include "Camera.h"
#include "RenderList.h"
#include "Viewport.h"

class TextRenderer
{
public:
   TextRenderer(std::shared_ptr<Camera> camera, const Viewport& viewport);

   void PreRender();
   void Render();
   void PostRender();
   
   inline void SubmitRenderList(RenderList& renderList) { m_renderList.Swap(renderList); }

   inline void SendTelemetry(std::shared_ptr<GameTelemetry> telemetry) { m_telemetry = telemetry; }

private:
   void RenderUI() const;

   struct RenderItemComparator
   {
      bool operator()(const RenderItem& a, const RenderItem& b) const;
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
   std::shared_ptr<Camera> m_camera;

   std::shared_ptr<GameTelemetry> m_telemetry;
};
