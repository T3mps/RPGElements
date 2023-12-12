#pragma once

#include <memory>
#include <string>

class QuestGoal;

class Quest
{
public:
   enum class State
   {
      NOT_STARTED = 0,
      IN_PROGRESS,
      COMPLETED
   };

   Quest(uint32_t id, const std::string& name);
   ~Quest() = default;

   void Start(bool force = false);
   
   void AddGoal(std::shared_ptr<QuestGoal> goal);
   void Update();
   
   inline bool IsCompleted() const { return m_state == State::COMPLETED; }

   inline uint32_t GetID() const { return m_id; }
   inline const std::string& GetName() const { return m_name; }
   inline State GetState() const { return m_state; }
   inline std::shared_ptr<QuestGoal> GetFirstGoal() const { return m_firstGoal; }
   inline std::shared_ptr<QuestGoal> GetCurrentGoal() const { return m_currentGoal; }

private:
   uint32_t m_id;
   std::string m_name;
   State m_state;
   std::shared_ptr<QuestGoal> m_firstGoal;
   std::shared_ptr<QuestGoal> m_currentGoal;
};