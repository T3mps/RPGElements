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

      Renderable(Sprite renderableSprite) : sprite(renderableSprite) {}
   };
}