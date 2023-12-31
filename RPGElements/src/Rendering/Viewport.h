#pragma once

struct Viewport
{
   RenderUnit row0;
   RenderUnit col0;
   RenderUnit row1;
   RenderUnit col1;
   RenderUnit width;
   RenderUnit height;

   Viewport(RenderUnit row00 = 0, RenderUnit col00 = 0, RenderUnit row01 = 0, RenderUnit col01 = 0) :
      row0(row00),
      col0(col00),
      row1(row01),
      col1(col01),
      width(col01 - col00),
      height(row01 - row00)
   {
   }

   inline bool InBounds(RenderUnit row, RenderUnit col) { return row >= row0 && row < row1 && col >= col0 && col < col1; }
};

namespace Viewports
{
   static const Viewport STANDARD_80x25(0, 0, 25, 80);
   static const Viewport EXTENDED_120x30(0, 0, 30, 120);
   static const Viewport WIDE_100x40(0, 0, 40, 100);
   static const Viewport COMPACT_60x20(0, 0, 20, 60);
   static const Viewport ASPECT_RATIO_4_3(0, 0, 30, 40);
   static const Viewport ASPECT_RATIO_16_9(0, 0, 22, 80);
}
