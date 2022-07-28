

#include <AllegroFlare/Prototypes/FixedRoom2D/CollectItemEventData.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


CollectItemEventData::CollectItemEventData(std::string item_dictionary_name_to_collect)
   : AllegroFlare::GameEventDatas::Base("CollectItemEventData")
   , item_dictionary_name_to_collect(item_dictionary_name_to_collect)
{
}


CollectItemEventData::~CollectItemEventData()
{
}


void CollectItemEventData::set_item_dictionary_name_to_collect(std::string item_dictionary_name_to_collect)
{
   this->item_dictionary_name_to_collect = item_dictionary_name_to_collect;
}


std::string CollectItemEventData::get_item_dictionary_name_to_collect()
{
   return item_dictionary_name_to_collect;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


