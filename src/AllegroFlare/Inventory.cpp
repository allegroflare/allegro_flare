

#include <AllegroFlare/Inventory.hpp>

#include <sstream>
#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
   Inventory::Inventory()
      : items()
   {}


   int Inventory::size()
   {
      return items.size();
   }


   void Inventory::add_item(int item_type)
   {
      items.push_back(item_type);
   }


   void Inventory::add_items(std::vector<int> items_to_add)
   {
      items.insert(items.end(), items_to_add.begin(), items_to_add.end());
   }


   bool Inventory::has_item(int item_type)
   {
      for (auto &item : items) if (item == item_type) return true;
      return false;
   }


   bool Inventory::remove_item(int item_type)
   {
      for (unsigned i=0; i<items.size(); i++)
         if (items[i] == item_type)
         {
            items.erase(items.begin() + i);
            return true;
         }
      return false;
   }


   std::vector<int> &Inventory::get_items_ref()
   {
      return items;
   }


   bool Inventory::is_empty()
   {
      return items.empty();
   }


   int Inventory::count_item(int item_type)
   {
      int count = 0;
      for (auto &item : items) if (item == item_type) count++;
      return count;
   }


   int Inventory::get_item_count(int item_type)
   {
      AllegroFlare::Logger::warn_from_once(
         "AllegroFlare::Inventory::get_item_count"
         "This method is deprecated, use \"count_item\" instead."
      );
      return count_item(item_type);
   }


   std::string Inventory::get_str()
   {
      std::stringstream result;
      for (auto &i : items)
      {
         result << i << " ";
      }
      return result.str();
   }
}


