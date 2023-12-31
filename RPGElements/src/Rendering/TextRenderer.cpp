#include "TextRenderer.h"

#include <algorithm>

#include"../Core/Console.h"

TextRenderer::TextRenderer(std::shared_ptr<Camera> camera, const Viewport& viewport) :
   m_camera(camera),
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
   if (!m_renderList.IsDirty())
      return;

   Camera::Extents cameraExtents = m_camera->GetExtents();
   const size_t rowStart = cameraExtents.rowStart;
   const size_t colStart = cameraExtents.colStart;
   const size_t rowEnd = std::min(cameraExtents.rowEnd, m_viewport.height);
   const size_t colEnd = std::min(cameraExtents.colEnd, m_viewport.width);

   for (auto& [_, sublayers] : m_renderList)
   {
      for (auto& [_, grid] : sublayers)
      {
         for (auto& row : grid)
         {
            if (std::any_of(row.begin(), row.end(), [](const RenderItem& item) { return item.isDirty; }))
               std::sort(row.begin(), row.end(), RenderItemComparator());
         }

         for (size_t row = rowStart; row < rowEnd && row < grid.size(); ++row)
         {
            for (size_t col = colStart; col < colEnd && col < grid[row].size(); ++col)
            {
               RenderItem& item = grid[row][col];

               if (item.isDirty && m_viewport.InBounds(row, col))
               {
                  RenderUnit offsetRow = row - rowStart;
                  RenderUnit offsetCol = col - colStart;
                  m_backBuffer.SetFrame(offsetRow, offsetCol, item.frame);
                  item.isDirty = false;
               }
            }
         }
      }
   }

   std::cout << m_backBuffer;
   m_renderList.ClearDirtyFlag();
   
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
