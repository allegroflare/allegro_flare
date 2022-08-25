#pragma once


#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/InventoryIndexItem.hpp>
#include <map>


namespace AllegroFlare
{
   class InventoryIndex
   {
   private:
      std::map<int, AllegroFlare::InventoryIndexItem> index;

   public:
      InventoryIndex(std::map<int, AllegroFlare::InventoryIndexItem> index={});
      ~InventoryIndex();

      void set_index(std::map<int, AllegroFlare::InventoryIndexItem> index);
      std::map<int, AllegroFlare::InventoryIndexItem> get_index() const;
      int size();
      bool exists(int id=0);
      AllegroFlare::InventoryIndexItem at(int id=0);
      static AllegroFlare::InventoryIndex build_placeholder_inventory_index();
   };
}



