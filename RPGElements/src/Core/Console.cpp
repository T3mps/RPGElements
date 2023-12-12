#include "Console.h"

#ifdef _WIN32
   #include "windows.h"
#else
   #include <sys/ioctl.h>
   #include <unistd.h>
#endif

void Console::ClearScreen()
{
#ifdef _WIN32
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   COORD coordScreen = { 0, 0 };
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

   if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
      return;

   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   if (!FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten))
      return;

   if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
      return;

   if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
      return;

   SetConsoleCursorPosition(hConsole, coordScreen);
#else
   std::cout << "\033[2J\033[H";
#endif
}

void Console::HideCursor()
{
#ifdef _WIN32
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO cursorInfo;

   GetConsoleCursorInfo(consoleHandle, &cursorInfo);
   cursorInfo.bVisible = false;
   SetConsoleCursorInfo(consoleHandle, &cursorInfo);
#else
   std::cout << "\033[?25l";
#endif
}

void Console::ShowCursor()
{
#ifdef _WIN32
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO cursorInfo;

   GetConsoleCursorInfo(consoleHandle, &cursorInfo);
   cursorInfo.bVisible = true;
   SetConsoleCursorInfo(consoleHandle, &cursorInfo);
#else
   std::cout << "\033[?25h";
#endif
}

void Console::MoveCursorTo(size_t row, size_t col)
{
   auto cursorPosition = std::format("\033[{};{}H", row + 1, col + 1);
   std::cout << cursorPosition;
}

bool Console::GetConsoleWindowSize(size_t& columns, size_t& rows)
{
#ifdef _WIN32
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
   if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
      return false;

   columns = static_cast<size_t>(csbi.srWindow.Right) - csbi.srWindow.Left + 1;
   rows = static_cast<size_t>(csbi.srWindow.Bottom) - csbi.srWindow.Top + 1;
#else
   struct winsize ws;
   if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
      return false;

   columns = ws.ws_col;
   rows = ws.ws_row;
#endif
   return true;
}
