

#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CreateYouGotAnItemDialog.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace DialogEventDatas
{


CreateYouGotAnItemDialog::CreateYouGotAnItemDialog(std::string item_name, std::string item_bitmap_identifier)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotAnItemDialog::TYPE)
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
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


