#pragma once


#include <AllegroFlare/InventoryDictionary.hpp>
#include <AllegroFlare/InventoryDictionaryItems/Base.hpp>
#include <map>


namespace AllegroFlare
{
   class InventoryDictionary
   {
   private:
      std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> dictionary;

   protected:


   public:
      InventoryDictionary(std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> dictionary={});
      ~InventoryDictionary();

      void set_dictionary(std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> dictionary);
      std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> get_dictionary() const;
      int size();
      bool exists(int id=0);
      AllegroFlare::InventoryDictionaryItems::Base* at(int id=0);
      static AllegroFlare::InventoryDictionary build_placeholder_inventory_dictionary();
   };
}



