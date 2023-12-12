#pragma once

#include <map>

#include "../DIVE/DIVETag.h"

using ItemID = uint32_t;

class ItemTemplate
{
public:
   struct ParseData
   {
      std::string name;
      size_t stackCapacity;
      std::map<std::string, std::string> data;
   };

   static const ItemTemplate DEFAULT;
   static constexpr size_t DEFAULT_CAPACITY = 64;

   ItemTemplate();
   ItemTemplate(ParseData parseData);
   ~ItemTemplate() = default;

   DIVE::TagValue& operator[](const std::string& key);
   const DIVE::TagValue& operator[](const std::string& key) const;

   ItemID GetID() const { return m_id; }
   size_t GetStackCapacity() const { return m_stackCapacity; }

   const std::string& GetName() const { return m_name; }

private:
   static ParseData ParseItemTemplateJSON(const std::string& json);

   static ItemID s_currentID;
   ItemID m_id;
   std::string m_name;
   size_t m_stackCapacity;
   DIVE::TagCompound m_attributes;
};
