

#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>




namespace AllegroFlare
{
namespace DialogSystemDrivers
{


BasicCharacterDialogDriver::BasicCharacterDialogDriver()
   : AllegroFlare::DialogSystemDrivers::Base(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE)
   , dialog_roll()
   , active_character_staging_layout(nullptr)
   , character_roster(nullptr)
{
}


BasicCharacterDialogDriver::~BasicCharacterDialogDriver()
{
}


void BasicCharacterDialogDriver::set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll)
{
   this->dialog_roll = dialog_roll;
}


AllegroFlare::Elements::DialogRoll BasicCharacterDialogDriver::get_dialog_roll() const
{
   return dialog_roll;
}


AllegroFlare::Elements::DialogRoll &BasicCharacterDialogDriver::get_dialog_roll_ref()
{
   return dialog_roll;
}


void BasicCharacterDialogDriver::append_to_dialog_roll(std::string speaking_character, std::string dialog)
{
   dialog_roll.append_log(speaking_character, dialog);
   return;
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


