

#include <AllegroFlare/InventoryDictionary.hpp>




namespace AllegroFlare
{


InventoryDictionary::InventoryDictionary(std::map<int, AllegroFlare::InventoryIndexItem> index)
   : index(index)
{
}


InventoryDictionary::~InventoryDictionary()
{
}


void InventoryDictionary::set_index(std::map<int, AllegroFlare::InventoryIndexItem> index)
{
   this->index = index;
}


std::map<int, AllegroFlare::InventoryIndexItem> InventoryDictionary::get_index() const
{
   return index;
}


int InventoryDictionary::size()
{
   return index.size();
}

bool InventoryDictionary::exists(int id)
{
   return (index.count(id) > 0);
}

AllegroFlare::InventoryIndexItem InventoryDictionary::at(int id)
{
   if (!exists(id)) return AllegroFlare::InventoryIndexItem("", "", "");
   return index.at(id);
}

AllegroFlare::InventoryDictionary InventoryDictionary::build_placeholder_inventory_dictionary()
{
   return AllegroFlare::InventoryDictionary({
         { 1, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
         { 2, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
         { 3, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
         { 4, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
      });
}


} // namespace AllegroFlare


