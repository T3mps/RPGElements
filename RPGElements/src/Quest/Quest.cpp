#include "Quest.h"
#include "QuestGoal.h"

Quest::Quest(uint32_t id, const std::string& name) :
   m_id(id),
   m_name(name),
   m_state(State::NOT_STARTED),
   m_firstGoal(nullptr),
   m_currentGoal(nullptr)
{
}

void Quest::Start(bool force /* = false */)
{
   if (m_firstGoal && (force || m_currentGoal == nullptr))
   {
      m_currentGoal = m_firstGoal;
      m_state = State::IN_PROGRESS;
   }
}

void Quest::AddGoal(std::shared_ptr<QuestGoal> goal)
{
   if (!m_firstGoal)
   {
      m_firstGoal = goal;
   }
   else
   {
      std::shared_ptr<QuestGoal> lastGoal = m_firstGoal;
      while (lastGoal->GetNextGoal() != nullptr)
      {
         lastGoal = lastGoal->GetNextGoal();
      }
      lastGoal->SetNextGoal(goal);
   }
}

void Quest::Update()
{
   if (m_state == State::COMPLETED || !m_currentGoal || !m_currentGoal->IsEnabled())
      return;

   if (m_currentGoal->CheckCompletion())
   {
      if (m_currentGoal->IsLastGoal())
         m_state = State::COMPLETED;
      else
         m_currentGoal = m_currentGoal->GetNextGoal();
   }
}
