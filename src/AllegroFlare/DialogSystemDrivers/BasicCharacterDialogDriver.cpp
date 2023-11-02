

#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/MultiModal.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>
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
   , handle_activate_dialog_from_raw_script_line_func()
   , handle_activate_dialog_from_raw_script_line_func_user_data(nullptr)
   , handle_finished_dialog_from_raw_script_line_func()
   , handle_finished_dialog_from_raw_script_line_func_user_data(nullptr)
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


void BasicCharacterDialogDriver::set_handle_activate_dialog_from_raw_script_line_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> handle_activate_dialog_from_raw_script_line_func)
{
   this->handle_activate_dialog_from_raw_script_line_func = handle_activate_dialog_from_raw_script_line_func;
}


void BasicCharacterDialogDriver::set_handle_activate_dialog_from_raw_script_line_func_user_data(void* handle_activate_dialog_from_raw_script_line_func_user_data)
{
   this->handle_activate_dialog_from_raw_script_line_func_user_data = handle_activate_dialog_from_raw_script_line_func_user_data;
}


void BasicCharacterDialogDriver::set_handle_finished_dialog_from_raw_script_line_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> handle_finished_dialog_from_raw_script_line_func)
{
   this->handle_finished_dialog_from_raw_script_line_func = handle_finished_dialog_from_raw_script_line_func;
}


void BasicCharacterDialogDriver::set_handle_finished_dialog_from_raw_script_line_func_user_data(void* handle_finished_dialog_from_raw_script_line_func_user_data)
{
   this->handle_finished_dialog_from_raw_script_line_func_user_data = handle_finished_dialog_from_raw_script_line_func_user_data;
}


AllegroFlare::Elements::DialogRoll BasicCharacterDialogDriver::get_dialog_roll() const
{
   return dialog_roll;
}


std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> BasicCharacterDialogDriver::get_handle_activate_dialog_from_raw_script_line_func() const
{
   return handle_activate_dialog_from_raw_script_line_func;
}


void* BasicCharacterDialogDriver::get_handle_activate_dialog_from_raw_script_line_func_user_data() const
{
   return handle_activate_dialog_from_raw_script_line_func_user_data;
}


std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> BasicCharacterDialogDriver::get_handle_finished_dialog_from_raw_script_line_func() const
{
   return handle_finished_dialog_from_raw_script_line_func;
}


void* BasicCharacterDialogDriver::get_handle_finished_dialog_from_raw_script_line_func_user_data() const
{
   return handle_finished_dialog_from_raw_script_line_func_user_data;
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

void BasicCharacterDialogDriver::on_before_spawn_basic_dialog(std::string speaking_character_identifier)
{
   set_speaking_character_avatar(speaking_character_identifier);
   return;
}

void BasicCharacterDialogDriver::on_before_spawn_choice_dialog(std::string speaking_character_identifier)
{
   set_speaking_character_avatar(speaking_character_identifier);
   return;
}

void BasicCharacterDialogDriver::on_raw_script_line_activate(AllegroFlare::DialogSystem::DialogSystem* dialog_system, AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node)
{
   // TODO: Will you need the dialog node name?
   if (handle_activate_dialog_from_raw_script_line_func)
   {
      handle_activate_dialog_from_raw_script_line_func(
         dialog_system,
         active_dialog_box,
         active_dialog_node,
         handle_activate_dialog_from_raw_script_line_func_user_data
      );
   }
   // Nothing to do in this case
   return;
}

void BasicCharacterDialogDriver::on_raw_script_line_finished(AllegroFlare::DialogSystem::DialogSystem* dialog_system, AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node)
{
   if (handle_finished_dialog_from_raw_script_line_func)
   {
      handle_finished_dialog_from_raw_script_line_func(
         dialog_system,
         active_dialog_box,
         active_dialog_node,
         handle_finished_dialog_from_raw_script_line_func_user_data
      );
   }
   // Nothing to do in this case
   return;
}

std::string BasicCharacterDialogDriver::decorate_speaking_character_name(std::string speaking_character_identifier)
{
   // TODO: Translate the speaking character identifier to display_name
   return speaking_character_identifier;
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

void BasicCharacterDialogDriver::set_speaking_character_avatar(std::string speaking_character_identifier, std::string speaking_character_expression)
{
   if (!((!speaking_character_identifier.empty())))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::set_speaking_character_avatar]: error: guard \"(!speaking_character_identifier.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::set_speaking_character_avatar: error: guard \"(!speaking_character_identifier.empty())\" not met");
   }
   auto _driver = this;
   // TODO: Test the guards. Is the second one (!speaking_character_identifier.empty()) necessary?
   //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver = this;
   if (!_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      throw std::runtime_error("expecting type aaaaa");
      //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *as =
         //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
   }

   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *as =
      static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);

   //if (!_driver->is_type(AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal::TYPE))
   //{
      //throw std::runtime_error("expecting type aaaaa");
   //}

   if (!as->active_character_staging_layout)
   {
      return; // TODO: Hack, not sure if this is expected behavior
      throw std::runtime_error("expecting type bbbbb");
   }
   //->is_type(AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal::TYPE))
   if (!as->active_character_staging_layout->is_type(AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal::TYPE))
   {
      throw std::runtime_error("expecting type cccccc");
   }

   AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal *layout_as =
      static_cast<AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal*>(
         as->active_character_staging_layout
      );

   AllegroFlare::DialogSystem::CharacterStagingLayouts::Base *layout = layout_as; ////layout_as->active_character_staging_layout;

   //if (driver->active_character_staging_layout->is_type(
            //AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered::TYPE
         //))
   //{
      //AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered *as =
         //static_cast<AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered*>(
            //driver->active_character_staging_layout
         //);
      ALLEGRO_BITMAP *speaking_character_bitmap = as->lookup_speaking_character_avatar(
            speaking_character_identifier,
            speaking_character_expression
         );

      //if (!speaking_character_bitmap) as->clear();
      //else as->set_speaking_character_bitmap(speaking_character_bitmap);

      if (!speaking_character_bitmap) layout->clear();
      else layout->set_speaking_character_bitmap(speaking_character_bitmap);
      // TODO: Set the character
   //}
   //else
   //{
      //throw std::runtime_error(
         //"DialogSystemSystemDrivers::BasicCharacterDialogDriver::set_speaking_character: error: Unable to perform action because "
            //"\"driver.active_character_staging_layout\" is of type \"" + driver->active_character_staging_layout->get_type() + "\" "
            //"and a condition is not provided to handle this type."
      //);
   //}
   return;
}

