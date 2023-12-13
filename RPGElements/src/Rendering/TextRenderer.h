#pragma once

#include <string>
#include <vector>

#include "Buffer.h"
#include "RenderList.h"
#include "Viewport.h"

class TextRenderer
{
public:
   explicit TextRenderer(const Viewport& viewport);

   void PreRender();
   void Render();
   void PostRender();
   
   inline void SubmitRenderList(RenderList& renderList) { m_renderList.Swap(renderList); }

private:
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
};
