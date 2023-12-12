#include "ItemInventory.h"

Inventory::Inventory(size_t capacity) :
   m_size(0),
   m_capacity(capacity)
{
   m_stacks.reserve(capacity);
}

bool Inventory::AddStack(const ItemStack& stack)
{
   if (m_size < m_capacity)
   {
      m_stacks.push_back(stack);
      ++m_size;
      return true;
   }
   return false;
}

std::optional<ItemStack> Inventory::RemoveStack(size_t index)
{
   if (index < m_size)
   {
      ItemStack stack = m_stacks[index];
      m_stacks.erase(m_stacks.begin() + index);
      --m_size;
      return stack;
   }
   return std::nullopt;
}

ItemStack* Inventory::GetStack(size_t index)
{
   if (index < m_size)
   {
      return &m_stacks[index];
   }
   return nullptr;
}

const ItemStack* Inventory::GetStack(size_t index) const
{
   if (index < m_size)
   {
      return &m_stacks[index];
   }
   return nullptr;
}
