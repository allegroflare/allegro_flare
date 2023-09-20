

#include <AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotAnItemDialog.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace DialogEventDatas
{


CreateYouGotAnItemDialog::CreateYouGotAnItemDialog(std::string item_name, std::string item_bitmap_identifier)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotAnItemDialog::TYPE)
   , item_name(item_name)
   , item_bitmap_identifier(item_bitmap_identifier)
{
}


CreateYouGotAnItemDialog::~CreateYouGotAnItemDialog()
{
}


std::string CreateYouGotAnItemDialog::get_item_name() const
{
   return item_name;
}


std::string CreateYouGotAnItemDialog::get_item_bitmap_identifier() const
{
   return item_bitmap_identifier;
}




} // namespace DialogEventDatas
} // namespace DialogSystem
} // namespace AllegroFlare


