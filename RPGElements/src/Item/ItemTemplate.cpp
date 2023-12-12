#include <sstream>

#include "ItemTemplate.h"

ItemID ItemTemplate::s_currentID = 0;
const ItemTemplate ItemTemplate::DEFAULT;

ItemTemplate::ItemTemplate() : m_id(++s_currentID), m_name("Default"), m_stackCapacity(DEFAULT_CAPACITY)
{}

ItemTemplate::ItemTemplate(ParseData parseData) : m_id(++s_currentID), m_name(parseData.name), m_stackCapacity(parseData.stackCapacity)
{
   for (const auto& [key, value] : parseData.data)
   {
      (*this)[key] = value;
   }
}

DIVE::TagValue& ItemTemplate::operator[](const std::string& key)
{
   auto& ptr = m_attributes[key];
   if (!ptr)
   {
      ptr = std::make_unique<DIVE::Tag>();
      ptr->name = key;
   }
   return ptr->value;
}

const DIVE::TagValue& ItemTemplate::operator[](const std::string& key) const
{
   auto it = m_attributes.find(key);
   if (it == m_attributes.end() || !it->second)
      throw std::out_of_range("Attribute not found");
   return it->second->value;
}

ItemTemplate::ParseData ItemTemplate::ParseItemTemplateJSON(const std::string& json)
{
   ParseData parseData;
   std::istringstream stream(json);
   std::string token;

   while (getline(stream, token, ','))
   {
      auto colonPos = token.find(':');
      if (colonPos != std::string::npos)
      {
         std::string key = token.substr(0, colonPos);
         std::string value = token.substr(colonPos + 1);

         key.erase(remove_if(key.begin(), key.end(),
            [](char c) { return c == '{' || c == '}' || c == '\"' || c == ' '; }), key.end());
         value.erase(remove_if(value.begin(), value.end(),
            [](char c) { return c == '{' || c == '}' || c == '\"' || c == ' '; }), value.end());

         static std::string nameString = "name";
         static std::string stackCapacityString = "stackCapacity";
         if (key == nameString)
            parseData.name = value;
         else if (key == stackCapacityString)
            parseData.stackCapacity = std::stoul(stackCapacityString);
         else
            parseData.data[key] = value;
      }
   }

   return parseData;
}
