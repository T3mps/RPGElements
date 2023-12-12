#pragma once

#include <vector>

#include "Sprite.h"

struct RenderItem
{
   Sprite::Frame frame;
   size_t row;
   size_t col;
};

using RenderList = std::vector<RenderItem>;
