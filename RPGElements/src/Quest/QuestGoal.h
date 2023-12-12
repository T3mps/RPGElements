#pragma once

#include <string>
#include <functional>
#include <memory>

class QuestGoal
{
public:
   enum class State
   {
      NOT_STARTED = 0,
      IN_PROGRESS,
      COMPLETED
   };

   using CompletionCriteria = std::function<bool()>;
   using CompletionCallback = std::function<void()>;

   QuestGoal(const std::string& name, CompletionCriteria completionCriteria, CompletionCallback completionCallback, bool enabled = true);
   ~QuestGoal() = default;

   bool CheckCompletion();

   inline const std::string& GetName() const { return m_name; }
   inline State GetState() const { return m_state; }

   inline void SetCompletionCriteria(CompletionCriteria criteria) { m_completionCriteria = criteria; }
   inline void SetCompletionCallback(CompletionCallback callback) { m_completionCallback = callback; }

   inline bool IsCompleted() const { return m_state == State::COMPLETED; }

   inline std::shared_ptr<QuestGoal> GetNextGoal() const { return m_nextGoal; }
   inline void SetNextGoal(std::shared_ptr<QuestGoal> nextGoal) { m_nextGoal = nextGoal; }
   inline bool IsLastGoal() const { return m_nextGoal == nullptr; }
   
   inline void Enable() { m_enabled = true; }
   inline void Disable() { m_enabled = false; }
   inline bool IsEnabled() const { return m_enabled; }

private:
   std::string m_name;
   State m_state;
   CompletionCriteria m_completionCriteria;
   CompletionCallback m_completionCallback;

   std::shared_ptr<QuestGoal> m_nextGoal;

   bool m_enabled;
};
