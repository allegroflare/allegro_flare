

#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


YouGotAnItem::YouGotAnItem(int item_num, std::string item_name, std::string item_bitmap_identifier)
   : AllegroFlare::Elements::DialogBoxes::Base("YouGotAnItem")
   , item_num(item_num)
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


float YouGotAnItem::infer_age()
{
   return al_get_time() - get_created_at();
}

void YouGotAnItem::show()
{
   set_created_at(al_get_time());
}
} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


