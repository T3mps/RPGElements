#include <cstdint>

#include "DIVESerializer.h"

void DIVE::SerializeString(const std::string& value, std::ostream& out)
{
   SerializeBasicType<std::int32_t>(static_cast<std::int32_t>(value.size()), out);
   out.write(value.c_str(), static_cast<std::streamsize>(value.size()));
}

void DIVE::SerializeTagCompound(const TagCompound& compound, std::ostream& out)
{
   SerializeBasicType<std::int32_t>(static_cast<std::int32_t>(compound.size()), out);
   for (const auto& [key, tagPtr] : compound)
   {
      if (tagPtr)
      {
         SerializeString(key, out);
         SerializeTag(*tagPtr, out);
      }
   }
}

void DIVE::Serialize(const TagValue& value, std::ostream& out)
{
   SerializeBasicType<std::int32_t>(static_cast<std::int32_t>(value.index()), out);
   std::visit(
      overloaded
      {
         [](std::monostate) { /* Nothing to do for std::monostate */ },
         [&out](std::int32_t arg) { SerializeBasicType<std::int32_t>(arg, out); },
         [&out](std::float_t arg) { SerializeBasicType<std::float_t>(arg, out); },
         [&out](const std::string& arg) { SerializeString(arg, out); },
         [&out](const ByteArray& arg) { SerializeVector<int8_t>(arg, out); },
         [&out](const ShortArray& arg) { SerializeVector<int16_t>(arg, out); },
         [&out](const IntArray& arg) { SerializeVector<std::int32_t>(arg, out); },
         [&out](const LongArray& arg) { SerializeVector<int64_t>(arg, out); },
         [&out](const TagList& arg)
         {
             SerializeBasicType<std::int32_t>(static_cast<std::int32_t>(arg.size()), out);
             for (const auto& tagPtr : arg)
             {
                if (tagPtr)
                   SerializeTag(*tagPtr, out);
             }
         },
         [&out](const TagCompound& arg) { SerializeTagCompound(arg, out); }
      }, 
      value);
}

void DIVE::SerializeTag(const Tag& tag, std::ostream& out)
{
   SerializeString(tag.name, out);
   Serialize(tag.value, out);
}

std::string DIVE::DeserializeString(std::istream& in)
{
   std::int32_t length = DeserializeBasicType<std::int32_t>(in);
   std::string value(length, '\0');
   in.read(&value[0], length);
   return value;
}

DIVE::TagCompound DIVE::DeserializeTagCompound(std::istream& in)
{
   std::int32_t size = DeserializeBasicType<std::int32_t>(in);
   TagCompound compound;
   compound.reserve(size);

   for (size_t i = 0; i < size; ++i)
   {
      std::string key = DeserializeString(in);
      auto tag = std::make_unique<Tag>(DeserializeTag(in));
      compound.emplace(std::move(key), std::move(tag));
   }
   return compound;
}

DIVE::TagValue DIVE::Deserialize(std::istream& in)
{
   std::int32_t typeID = DeserializeBasicType<std::int32_t>(in);
   switch (typeID)
   {
      case 1: return DeserializeBasicType<std::int32_t>(in);
      case 2: return DeserializeBasicType<std::float_t>(in);
      case 3: return DeserializeString(in);
      case 4: return DeserializeVector<std::int8_t>(in);
      case 5: return DeserializeVector<std::int16_t>(in);
      case 6: return DeserializeVector<std::int32_t>(in);
      case 7: return DeserializeVector<std::int64_t>(in);
      case 8:
      {
         std::int32_t size = DeserializeBasicType<std::int32_t>(in);
         TagList list;
         list.reserve(size);
         for (size_t i = 0; i < size; ++i)
         {
            list.emplace_back(std::make_unique<Tag>(DeserializeTag(in)));
         }
         return list;
      }
      case 9: return DeserializeTagCompound(in);
      default: return std::monostate{};
   }
}

DIVE::Tag DIVE::DeserializeTag(std::istream& in)
{
   Tag tag;
   tag.name = DeserializeString(in);
   tag.value = Deserialize(in);
   return tag;
}