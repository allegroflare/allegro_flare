

#include <AllegroFlare/InventoryIndexItem.hpp>



namespace AllegroFlare
{


InventoryIndexItem::InventoryIndexItem(std::string title, std::string bitmap_filename, std::string description)
   : title(title)
   , bitmap_filename(bitmap_filename)
   , description(description)
{
}


InventoryIndexItem::~InventoryIndexItem()
{
}


void InventoryIndexItem::set_title(std::string title)
{
   this->title = title;
}


void InventoryIndexItem::set_bitmap_filename(std::string bitmap_filename)
{
   this->bitmap_filename = bitmap_filename;
}


void InventoryIndexItem::set_description(std::string description)
{
   this->description = description;
}


std::string InventoryIndexItem::get_title()
{
   return title;
}


std::string InventoryIndexItem::get_bitmap_filename()
{
   return bitmap_filename;
}


std::string InventoryIndexItem::get_description()
{
   return description;
}


} // namespace AllegroFlare


