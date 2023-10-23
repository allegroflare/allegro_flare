

#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>




namespace AllegroFlare
{
namespace DialogSystemDrivers
{


BasicCharacterDialogDriver::BasicCharacterDialogDriver(AllegroFlare::DialogSystem::CharacterRoster* character_roster)
   : AllegroFlare::DialogSystemDrivers::Base(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE)
   , character_roster(character_roster)
   , active_character_staging_layout(nullptr)
   , dialog_roll()
{
}


BasicCharacterDialogDriver::~BasicCharacterDialogDriver()
{
}


void BasicCharacterDialogDriver::set_character_roster(AllegroFlare::DialogSystem::CharacterRoster* character_roster)
{
   this->character_roster = character_roster;
}


void BasicCharacterDialogDriver::set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll)
{
   this->dialog_roll = dialog_roll;
}


AllegroFlare::DialogSystem::CharacterRoster* BasicCharacterDialogDriver::get_character_roster() const
{
   return character_roster;
}


AllegroFlare::Elements::DialogRoll BasicCharacterDialogDriver::get_dialog_roll() const
{
   return dialog_roll;
}


AllegroFlare::Elements::DialogRoll &BasicCharacterDialogDriver::get_dialog_roll_ref()
{
   return dialog_roll;
}




} // namespace DialogSystemDrivers
} // namespace AllegroFlare


