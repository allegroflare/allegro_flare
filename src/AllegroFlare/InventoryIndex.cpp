

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


bool InventoryIndex::exists(int id)
{
   return index.find(id) != index.end();
}

AllegroFlare::InventoryIndexItem InventoryIndex::at(int id)
{
   if (!exists()) return AllegroFlare::InventoryIndexItem("", "", "");
   return index.at(id);
}

AllegroFlare::InventoryIndex InventoryIndex::create_placeholder_inventory_index()
{
   return AllegroFlare::InventoryIndex({
         { 1, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
         { 2, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
         { 3, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
         { 4, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
      });
}
} // namespace AllegroFlare


