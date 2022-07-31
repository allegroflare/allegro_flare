

#include <AllegroFlare/Prototypes/FixedRoom2D/InteractionEventData.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


InteractionEventData::InteractionEventData(std::string item_interacted_with, float cursor_x, float cursor_y)
   : AllegroFlare::GameEventDatas::Base("InteractionEventData")
   , item_interacted_with(item_interacted_with)
   , cursor_x(cursor_x)
   , cursor_y(cursor_y)
{
}


InteractionEventData::~InteractionEventData()
{
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


