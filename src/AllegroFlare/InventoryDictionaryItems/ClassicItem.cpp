

#include <AllegroFlare/InventoryDictionaryItems/ClassicItem.hpp>




namespace AllegroFlare
{
namespace InventoryDictionaryItems
{


ClassicItem::ClassicItem(std::string title, std::string bitmap_filename, std::string description)
   : AllegroFlare::InventoryDictionaryItems::Base(AllegroFlare::InventoryDictionaryItems::ClassicItem::TYPE)
   , title(title)
   , bitmap_filename(bitmap_filename)
   , description(description)
{
}


ClassicItem::~ClassicItem()
{
}


void ClassicItem::set_title(std::string title)
{
   this->title = title;
}


void ClassicItem::set_bitmap_filename(std::string bitmap_filename)
{
   this->bitmap_filename = bitmap_filename;
}


void ClassicItem::set_description(std::string description)
{
   this->description = description;
}


std::string ClassicItem::get_title() const
{
   return title;
}


std::string ClassicItem::get_bitmap_filename() const
{
   return bitmap_filename;
}


std::string ClassicItem::get_description() const
{
   return description;
}


std::tuple<std::string, std::string, std::string> ClassicItem::to_tuple()
{
   return std::tuple<std::string, std::string, std::string>(title, bitmap_filename, description);
}


} // namespace InventoryDictionaryItems
} // namespace AllegroFlare


