

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectEvidence.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace ScriptEventDatas
{


CollectEvidence::CollectEvidence(std::string item_dictionary_name_to_collect)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectEvidence::TYPE)
   , item_dictionary_name_to_collect(item_dictionary_name_to_collect)
{
}


CollectEvidence::~CollectEvidence()
{
}


void CollectEvidence::set_item_dictionary_name_to_collect(std::string item_dictionary_name_to_collect)
{
   this->item_dictionary_name_to_collect = item_dictionary_name_to_collect;
}


std::string CollectEvidence::get_item_dictionary_name_to_collect() const
{
   return item_dictionary_name_to_collect;
}




} // namespace ScriptEventDatas
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


