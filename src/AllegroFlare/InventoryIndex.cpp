

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


std::map<int, AllegroFlare::InventoryIndexItem> InventoryIndex::get_index() const
{
   return index;
}


int InventoryIndex::size()
{
   return index.size();
}

bool InventoryIndex::exists(int id)
{
   return (index.count(id) > 0);
}

AllegroFlare::InventoryIndexItem InventoryIndex::at(int id)
{
   if (!exists(id)) return AllegroFlare::InventoryIndexItem("", "", "");
   return index.at(id);
}

AllegroFlare::InventoryIndex InventoryIndex::build_placeholder_inventory_index()
{
   return AllegroFlare::InventoryIndex({
         { 1, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
         { 2, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
         { 3, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
         { 4, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
         { 5, { "Robot Helmet", "robot_helmet-01.png", "Features integrated sensors and communication modules." } },
      });
}


} // namespace AllegroFlare


