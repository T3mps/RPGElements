#pragma once

#include "../Rendering/Sprite.h"

namespace Component
{
   struct Tag {};

   struct PlayerTag : public Tag {};

   struct Position
   {
      size_t x, y;
   };

   struct PreviousPosition : public Position {};

   struct Renderable
   {
      Sprite sprite;
      uint16_t zIndex;

      Renderable(Sprite renderableSprite, uint16_t zIdx) : sprite(renderableSprite), zIndex(zIdx) {}
   };
}