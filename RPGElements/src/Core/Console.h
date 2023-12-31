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

   static bool GetWindowSize(size_t& rows, size_t& cols);
   static bool SetWindowSize(size_t rows, size_t cols);
private:
   Console() = delete;
};
