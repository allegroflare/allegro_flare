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
      void add_items(std::vector<int> items_to_add);
      bool has_item(int item_type);
      int count_item(int item_type);
      int get_item_count(int item_type); // deprecated, use "count_item"
      bool remove_item(int item_type);

      std::vector<int> &get_items_ref();
      bool is_empty();

      std::string get_str();
   };
}


