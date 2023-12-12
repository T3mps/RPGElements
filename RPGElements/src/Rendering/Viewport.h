#pragma once

struct Viewport
{
   const size_t x0;
   const size_t y0;
   const size_t x1;
   const size_t y1;
   const size_t width;
   const size_t height;

   Viewport(size_t x00, size_t y00, size_t x01, size_t y01) :
      x0(x00),
      y0(y00),
      x1(x01),
      y1(y01),
      width(x01 - x00),
      height(y01 - y00)
   {
   }
};
