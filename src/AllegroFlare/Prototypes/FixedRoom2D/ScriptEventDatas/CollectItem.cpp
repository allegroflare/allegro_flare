

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectItem.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace ScriptEventDatas
{


CollectItem::CollectItem(std::string item_dictionary_name_to_collect)
   : AllegroFlare::GameEventDatas::Base("CollectItem")
   , item_dictionary_name_to_collect(item_dictionary_name_to_collect)
{
}


CollectItem::~CollectItem()
{
}


void CollectItem::set_item_dictionary_name_to_collect(std::string item_dictionary_name_to_collect)
{
   this->item_dictionary_name_to_collect = item_dictionary_name_to_collect;
}


std::string CollectItem::get_item_dictionary_name_to_collect() const
{
   return item_dictionary_name_to_collect;
}


} // namespace ScriptEventDatas
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


