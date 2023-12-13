#include "TextRenderer.h"

#include <algorithm>

#include"../Core/Console.h"

TextRenderer::TextRenderer(const Viewport& viewport) :
   m_viewport(viewport),
   m_frontBuffer(viewport.height, viewport.width),
   m_backBuffer(viewport.height, viewport.width)
{
}

void TextRenderer::PreRender()
{
   Console::MoveCursorTo(m_viewport.y0, m_viewport.x0);
   Console::HideCursor();
}

void TextRenderer::Render()
{
   // const int fogRadius = 5;

   for (auto& [layer, sublayers] : m_renderList)
   {
      for (auto& [zIndex, batch] : sublayers)
      {
         if (m_backBuffer != m_frontBuffer)
            std::sort(batch.begin(), batch.end(), RenderItemComparator());

         for (const auto& item : batch)
         {
            if (m_viewport.InBounds(item.col, item.row) /* && InFogOfWarRadius(playerRow, playerCol, item.row, item.col, fogRadius) */)
               m_backBuffer.SetFrame(item.row - m_viewport.y0, item.col - m_viewport.x0, item.frame);
         }
      }
   }

   std::cout << m_backBuffer;
   
   RenderUI();
}

void TextRenderer::PostRender()
{
   std::swap(m_backBuffer, m_frontBuffer);
   Console::ShowCursor();
}

void TextRenderer::RenderUI() const
{
   if (m_telemetry)
      std::cout << m_telemetry->fps << " fps" << std::endl;
}
