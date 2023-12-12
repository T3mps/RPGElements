#include "Level.h"

#include "Components.h"
#include "Entities.h"

std::unordered_map<std::string, Tile> Level::TILE_FACTORY =
{
   { "floor", Tiles::FLOOR_TILE },
   { "wall", Tiles::WALL_TILE }
};

Level::Level(const std::string& levelString)
{
   LoadFromString(levelString);
}

void Level::LoadFromString(const std::string& levelString)
{
   std::vector<Tile> row;
   std::string articleName;
   bool readingName = false;
   size_t currentRowWidth = 0;
   size_t maxWidth = 0;

   for (const char& ch : levelString)
   {
      if (ch == '{')
      {
         readingName = true;
         articleName.clear();
         continue;
      }
      else if (ch == '}')
      {
         readingName = false;

         Tile tile;
         if (Entity::CreationMap.count(articleName) > 0)
         {
            Entity::CreationMap[articleName](m_registry, currentRowWidth, m_tiles.size());
            tile = TILE_FACTORY["floor"]; // Assuming floor under entities
         }
         else if (TILE_FACTORY.count(articleName) > 0)
         {
            tile = TILE_FACTORY[articleName];
         }

         row.push_back(std::move(tile));
         ++currentRowWidth;

         continue;
      }

      if (readingName)
      {
         articleName += ch;
      }
      else if (ch == '\n')
      {
         m_tiles.push_back(std::move(row));
         maxWidth = std::max(maxWidth, currentRowWidth);
         currentRowWidth = 0;
         row.clear();
      }
   }

   if (!row.empty())
   {
      m_tiles.push_back(std::move(row));
      maxWidth = std::max(maxWidth, currentRowWidth);
   }

   m_width = maxWidth;
   m_height = m_tiles.size();
}

void Level::Update(float deltaTime)
{
   for (auto& row : m_tiles)
   {
      for (auto& tile : row)
      {
         tile.sprite.NextFrame(deltaTime);
      }
   }

   m_registry.view<Component::Renderable>().each([&](auto& renderable)
      { renderable.sprite.NextFrame(deltaTime); });
}

bool Level::OnEvent(Event& event)
{
   for (auto& listener : m_eventListeners)
   {
      if (listener(event))
         return true;
   }
   return false;
}

Tile* Level::GetTile(size_t x, size_t y)
{
   if (x < 0 || x >= m_width || y < 0 || y >= m_height)
      return nullptr;
   return &m_tiles[y][x];
}

const Tile* Level::GetTile(size_t x, size_t y) const
{
   if (x < 0 || x >= m_width || y < 0 || y >= m_height)
      return nullptr;
   return &m_tiles[y][x];
}

RenderList Level::GetRenderList()
{
   RenderList renderList;

   for (size_t row = 0; row < m_tiles.size(); ++row)
   {
      for (size_t col = 0; col < m_tiles[row].size(); ++col)
      {
         renderList.push_back(RenderItem(m_tiles[row][col].sprite.GetCurrentFrame(), row, col));
      }
   }

   m_registry.view<Component::Renderable, Component::Position>().each([&](const auto& renderable, const auto& pos)
      { renderList.push_back(RenderItem(renderable.sprite.GetCurrentFrame(), pos.y, pos.x)); });

   return renderList;
}
