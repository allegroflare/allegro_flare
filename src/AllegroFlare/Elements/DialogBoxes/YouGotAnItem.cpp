

#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>

#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


YouGotAnItem::YouGotAnItem(std::string item_name, std::string item_bitmap_identifier)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::YouGotAnItem::TYPE)
   , item_name(item_name)
   , item_bitmap_identifier(item_bitmap_identifier)
{
}


YouGotAnItem::~YouGotAnItem()
{
}


std::string YouGotAnItem::get_item_name() const
{
   return item_name;
}


std::string YouGotAnItem::get_item_bitmap_identifier() const
{
   return item_bitmap_identifier;
}


void YouGotAnItem::start()
{
   // TODO: Implement this, considering its relationship to "created_at"
   return;
}

void YouGotAnItem::update()
{
   if (get_finished()) return;
   if (infer_age() > 1.0) // NOTE: giving it one second before can be dismissed
   {
      set_finished(true);
   }
   return;
}

void YouGotAnItem::advance()
{
   // TODO: rather than have this "finish" it should advance the animation to the end.  Then, if the dialog
   // has "advance()" called a second time, it will set finished to true.
   if (get_finished()) return;
   set_finished(true);
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


