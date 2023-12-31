#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

class Event
{
public:
   enum class Type
   {
      Unknown,
      KeyPress
   };

   Event() : m_type(Type::Unknown), m_processed(false) {}
   Event(Type eventType) : m_type(eventType), m_processed(false) {}

   bool IsProcessed() const { return m_processed; }
   void SetProcessed(bool state) { m_processed = state; }
   Type GetType() const { return m_type; }

protected:
   Type m_type;
   bool m_processed;
};

class KeyPressEvent : public Event
{
public:
   KeyPressEvent(char key) : Event(Type::KeyPress), m_key(key) {}

   char GetKey() const { return m_key; }

protected:
   char m_key;
};

using EventListener = std::function<bool(Event&)>;

class EventDispatcher
{
public:
   void RegisterListener(Event::Type type, EventListener listener) {
      m_listeners[type].push_back(std::move(listener));
   }

   void Dispatch(Event& event)
   {
      auto it = m_listeners.find(event.GetType());
      if (it != m_listeners.end())
      {
         for (auto& listener : it->second)
         {
            if (event.IsProcessed())
               break;
            listener(event);
         }
      }
   }

private:
   std::unordered_map<Event::Type, std::vector<EventListener>> m_listeners;
};
