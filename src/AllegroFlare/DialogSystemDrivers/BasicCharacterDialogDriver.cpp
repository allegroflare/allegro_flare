

#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>

#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystemDrivers
{


BasicCharacterDialogDriver::BasicCharacterDialogDriver(AllegroFlare::BitmapBin* bitmap_bin)
   : AllegroFlare::DialogSystemDrivers::Base(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE)
   , bitmap_bin(bitmap_bin)
   , dialog_roll()
   , initialized(false)
   , active_character_staging_layout(nullptr)
   , character_roster(nullptr)
   , scene_index(nullptr)
   , chapter_index(nullptr)
{
}


BasicCharacterDialogDriver::~BasicCharacterDialogDriver()
{
}


void BasicCharacterDialogDriver::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
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
   //active_character_staging_layout = new AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal();
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
   // TODO: consider where delete character_roster, scene_index should occour
   //if (active_character_staging_layout) delete active_character_staging_layout;
   return;
}

void BasicCharacterDialogDriver::on_switch_in()
{
   if (active_character_staging_layout) active_character_staging_layout->show();
   return;
}

void BasicCharacterDialogDriver::on_deactivate()
{
   if (active_character_staging_layout) active_character_staging_layout->hide();
   return;
}

void BasicCharacterDialogDriver::on_render()
{
   if (active_character_staging_layout) active_character_staging_layout->render();
   return;
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
   if (active_character_staging_layout) active_character_staging_layout->clear();
   return;
}

AllegroFlare::DialogSystem::Characters::Basic* BasicCharacterDialogDriver::find_character_by_identifier_as_Basic(std::string character_identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::find_character_by_identifier_as_Basic]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::find_character_by_identifier_as_Basic: error: guard \"initialized\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::find_character_by_identifier_as_Basic]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::find_character_by_identifier_as_Basic: error: guard \"bitmap_bin\" not met");
   }
   if (!(character_roster))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::find_character_by_identifier_as_Basic]: error: guard \"character_roster\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::find_character_by_identifier_as_Basic: error: guard \"character_roster\" not met");
   }
   // TOOD: Review guards

   if (!character_roster->character_exists_by_name(character_identifier))
   {
      // Throw for now
      std::stringstream available_character_names;
      available_character_names << "[ ";
      for (auto &character_identifier : character_roster->get_character_names())
      {
         available_character_names << "\"" << character_identifier << "\", ";
      }
      available_character_names << " ]";

      std::string error_message = "Roster is present, but character \"" + character_identifier + "\" "
                               "does not exist in roster. Available names are " + available_character_names.str();

      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver",
         error_message
      );
   }

   AllegroFlare::DialogSystem::Characters::Base *base =
      character_roster->find_character_by_name(character_identifier);

   if (base->is_type(AllegroFlare::DialogSystem::Characters::Basic::TYPE))
   {
      AllegroFlare::DialogSystem::Characters::Basic *as =
         static_cast<AllegroFlare::DialogSystem::Characters::Basic*>(base);

      return as;
   }
   else
   {
      throw std::runtime_error(
         "DialogSystemDrivers::BasicCharacterDialogDriver::lookup_speaking_character_as_Basic"
         "unknown handled character type"
      );
   }
   return nullptr;
}

void BasicCharacterDialogDriver::append_to_dialog_roll(std::string speaking_character, std::string dialog)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::append_to_dialog_roll]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::append_to_dialog_roll: error: guard \"initialized\" not met");
   }
   dialog_roll.append_log(speaking_character, dialog);
   return;
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


