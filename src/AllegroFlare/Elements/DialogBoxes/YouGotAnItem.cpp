

#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>



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


std::string YouGotAnItem::get_item_name() const
{
   return item_name;
}


std::string YouGotAnItem::get_item_bitmap_identifier() const
{
   return item_bitmap_identifier;
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


