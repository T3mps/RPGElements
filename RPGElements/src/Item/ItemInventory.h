#pragma once

#include <vector>
#include <optional>

#include "Item.h"

class Inventory
{
public:
   using iterator = std::vector<ItemStack>::iterator;
   using const_iterator = std::vector<ItemStack>::const_iterator;
   using reverse_iterator = std::vector<ItemStack>::reverse_iterator;
   using const_reverse_iterator = std::vector<ItemStack>::const_reverse_iterator;

   Inventory(size_t capacity);
   ~Inventory() = default;

   ItemStack& operator[](size_t index) { return m_stacks[index]; }
   const ItemStack& operator[](size_t index) const { return m_stacks[index]; }

   bool AddStack(const ItemStack& stack);
   std::optional<ItemStack> RemoveStack(size_t index);
   ItemStack* GetStack(size_t index);
   const ItemStack* GetStack(size_t index) const;

   size_t GetCapacity() const { return m_capacity; }
   size_t GetStackCount() const { return m_stacks.size(); }

   iterator begin() { return m_stacks.begin(); }
   iterator end() { return m_stacks.end(); }
   const_iterator begin() const { return m_stacks.begin(); }
   const_iterator end() const { return m_stacks.end(); }

   reverse_iterator rbegin() { return m_stacks.rbegin(); }
   reverse_iterator rend() { return m_stacks.rend(); }
   const_reverse_iterator rbegin() const { return m_stacks.rbegin(); }
   const_reverse_iterator rend() const { return m_stacks.rend(); }

   const_iterator cbegin() const { return m_stacks.cbegin(); }
   const_iterator cend() const { return m_stacks.cend(); }
   const_reverse_iterator crbegin() const { return m_stacks.crbegin(); }
   const_reverse_iterator crend() const { return m_stacks.crend(); }

private:
   std::vector<ItemStack> m_stacks;
   size_t m_size;
   size_t m_capacity;
};
