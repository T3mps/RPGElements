#pragma once

#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

#include "../Core/Event.h"
#include "../Rendering/RenderList.h"
#include "../Rendering/Camera.h"
#include "entt.hpp"
#include "Tile.h"

class Level
{
public:
   using iterator = TileGrid::iterator;
   using const_iterator = TileGrid::const_iterator;

   Level() = default;
   explicit Level(const std::string& levelString);
   Level(const Level&) = delete;
   ~Level() = default;

   Level& operator=(const Level&) = delete;

   void LoadFromString(const std::string& levelString);
   Tile CreateEntityTile(const std::string& entityName, size_t x, size_t y);

   void Update(float deltaTime);
   bool OnEvent(Event& event);

   Tile* GetTile(size_t x, size_t y);
   const Tile* GetTile(size_t x, size_t y) const;

   RenderList GetRenderList();

   inline void RegisterEventListener(EventListener listener) { m_eventListeners.push_back(std::move(listener)); }

   inline TileGrid& GetTiles() { return m_tiles; }
   inline const TileGrid& GetTiles() const { return m_tiles; }
   inline size_t GetWidth() const { return m_width; }
   inline size_t GetHeight() const { return m_height; }
   inline entt::registry& GetRegistry() { return m_registry; }
   inline const entt::registry& GetRegistry() const { return m_registry; }
   std::shared_ptr<Camera> GetCamera() const { return m_camera; }
   void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

   iterator begin() { return m_tiles.begin(); }
   iterator end() { return m_tiles.end(); }
   const_iterator begin() const { return m_tiles.end(); }
   const_iterator end() const { return m_tiles.end(); }

private:
   std::vector<EventListener> m_eventListeners;
   TileGrid m_tiles;
   size_t m_width;
   size_t m_height;
   entt::registry m_registry;
   RenderList m_renderList;
   std::shared_ptr<Camera> m_camera;
};
