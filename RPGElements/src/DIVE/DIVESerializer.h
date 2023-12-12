#pragma once

#include <algorithm>
#include <sstream>
#include <string>

#include "DIVETag.h"

namespace DIVE
{
   template<typename T>
   concept SerializableType = std::is_arithmetic_v<T> || std::is_same_v<T, std::string>;

   template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
   template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

   template <SerializableType T>
   inline void SerializeBasicType(const T& value, std::ostream& out);

   template <SerializableType T>
   void SerializeVector(const std::vector<T>& vector, std::ostream& out);

   void SerializeString(const std::string& value, std::ostream& out);
   void SerializeTagCompound(const TagCompound& compound, std::ostream& out);
   
   void Serialize(const TagValue& value, std::ostream& out);
   
   void SerializeTag(const Tag& tag, std::ostream& out);

   template <SerializableType T>
   T DeserializeBasicType(std::istream& in);

   template <SerializableType T>
   std::vector<T> DeserializeVector(std::istream& in);

   std::string DeserializeString(std::istream& in);
   TagCompound DeserializeTagCompound(std::istream& in);
   
   TagValue Deserialize(std::istream& in);

   Tag DeserializeTag(std::istream& in);

   // -- Implementation --

   template <SerializableType T>
   inline void SerializeBasicType(const T& value, std::ostream& out) { out.write(reinterpret_cast<const char*>(&value), sizeof(T)); }

   template <SerializableType T>
   void SerializeVector(const std::vector<T>& vector, std::ostream& out)
   {
      SerializeBasicType<std::int32_t>(static_cast<std::int32_t>(vector.size()), out);

      if constexpr (std::is_trivially_copyable_v<T> && !std::is_same_v<T, std::string>)
      {
         // If the type is trivially copyable, we can write it out in one block.
         out.write(reinterpret_cast<const char*>(vector.data()), vector.size() * sizeof(T));
      }
      else
      {
         for (const T& val : vector)
         {
            SerializeBasicType<T>(val, out);
         }
      }
   }

   template <SerializableType T>
   T DeserializeBasicType(std::istream& in)
   {
      T value;
      in.read(reinterpret_cast<char*>(&value), sizeof(T));
      return value;
   }

   template <SerializableType T>
   std::vector<T> DeserializeVector(std::istream& in)
   {
      const std::int32_t size = DeserializeBasicType<std::int32_t>(in);
      std::vector<T> vector;
      vector.reserve(size);

      if constexpr (std::is_trivially_copyable_v<T> && !std::is_same_v<T, std::string>)
      {
         // If the type is trivially copyable, we can read it in one block.
         vector.resize(size);
         in.read(reinterpret_cast<char*>(vector.data()), size * sizeof(T));
      }
      else
      {
         for (size_t i = 0; i < size; ++i)
         {
            vector.emplace_back(DeserializeBasicType<T>(in));
         }
      }
      return vector;
   }
}
