#include "TextRenderer.h"

#include <algorithm>

#include"../Core/Console.h"

TextRenderer::TextRenderer(const Viewport& viewport) :
   m_viewport(viewport),
   m_frontBuffer(viewport),
   m_backBuffer(viewport)
{
   Console::SetWindowSize(viewport.row1 + 1, viewport.col1 + 1);
}

void TextRenderer::PreRender()
{
   Console::MoveCursorTo(m_viewport.col0, m_viewport.row0);
   Console::HideCursor();
}

void TextRenderer::Render()
{
   // const int fogRadius = 5;

   if (m_renderList.IsDirty())
   {
      for (auto& [layer, sublayers] : m_renderList)
      {
         for (auto& [zIndex, grid] : sublayers)
         {
            for (auto& row : grid)
            {
               if (std::any_of(row.begin(), row.end(), [](const RenderItem& item) { return item.isDirty; }))
                  std::sort(row.begin(), row.end(), RenderItemComparator());
            }
            for (size_t row = 0; row < grid.size(); ++row)
            {
               for (size_t col = 0; col < grid[row].size(); ++col)
               {
                  auto& item = grid[row][col];

                  if (item.isDirty && m_viewport.InBounds(item.row, item.col))
                  {
                     m_backBuffer.SetFrame(item.row - m_viewport.row0, item.col - m_viewport.col0, item.frame);
                     item.isDirty = false;
                  }
               }
            }
         }
      }
      m_renderList.ClearDirtyFlag();
   }

   std::cout << m_backBuffer;
   
   //RenderUI();
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

bool TextRenderer::RenderItemComparator::operator()(const RenderItem& a, const RenderItem& b) const
{
   if (a.row == b.row)
      return a.col < b.col;
   return a.row < b.row;
}
