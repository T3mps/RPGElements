#pragma once

#include "Defines.h"

class Camera
{
public:
   struct Extents
   {
      RenderUnit rowStart;
      RenderUnit colStart;
      RenderUnit rowEnd;
      RenderUnit colEnd;
   };

   Camera(int m_rowViewCount, int m_colViewCount) :
      m_row(0),
      m_col(0),
      m_rowViewCount(m_rowViewCount),
      m_colViewCount(m_colViewCount),
      m_halfRowViewCount(static_cast<int>(m_rowViewCount * 0.5)),
      m_halfColViewCount(static_cast<int>(m_colViewCount * 0.5))
   {
   }

   ~Camera() = default;

   Extents GetExtents() const
   {
      const size_t rowStart = (m_row > m_halfRowViewCount) ? m_row - m_halfRowViewCount : 0;
      const size_t colStart = (m_col > m_halfColViewCount) ? m_col - m_halfColViewCount : 0;
      const size_t rowEnd = std::max<size_t>(m_row + m_halfRowViewCount, m_rowViewCount);
      const size_t colEnd = std::max<size_t>(m_col + m_halfColViewCount, m_colViewCount);

      return { rowStart, colStart, rowEnd, colEnd };
   }

   inline RenderUnit GetRow() { return m_row; }
   inline void SetRow(RenderUnit row) { m_row = row; }
   inline RenderUnit GetCol() { return m_col; }
   inline void SetCol(RenderUnit col) { m_col = col; }

private:
   RenderUnit m_row;
   RenderUnit m_col;
   int m_rowViewCount;
   int m_colViewCount;
   int m_halfRowViewCount;
   int m_halfColViewCount;
};
