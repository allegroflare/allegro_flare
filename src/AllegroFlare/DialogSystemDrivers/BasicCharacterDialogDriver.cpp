

#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystemDrivers
{


BasicCharacterDialogDriver::BasicCharacterDialogDriver()
   : AllegroFlare::DialogSystemDrivers::Base(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE)
   , dialog_roll()
   , initialized(false)
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


void BasicCharacterDialogDriver::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::initialize: error: guard \"(!initialized)\" not met");
   }
   active_character_staging_layout = new AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered();
   initialized = true;
   return;
}

void BasicCharacterDialogDriver::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::destroy: error: guard \"initialized\" not met");
   }
   delete active_character_staging_layout;
}

void BasicCharacterDialogDriver::clear_character_staging_layout()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::clear_character_staging_layout]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::clear_character_staging_layout: error: guard \"initialized\" not met");
   }
   if (active_character_staging_layout->is_type(
            AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered::TYPE
         ))
   {
      AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered *as =
         static_cast<AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered*>(
            active_character_staging_layout
         );
      as->clear_speaking_character_bitmap();
   }
   else
   {
      throw std::runtime_error(
         "DialogSystem::set_speaking_character: error: Unable to perform action because "
            "\"active_character_staging_layout\" is of type \"" + active_character_staging_layout->get_type() + "\" "
            "and a condition is not provided to handle this type."
      );
   }
   return;
}

bool BasicCharacterDialogDriver::activate_dialog_node_by_name_func(AllegroFlare::DialogSystem::DialogSystem* dialog_system, std::string active_dialog_node_name, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node, void* user_data)
{
   if (!(dialog_system))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::activate_dialog_node_by_name_func]: error: guard \"dialog_system\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::activate_dialog_node_by_name_func: error: guard \"dialog_system\" not met");
   }
   if (!(active_dialog_node))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::activate_dialog_node_by_name_func]: error: guard \"active_dialog_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::activate_dialog_node_by_name_func: error: guard \"active_dialog_node\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::activate_dialog_node_by_name_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::activate_dialog_node_by_name_func: error: guard \"user_data\" not met");
   }
   return true;
}

void BasicCharacterDialogDriver::append_to_dialog_roll(std::string speaking_character, std::string dialog)
{
   dialog_roll.append_log(speaking_character, dialog);
   return;
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


