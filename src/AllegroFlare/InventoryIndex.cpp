

#include <AllegroFlare/InventoryIndex.hpp>



namespace AllegroFlare
{


InventoryIndex::InventoryIndex(std::map<int, AllegroFlare::InventoryIndexItem> index)
   : index(index)
{
}


InventoryIndex::~InventoryIndex()
{
}


void InventoryIndex::set_index(std::map<int, AllegroFlare::InventoryIndexItem> index)
{
   this->index = index;
}


std::map<int, AllegroFlare::InventoryIndexItem> InventoryIndex::get_index()
{
   return index;
}


} // namespace AllegroFlare


