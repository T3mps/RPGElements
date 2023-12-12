#pragma once

#include <format>
#include <iostream>
#include <string>

class Console
{
public:
   static void ClearScreen();

   static void HideCursor();
   static void ShowCursor();
   static void MoveCursorTo(size_t row, size_t col);

   static bool GetConsoleWindowSize(size_t& columns, size_t& rows);
private:
   Console() = delete;
};
