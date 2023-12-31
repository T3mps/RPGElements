#pragma once

#include <atomic>
#include <chrono>
#include <ratio>
#include <thread>

class InputHandler
{
public:
   static constexpr std::chrono::duration<long long, std::milli> THREAD_SLEEP_TIME = std::chrono::milliseconds(16);

   InputHandler();
   ~InputHandler();

   void Start();
   char GetInput();
   void Stop();

   inline bool IsRunning() const { return m_running.load(); }

private:
   void Poll();

   std::atomic<bool> m_running;
   std::atomic<char> m_lastChar;
   std::thread m_inputThread;
};
