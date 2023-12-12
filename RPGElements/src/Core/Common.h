#pragma once

#include <random>
#include <chrono>
#include <limits>

using uuid = uint64_t;
static constexpr uuid INVALID_UUID = std::numeric_limits<uuid>::max();

static uuid generate_uuid()
{
   long long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();

   static std::mt19937_64 rng(now);

   uuid randomID = rng();
   return randomID;
}
