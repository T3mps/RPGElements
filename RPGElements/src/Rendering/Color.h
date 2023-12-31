#pragma once

using Color = const char*;

namespace Colors
{
   static constexpr Color Reset = "\033[0m";
   static constexpr Color Grey = "\033[90m";
   static constexpr Color Black = "\033[30m";
   static constexpr Color Red = "\033[31m";
   static constexpr Color Green = "\033[32m";
   static constexpr Color Yellow = "\033[33m";
   static constexpr Color Blue = "\033[34m";
   static constexpr Color Magenta = "\033[35m";
   static constexpr Color Cyan = "\033[36m";
   static constexpr Color White = "\033[37m";

   static constexpr Color BrightRed = "\033[91m";
   static constexpr Color BrightGreen = "\033[92m";
   static constexpr Color BrightYellow = "\033[93m";
   static constexpr Color BrightBlue = "\033[94m";
   static constexpr Color BrightMagenta = "\033[95m";
   static constexpr Color BrightCyan = "\033[96m";
   static constexpr Color BrightWhite = "\033[97m";
};
