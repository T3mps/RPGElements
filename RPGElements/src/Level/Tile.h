#pragma once

#include <optional>
#include <string>
#include <vector>
#include <unordered_map>

#include "../DIVE/DIVETag.h"
#include "../Rendering/Sprite.h"

struct Tile;

using TileGrid = std::vector<std::vector<Tile>>;

struct Tile
{
   Sprite sprite;
   bool walkable;
   uint16_t zIndex;
   DIVE::TagCompound metadata;
   
   Tile() : sprite('?'), walkable(false), zIndex(0) {}
   Tile(const Sprite& sprite, bool walkable = true, uint16_t zIdx = 0) : sprite(sprite), walkable(walkable), zIndex(zIdx) {}

   template <typename T>
   inline void AddMetadata(const std::string& key, T&& value) { DIVE::SetTag(metadata, key, std::forward<T>(value)); }

   template <typename T>
   std::optional<T> GetMetadata(const std::string& key) const { return DIVE::GetTag<T>(metadata, key); }
};

namespace Tiles
{
   static const Tile FLOOR(Sprites::FLOOR);
   static const Tile WALL(Sprites::WALL, false);

   static const std::unordered_map<std::string, Tile> TileMap =
   {
      { "floor", Tiles::FLOOR},
      { "wall", Tiles::WALL}
   };
}
