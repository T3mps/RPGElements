#pragma once

struct Viewport
{
   size_t x0;
   size_t y0;
   size_t x1;
   size_t y1;
   size_t width;
   size_t height;

   Viewport(size_t x00 = 0, size_t y00 = 0, size_t x01 = 0, size_t y01 = 0) :
      x0(x00),
      y0(y00),
      x1(x01),
      y1(y01),
      width(x01 - x00),
      height(y01 - y00)
   {
   }

   inline bool InBounds(size_t row, size_t col) { return row >= x0 && row < x1 && col >= y0 && col < y1; }
};
