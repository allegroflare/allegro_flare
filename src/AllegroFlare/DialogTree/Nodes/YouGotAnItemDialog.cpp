

#include <AllegroFlare/DialogTree/Nodes/YouGotAnItemDialog.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


YouGotAnItemDialog::YouGotAnItemDialog(std::string item_name, std::string item_bitmap_identifier)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog::TYPE)
   , item_name(item_name)
   , item_bitmap_identifier(item_bitmap_identifier)
{
}


YouGotAnItemDialog::~YouGotAnItemDialog()
{
}


void YouGotAnItemDialog::set_item_name(std::string item_name)
{
   this->item_name = item_name;
}


void YouGotAnItemDialog::set_item_bitmap_identifier(std::string item_bitmap_identifier)
{
   this->item_bitmap_identifier = item_bitmap_identifier;
}


std::string YouGotAnItemDialog::get_item_name() const
{
   return item_name;
}


std::string YouGotAnItemDialog::get_item_bitmap_identifier() const
{
   return item_bitmap_identifier;
}




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


