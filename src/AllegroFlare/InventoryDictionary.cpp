

#include <AllegroFlare/InventoryDictionary.hpp>

#include <AllegroFlare/InventoryDictionaryItems/ClassicItem.hpp>


namespace AllegroFlare
{


InventoryDictionary::InventoryDictionary(std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> dictionary)
   : dictionary(dictionary)
{
}


InventoryDictionary::~InventoryDictionary()
{
}


void InventoryDictionary::set_dictionary(std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> dictionary)
{
   this->dictionary = dictionary;
}


std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> InventoryDictionary::get_dictionary() const
{
   return dictionary;
}


std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> &InventoryDictionary::get_dictionary_ref()
{
   return dictionary;
}


int InventoryDictionary::size()
{
   return dictionary.size();
}

bool InventoryDictionary::exists(int id)
{
   return (dictionary.count(id) > 0);
}

AllegroFlare::InventoryDictionaryItems::Base* InventoryDictionary::at(int id)
{
   if (!exists(id)) return nullptr;
   return dictionary.at(id);
}

AllegroFlare::InventoryDictionary InventoryDictionary::build_placeholder_inventory_dictionary()
{
   using AllegroFlare::InventoryDictionaryItems::ClassicItem;

   return AllegroFlare::InventoryDictionary({
         { 1, new ClassicItem
            (
               "Walkie-Talkie",
               "walkie-02.png",
               "A small portable radio to communicate with someone far away."
            )
         },
         { 2, new ClassicItem
            (
               "Blaster",
               "blaster-02.png",
               "Standard issue weaponry."
            )
         },
         { 3, new ClassicItem
            (
               "Train",
               "toy-train-02.png",
               "It sure has a lot of detail."
            )
         },
         { 4, new ClassicItem
            (
               "Metal Pipe",
               "metal-pipe-01.png",
               "Made of galvanized metal, this pipe is very sturdy."
            )
         },
      });
}


} // namespace AllegroFlare


