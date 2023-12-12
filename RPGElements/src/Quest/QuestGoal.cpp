#include "QuestGoal.h"

QuestGoal::QuestGoal(const std::string& name, CompletionCriteria completionCriteria, CompletionCallback completionCallback, bool enabled /* = false */) :
   m_name(name),
   m_state(State::NOT_STARTED),
   m_completionCriteria(completionCriteria),
   m_completionCallback(completionCallback),
   m_enabled(enabled)
{
}

bool QuestGoal::CheckCompletion()
{
   if (m_state == State::COMPLETED)
      return true;


   if (m_completionCriteria())
   {
      if (m_completionCallback)
         m_completionCallback();
      m_state = State::COMPLETED;
      return true;
   }
   else if (m_state == State::NOT_STARTED)
   {
      m_state = State::IN_PROGRESS;
   }

   return false;
}
