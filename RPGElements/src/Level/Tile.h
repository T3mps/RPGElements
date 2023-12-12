#pragma once

#include <optional>
#include <string>
#include <vector>

#include "../DIVE/DIVETag.h"
#include "../Rendering/Sprite.h"

struct Tile;

using TileGrid = std::vector<std::vector<Tile>>;

struct Tile
{
   Sprite sprite;
   bool walkable;
   DIVE::TagCompound metadata;
   
   Tile() : sprite('?'), walkable(false) {}
   Tile(const Sprite& sprite, bool walkable = true) : sprite(sprite), walkable(walkable) {}

   template <typename T>
   inline void AddMetadata(const std::string& key, T&& value) { DIVE::SetTag(metadata, key, std::forward<T>(value)); }

   template <typename T>
   std::optional<T> GetMetadata(const std::string& key) const { return DIVE::GetTag<T>(metadata, key); }
};


namespace Tiles
{
   const Tile FLOOR_TILE(Sprites::FLOOR);
   const Tile WALL_TILE(Sprites::WALL, false);
}
