#pragma once

#include <deque>
#include <span>
#include <sstream>
#include <string>
#include <vector>

#include "../Level/Components.h"
#include"../Core/Console.h"
#include "Buffer.h"
#include "entt.hpp"
#include "Sprite.h"
#include "Viewport.h"

#ifdef _WIN32
   #include "windows.h"
#endif

class TextRenderer
{
public:

   static constexpr size_t DOUBLE_BUFFER = 2;
   static constexpr size_t TRIPLE_BUFFER = 3;

   TextRenderer(const Viewport& viewport, size_t bufferCount = DOUBLE_BUFFER) :
      m_viewport(viewport),
      m_buffers(bufferCount, Buffer(viewport.height, viewport.width)),
      m_lastRenderedBuffer(m_buffers.back())
   {
   }

   void PreRender()
   {
      Console::MoveCursorTo(0, 0);
      Console::HideCursor();
      if (m_lastRenderedBuffer.IsEmpty())
         m_lastRenderedBuffer = m_buffers.back();
   }

   void Render()
   {
      Buffer& nextBuffer = m_buffers.back();

      for (const auto& item : m_renderList)
      {
         if (InBounds(item.col, item.row))
            m_buffers.back().SetFrame(item.row, item.col, item.frame);
      }

      std::stringstream ss;
      for (size_t row = 0; row < nextBuffer.GetRows(); ++row)
      {
         for (size_t col = 0; col < nextBuffer.GetCols(); ++col)
         {
            const auto& frame = nextBuffer.GetFrame(row, col);
            ss << frame.color << frame.character;
         }
         ss << '\n';
      }

      m_renderString = ss.str();
   }

   void PostRender()
   {
      std::cout << m_renderString;

      SwapBuffers();

      Console::ShowCursor();
   }
   
   inline void SubmitRenderList(RenderList& renderList) { m_renderList.swap(renderList); }

private:
   void SwapBuffers()
   {
      m_buffers.push_front(std::move(m_buffers.back()));
      m_buffers.pop_back();
   }

   inline bool InBounds(size_t row, size_t col)
   {
      size_t width, height;
      Console::GetConsoleWindowSize(width, height);
      return (row >= 0 && row < width) && (col >= 0 && col < height);
   }

   Viewport m_viewport;
   RenderList m_renderList;
   std::deque<Buffer> m_buffers;
   Buffer& m_lastRenderedBuffer;
   std::string m_renderString;
};
