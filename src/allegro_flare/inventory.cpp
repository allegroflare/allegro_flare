


#include <allegro_flare/inventory.h>

#include <sstream>



Inventory::Inventory()
   : items()
{}



void Inventory::add_item(int item_type)
{
   items.push_back(item_type);
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



int Inventory::get_item_count(int item_type)
{
   int count = 0;
   for (auto &item : items) if (item == item_type) count++;
   return count;
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



