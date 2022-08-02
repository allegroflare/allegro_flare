#pragma once


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
      std::map<int, AllegroFlare::InventoryIndexItem> get_index();
   };
}



