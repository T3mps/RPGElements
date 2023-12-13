#include "TextRenderer.h"

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

   for (const auto& item : m_renderList)
   {
      if (m_viewport.InBounds(item.col, item.row) /* && InFogOfWarRadius(playerRow, playerCol, item.row, item.col, fogRadius) */)
         m_frontBuffer.SetFrame(item.row - m_viewport.y0, item.col - m_viewport.x0, item.frame);
   }

   std::cout << m_frontBuffer;
}

void TextRenderer::PostRender()
{
   std::swap(m_frontBuffer, m_backBuffer);
   Console::ShowCursor();
}
