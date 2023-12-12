#include "Game.h"

int main()
{
   const std::string levelData =
      "{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}\n"
      "{wall}{floor}{player}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{wall}{floor}{floor}{floor}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{goblin}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{wall}{wall}{wall}{wall}{floor}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{floor}{wall}{wall}{wall}{wall}{wall}{wall}{floor}{wall}{wall}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}\n"
      "{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{floor}{floor}{wall}{floor}{floor}{floor}{floor}{floor}{wall}\n"
      "{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}{wall}\n";

   Level level(levelData);
   Game game(level);
   game.Run();

   return 0;
}