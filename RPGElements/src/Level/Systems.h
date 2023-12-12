#pragma once

#include "../Core/Event.h"
#include "Components.h"
#include "../Level/Level.h"

namespace System
{
   static bool PlayerMovement(Event& event, Level& level)
   {
      if (event.GetType() != Event::Type::KeyPress)
         return false;

      const auto& keyPressEvent = static_cast<const KeyPressEvent&>(event);
      char key = keyPressEvent.GetKey();

      auto view = level.GetRegistry().view<Component::Position, Component::PlayerTag>();

      auto& position = view.get<Component::Position>(view.front());
      size_t newX = position.x;
      size_t newY = position.y;

      switch (key)
      {
         case 'W': case 'w': newY -= 1; break;
         case 'A': case 'a': newX -= 1; break;
         case 'S': case 's': newY += 1; break;
         case 'D': case 'd': newX += 1; break;
         default: return false;
      }

      if (const Tile* tile = level.GetTile(newX, newY); tile && tile->walkable)
      {
         position.x = newX;
         position.y = newY;
         return true;
      }

      return false;
   }
}