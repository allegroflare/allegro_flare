#pragma once


#include <AllegroFlare/InventoryDictionary.hpp>
#include <AllegroFlare/InventoryIndexItem.hpp>
#include <map>


namespace AllegroFlare
{
   class InventoryDictionary
   {
   private:
      std::map<int, AllegroFlare::InventoryIndexItem> dictionary;

   protected:


   public:
      InventoryDictionary(std::map<int, AllegroFlare::InventoryIndexItem> dictionary={});
      ~InventoryDictionary();

      void set_dictionary(std::map<int, AllegroFlare::InventoryIndexItem> dictionary);
      std::map<int, AllegroFlare::InventoryIndexItem> get_dictionary() const;
      int size();
      bool exists(int id=0);
      AllegroFlare::InventoryIndexItem at(int id=0);
      static AllegroFlare::InventoryDictionary build_placeholder_inventory_dictionary();
   };
}



