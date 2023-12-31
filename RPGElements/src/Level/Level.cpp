#include "Level.h"

#include <ranges>

#include "Components.h"
#include "Entities.h"

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
      }
      else if (ch == '}')
      {
         readingName = false;
         auto tile = Tiles::TileMap.find(articleName) != Tiles::TileMap.end() ?
                     Tiles::TileMap.at(articleName) :
                     Entity::CreationMap.count(articleName) > 0 ?
                     CreateEntityTile(articleName, currentRowWidth, m_tiles.size()) :
                     Tile();

         row.push_back(std::move(tile));
         currentRowWidth++;
      }
      else if (readingName)
      {
         articleName += ch;
      }
      else if (ch == '\n')
      {
         m_tiles.push_back(std::move(row));
         maxWidth = std::max(maxWidth, currentRowWidth);
         row.clear();
         currentRowWidth = 0;
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

Tile Level::CreateEntityTile(const std::string& entityName, size_t x, size_t y)
{
   Entity::CreationMap.at(entityName)(m_registry, x, y);
   return Tiles::TileMap.at("floor");
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
   m_renderList.Clear();

   for (size_t row = 0; row < m_tiles.size(); ++row)
   {
      for (size_t col = 0; col < m_tiles[row].size(); ++col)
      {
         Tile tile = m_tiles[row][col];
         m_renderList.SetItem(tile.sprite.GetCurrentFrame(), row, col, RenderLayer::Background, tile.zIndex);
      }
   }

   m_registry.view<Component::Renderable, Component::Position>().each([&](auto entity, const auto& renderable, const auto& position)
   {
      m_renderList.SetItem(renderable.sprite.GetCurrentFrame(), position.y, position.x, RenderLayer::Foreground, renderable.zIndex);
   });

   return m_renderList;
}
