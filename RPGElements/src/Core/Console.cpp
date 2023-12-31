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

bool Console::GetWindowSize(size_t& rows, size_t& columns)
{
#ifdef _WIN32
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
   if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
      return false;

   rows = static_cast<size_t>(csbi.srWindow.Bottom) - csbi.srWindow.Top + 1;
   columns = static_cast<size_t>(csbi.srWindow.Right) - csbi.srWindow.Left + 1;
#else
   struct winsize ws;
   if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
      return false;

   rows = ws.ws_row;
   columns = ws.ws_col;
#endif
   return true;
}

bool Console::SetWindowSize(size_t rows, size_t columns)
{
#ifdef _WIN32
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   if (hConsole == INVALID_HANDLE_VALUE)
      return false;

   SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(columns - 1), static_cast<SHORT>(rows - 1) };
   if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
      return false;

   COORD bufferSize = { static_cast<SHORT>(columns), static_cast<SHORT>(rows) };
   if (!SetConsoleScreenBufferSize(hConsole, bufferSize))
      return false;

   return true;
#else
   std::cout << "\033[8;" << rows << ";" << columns << "t";
   return false;
#endif
}
