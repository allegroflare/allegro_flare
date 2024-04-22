

#include <AllegroFlare/DialogTree/Nodes/YouGotAnItemDialog.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


YouGotAnItemDialog::YouGotAnItemDialog(std::string item_title, std::string item_bitmap_identifier)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog::TYPE)
   , item_title(item_title)
   , item_bitmap_identifier(item_bitmap_identifier)
{
}


YouGotAnItemDialog::~YouGotAnItemDialog()
{
}


void YouGotAnItemDialog::set_item_title(std::string item_title)
{
   this->item_title = item_title;
}


void YouGotAnItemDialog::set_item_bitmap_identifier(std::string item_bitmap_identifier)
{
   this->item_bitmap_identifier = item_bitmap_identifier;
}


std::string YouGotAnItemDialog::get_item_title() const
{
   return item_title;
}


std::string YouGotAnItemDialog::get_item_bitmap_identifier() const
{
   return item_bitmap_identifier;
}




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


