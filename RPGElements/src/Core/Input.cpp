#include "Input.h"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "conio.h"

InputHandler::InputHandler() :
   m_running(false),
   m_lastChar('\0')
{
}

InputHandler::~InputHandler()
{
   Stop();
}

void InputHandler::Start()
{
   if (!m_running.load())
   {
      m_running.store(true);
      m_inputThread = std::thread(&InputHandler::Poll, this);
   }
}

char InputHandler::GetInput()
{
   char ch = m_lastChar.load();
   m_lastChar.store('\0'); // Reset lastChar after reading
   return ch;
}

void InputHandler::Stop()
{
   if (m_running.load())
   {
      m_running.store(false);
      if (m_inputThread.joinable())
         m_inputThread.join();
   }
}

void InputHandler::Poll()
{
#ifdef _WIN32
   // Windows-specific input handling
   while (m_running.load())
   {
      if (_kbhit())
      {
         char ch = _getch();
         m_lastChar.store(ch);
      }
      std::this_thread::sleep_for(THREAD_SLEEP_TIME);
   }
#else
   // Unix-like system input handling
   struct termios oldt;
   if (tcgetattr(STDIN_FILENO, &oldt) == -1)
      throw std::runtime_error("Failed to get terminal settings: " + std::string(strerror(errno)));

   struct termios newt = oldt;
   newt.c_lflag &= ~(ICANON | ECHO);
   if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == -1)
      throw std::runtime_error("Failed to set terminal settings: " + std::string(strerror(errno)));

   try
   {
      while (m_running.load())
      {
         int ch = getchar();
         if (ch != EOF)
            m_lastChar.store(static_cast<char>(ch));
         std::this_thread::sleep_for(THREAD_SLEEP_TIME);
      }
   }
   catch (...)
   {
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal settings
      throw; // Re-throw the exception
   }

   if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) == -1)
      throw std::runtime_error("Failed to restore terminal settings: " + std::string(strerror(errno)));
#endif
}
