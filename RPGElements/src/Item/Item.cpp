#include "Item.h"

ItemStack::ItemStack() : m_attributes(0), m_templateID(ItemTemplate::DEFAULT.GetID()), m_capacity(ItemTemplate::DEFAULT.GetStackCapacity())
{
   SetAttribute(AttributeFlags::Unstackable, m_capacity == 1);
   m_items.reserve(m_capacity);
}

ItemStack::ItemStack(const Item& item) : m_attributes(0), m_templateID(item.itemTemplate.GetID()), m_capacity(item.itemTemplate.GetStackCapacity())
{
   m_items.reserve(m_capacity);
   m_items.push_back(item);
}

Item& ItemStack::Back()
{
   if (Empty())
   {
      static Item empty;
      return empty;
   }

   return m_items.back();
}

const Item& ItemStack::Back() const
{
   if (Empty())
   {
      static const Item empty;
      return empty;
   }

   return m_items.back();
}

bool ItemStack::Push(const Item& item)
{
   if (Full() || item.itemTemplate.GetID() != m_templateID)
      return false;

   m_items.push_back(item);
   return true;
}

std::optional<Item> ItemStack::Pop()
{
   if (Empty())
      return std::nullopt;

   Item item = m_items.back();
   m_items.pop_back();
   return item;
}

bool ItemStack::Contains(const Item& item) const
{
   const_iterator iter = std::find(cbegin(), cend(), item);
   return iter != cend();
}

ItemStack::iterator ItemStack::Erase(const Item& item)
{
   if (Empty())
      return end();

   auto it = std::find(begin(), end(), item);
   if (it != end())
      it = m_items.erase(it);
   
   return it;
}

ItemStack::iterator ItemStack::Erase(iterator& iter)
{
   if (iter >= begin() && iter < end())
      return iter = m_items.erase(iter);
   return end();
}

size_t ItemStack::Merge(ItemStack& other)
{
   if (other.m_templateID != m_templateID)
      return 0;

   size_t mergeCount = 0;
   while (!other.Empty() && m_items.size() < m_capacity)
   {
      Item& item = other.m_items.back();
      if (!m_items.empty() && !item.CanStackWith(m_items.back()))
         break;

      m_items.push_back(std::move(item));
      other.m_items.pop_back();
      ++mergeCount;
   }

   if (other.Empty())
      other.m_uuid = INVALID_UUID;

   return mergeCount;
}

const std::vector<ItemStack> ItemStack::Split(size_t count /* = 2 */)
{
   const size_t size = m_items.size();
   std::vector<ItemStack> result;

   if (m_items.empty() || count < 2 || count >= size)
      return result;

   const size_t countMask = count - 1;
   result.reserve(countMask);

   const size_t proportions = size / count;
   size_t remainder = size % count;

   for (size_t i = 0; i < countMask; ++i)
   {
      ItemStack stack;
      const size_t currentStackSize = proportions + (remainder > 0 ? 1 : 0);
      
      for (size_t j = 0; j < currentStackSize; ++j)
      {
         stack.Push(std::move(m_items.back()));
         m_items.pop_back();
      }

      if (remainder > 0)
         --remainder;

      result.push_back(std::move(stack));
   }

   return result;
}

void ItemStack::SetAttribute(const AttributeFlags& flag, bool value)
{
   switch (value)
   {
      case true: m_attributes |= static_cast<uint8_t>(flag); break;
      case false: m_attributes &= ~static_cast<uint8_t>(flag); break;
   }
}

bool ItemStack::CheckAttribute(const AttributeFlags& flag) const
{
   return (m_attributes & static_cast<uint8_t>(flag)) != 0;
}