ALLEGRO_BITMAP* BasicCharacterDialogDriver::lookup_speaking_character_avatar(std::string speaking_character_identifier, std::string speaking_character_expression)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::lookup_speaking_character_avatar]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::lookup_speaking_character_avatar: error: guard \"initialized\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::lookup_speaking_character_avatar]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::lookup_speaking_character_avatar: error: guard \"bitmap_bin\" not met");
   }
   auto _driver = this;
   // TODO: Review guards
   // TODO: Consider throw on missing character_roster
   if (!_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      throw std::runtime_error("expecting type ddddd");
      //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *as =
         //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
   }

   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *as =
      static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);

   AllegroFlare::DialogSystem::CharacterRoster *character_roster = as->character_roster;
   //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);

   //if (!_driver->is_type(AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal::TYPE))
   //{
      //throw std::runtime_error("expecting type aaaaa");
   //}

   if (character_roster)
   {
      if (!character_roster->character_exists_by_name(speaking_character_identifier))
      {
         // Throw for now
         std::stringstream available_character_names;
         available_character_names << "[ ";
         for (auto &character_identifier : character_roster->get_character_names())
         {
            available_character_names << "\"" << character_identifier << "\", ";
         }
         available_character_names << " ]";

         throw std::runtime_error("Roster is present, but character \"" + speaking_character_identifier + "\" "
                                  "does not exist in roster. Available names are " + available_character_names.str()
                                  );
      }

      AllegroFlare::DialogSystem::Characters::Base *base =
         character_roster->find_character_by_name(speaking_character_identifier);

      if (base->is_type(AllegroFlare::DialogSystem::Characters::Basic::TYPE))
      {
         AllegroFlare::DialogSystem::Characters::Basic *as =
            static_cast<AllegroFlare::DialogSystem::Characters::Basic*>(base);

         std::string bitmap_identifier_to_use = "";
         if (as->expression_exists(speaking_character_expression))
         {
            bitmap_identifier_to_use = as->find_expression(speaking_character_expression);
         }
         else
         {
            // TODO: Add report about missing expression
            bitmap_identifier_to_use = as->get_avatar_portrait_identifier();
         }

         return bitmap_bin->auto_get(bitmap_identifier_to_use);
      }
      else
      {
         throw std::runtime_error("DialogSystemDrivers::BasicCharacterDialogDriver: unknown handled character type");
      }
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


