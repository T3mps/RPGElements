#pragma once

#include <optional>
#include <string>
#include <vector>

#include "../Core/Common.h"
#include "../DIVE/DIVE.h"
#include "ItemTemplate.h"

struct Item
{
   ItemTemplate itemTemplate;
   uuid uuid = generate_uuid();
   DIVE::TagCompound metadata;

   Item(const ItemTemplate& templateRef = ItemTemplate::DEFAULT) : itemTemplate(templateRef) {}

   bool operator==(const Item& other) const { return itemTemplate.GetID() == other.itemTemplate.GetID() && uuid == other.uuid && metadata == other.metadata; }

   bool CanStackWith(const Item& other) const { return itemTemplate.GetID() == other.itemTemplate.GetID() && metadata == other.metadata; }
};

class ItemStack
{
public:
   enum class AttributeFlags : uint8_t
   {
#define BIT(x) (1 << x)
      Unstackable = BIT(0)
   };
#undef BIT

   using iterator = std::vector<Item>::iterator;
   using const_iterator = std::vector<Item>::const_iterator;
   using reverse_iterator = std::reverse_iterator<iterator>;
   using const_reverse_iterator = std::reverse_iterator<const_iterator>;
   
   ItemStack();
   ItemStack(const Item& item);

   Item& operator[](size_t index) { return m_items[index]; }
   const Item& operator[](size_t index) const { return m_items[index]; }

   Item& Back();
   const Item& Back() const;

   bool Push(const Item& item);
   std::optional<Item> Pop();

   bool Contains(const Item& item) const;

   iterator Erase(const Item& item);
   iterator Erase(iterator& iter);
   
   size_t Merge(ItemStack& other);
   const std::vector<ItemStack> Split(size_t count = 2);

   void SetAttribute(const AttributeFlags& flag, bool value);
   bool CheckAttribute(const AttributeFlags& flag) const;

   void Clear() { m_items.clear(); }

   const uuid& GetUUID() const { return m_uuid; }
   const std::vector<Item>& GetItems() const { return m_items; }

   inline size_t Size() const { return m_items.size(); }
   inline bool Full() const { return m_items.size() == m_capacity; }
   inline bool Empty() const { return m_items.empty(); }

   iterator begin() { return m_items.begin(); }
   iterator end() { return m_items.end(); }
   const_iterator begin() const { return m_items.begin(); }
   const_iterator end() const { return m_items.end(); }

   reverse_iterator rbegin() { return m_items.rbegin(); }
   reverse_iterator rend() { return m_items.rend(); }
   const_reverse_iterator rbegin() const { return m_items.rbegin(); }
   const_reverse_iterator rend() const { return m_items.rend(); }

   const_iterator cbegin() const { return m_items.cbegin(); }
   const_iterator cend() const { return m_items.cend(); }
   const_reverse_iterator crbegin() const { return m_items.crbegin(); }
   const_reverse_iterator crend() const { return m_items.crend(); }

private:
   uint8_t m_attributes;
   ItemID m_templateID;
   uuid m_uuid = generate_uuid();
   size_t m_capacity;
   std::vector<Item> m_items;
};
