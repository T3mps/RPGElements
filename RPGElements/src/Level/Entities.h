#pragma once

#include <functional>
#include <unordered_map>

#include "Components.h"
#include "entt.hpp"

namespace Entity
{
   using CreationFunction = std::function<void(entt::registry&, size_t, size_t)>;

   static void CreatePlayer(entt::registry& registry, size_t x, size_t y)
   {
      auto entity = registry.create();
      registry.emplace<Component::PlayerTag>(entity);
      registry.emplace<Component::Position>(entity, x, y);
      registry.emplace<Component::Renderable>(entity, Sprites::PLAYER, -1);
   }

   static void CreateGoblin(entt::registry& registry, size_t x, size_t y)
   {
      auto entity = registry.create();
      registry.emplace<Component::Position>(entity, x, y);
      registry.emplace<Component::Renderable>(entity, Sprites::GOBLIN, 0);
   }

   static const std::unordered_map<std::string, CreationFunction> CreationMap =
   {
      {"player", &CreatePlayer},
      {"goblin", &CreateGoblin}
   };
}