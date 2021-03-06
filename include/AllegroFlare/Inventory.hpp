#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   class Inventory
   {
   public:
      std::vector<int> items;

   public:
      Inventory();

      int size();

      void add_item(int item_type);
      bool has_item(int item_type);
      int get_item_count(int item_type);
      bool remove_item(int item_type);

      std::vector<int> &get_items_ref();

      std::string get_str();
   };
}


