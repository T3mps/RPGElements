#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace DIVE
{
   struct Tag;

   using ByteArray = std::vector<std::int8_t>;
   using ShortArray = std::vector<std::int16_t>;
   using IntArray = std::vector<std::int32_t>;
   using LongArray = std::vector<std::int64_t>;
   using TagList = std::vector<std::shared_ptr<Tag>>;
   using TagCompound = std::unordered_map<std::string, std::shared_ptr<Tag>>;

   using TagValue = std::variant
      <
      std::monostate, // to represent 'no value'
      std::int32_t,
      std::float_t,
      std::string,
      ByteArray,
      ShortArray,
      IntArray,
      LongArray,
      TagList,
      TagCompound
      >;

   struct Tag
   {
      std::string name;
      TagValue value;
   };

   template <typename T>
   std::optional<T> GetTag(const TagCompound& compound, const std::string& key);

   template <typename T>
   void SetTag(TagCompound& compound, const std::string& key, T&& value);

   // -- Implementation --

   template <typename T>
   std::optional<T> GetTag(const TagCompound& compound, const std::string& key)
   {
      auto it = compound.find(key);
      if (it != compound.end() && it->second)
      {
         if (auto val = std::get_if<T>(&it->second->value))
            return *val;
      }
      return std::nullopt;
   }

   template <typename T>
   void SetTag(TagCompound& compound, const std::string& key, T&& value)
   {
      auto& tag = compound[key];
      if (!tag)
         tag = std::make_shared<Tag>();
      tag->name = key;
      tag->value = std::forward<T>(value);
   }
}