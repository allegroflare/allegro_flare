#pragma once


#include <AllegroFlare/InventoryDictionary.hpp>
#include <AllegroFlare/InventoryIndexItem.hpp>
#include <map>


namespace AllegroFlare
{
   class InventoryDictionary
   {
   private:
      std::map<int, AllegroFlare::InventoryIndexItem> index;

   protected:


   public:
      InventoryDictionary(std::map<int, AllegroFlare::InventoryIndexItem> index={});
      ~InventoryDictionary();

      void set_index(std::map<int, AllegroFlare::InventoryIndexItem> index);
      std::map<int, AllegroFlare::InventoryIndexItem> get_index() const;
      int size();
      bool exists(int id=0);
      AllegroFlare::InventoryIndexItem at(int id=0);
      static AllegroFlare::InventoryDictionary build_placeholder_inventory_dictionary();
   };
}



