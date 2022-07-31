

#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


YouGotAnItem::YouGotAnItem(std::string item_name, std::string item_bitmap_identifier)
   : AllegroFlare::Elements::DialogBoxes::Base("YouGotAnItem")
   , item_name(item_name)
   , item_bitmap_identifier(item_bitmap_identifier)
{
}


YouGotAnItem::~YouGotAnItem()
{
}


std::string YouGotAnItem::get_item_name()
{
   return item_name;
}


std::string YouGotAnItem::get_item_bitmap_identifier()
{
   return item_bitmap_identifier;
}


void YouGotAnItem::show()
{
   set_created_at(al_get_time());
}
} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


