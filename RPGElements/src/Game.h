#pragma once

#include <chrono>
#include <thread>

#include "Core/Event.h"
#include "Core/Input.h"
#include "Level/Level.h"
#include "Level/Systems.h"
#include "Rendering/TextRenderer.h"

class Game
{
public:
   Game(Level& level) :
      m_level(level),
      m_renderer(Viewport(0, 0, level.GetWidth(), level.GetHeight())),
      m_running(true),
      m_updatesPerSecond(60U)
   {
      m_input.Start();

      m_eventDispatcher.RegisterListener(Event::Type::KeyPress, [this](Event& event)
         { return this->OnKeyPress(static_cast<KeyPressEvent&>(event)); });

      m_level.RegisterEventListener([&](Event& event) -> bool
         { return System::PlayerMovement(event, m_level); });
   }

   ~Game()
   {
      m_input.Stop();
   }

   void Run()
   {
      using Clock = std::chrono::high_resolution_clock;
      using std::chrono::duration_cast;
      using std::chrono::milliseconds;

      const auto updateDuration = milliseconds(1000 / m_updatesPerSecond);

      auto lastUpdate = Clock::now();
      auto lastFrameTime = lastUpdate;

      while (m_running)
      {
         auto now = Clock::now();
         auto deltaTime = duration_cast<milliseconds>(now - lastFrameTime).count() / 1000.0f; // Delta time in seconds
         lastFrameTime = now;

         while (now - lastUpdate >= updateDuration)
         {
            Update(deltaTime);
            lastUpdate += updateDuration;
         }

         Render();

         std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Small delay to prevent CPU overuse
      }
   }

private:
   void ProcessInput()
   {
      char input = m_input.GetInput();
      if (input != 0)
      {
         KeyPressEvent event(input);
         m_eventDispatcher.Dispatch(event);
      }
   }

   bool OnKeyPress(KeyPressEvent& event)
   {
      if (m_level.OnEvent(event))
         event.SetProcessed(true);
      return event.IsProcessed();
   }

   void Update(float deltaTime)
   {
      ProcessInput();
      m_level.Update(deltaTime);
   }

   void Render()
   {
      auto renderList = m_level.GetRenderList();
      m_renderer.SubmitRenderList(renderList);

      m_renderer.PreRender();
      m_renderer.Render();
      m_renderer.PostRender();
   }

   InputHandler m_input;
   EventDispatcher m_eventDispatcher;
   Level& m_level;
   TextRenderer m_renderer;
   bool m_running;
   uint32_t m_updatesPerSecond;
};
