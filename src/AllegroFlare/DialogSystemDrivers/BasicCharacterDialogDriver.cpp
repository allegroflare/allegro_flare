

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
   , handle_load_node_bank_from_file_func()
   , handle_load_node_bank_from_file_func_user_data(nullptr)
   , handle_decorate_speaking_character_name_func()
   , handle_decorate_speaking_character_name_func_user_data(nullptr)
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


void BasicCharacterDialogDriver::set_handle_activate_dialog_from_raw_script_line_func(std::function<bool( AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*) > handle_activate_dialog_from_raw_script_line_func)
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


void BasicCharacterDialogDriver::set_handle_load_node_bank_from_file_func(std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> handle_load_node_bank_from_file_func)
{
   this->handle_load_node_bank_from_file_func = handle_load_node_bank_from_file_func;
}


void BasicCharacterDialogDriver::set_handle_load_node_bank_from_file_func_user_data(void* handle_load_node_bank_from_file_func_user_data)
{
   this->handle_load_node_bank_from_file_func_user_data = handle_load_node_bank_from_file_func_user_data;
}


void BasicCharacterDialogDriver::set_handle_decorate_speaking_character_name_func(std::function<std::string(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*, std::string, void*)> handle_decorate_speaking_character_name_func)
{
   this->handle_decorate_speaking_character_name_func = handle_decorate_speaking_character_name_func;
}


void BasicCharacterDialogDriver::set_handle_decorate_speaking_character_name_func_user_data(void* handle_decorate_speaking_character_name_func_user_data)
{
   this->handle_decorate_speaking_character_name_func_user_data = handle_decorate_speaking_character_name_func_user_data;
}


AllegroFlare::Elements::DialogRoll BasicCharacterDialogDriver::get_dialog_roll() const
{
   return dialog_roll;
}


std::function<bool( AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*) > BasicCharacterDialogDriver::get_handle_activate_dialog_from_raw_script_line_func() const
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


std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> BasicCharacterDialogDriver::get_handle_load_node_bank_from_file_func() const
{
   return handle_load_node_bank_from_file_func;
}


void* BasicCharacterDialogDriver::get_handle_load_node_bank_from_file_func_user_data() const
{
   return handle_load_node_bank_from_file_func_user_data;
}


std::function<std::string(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*, std::string, void*)> BasicCharacterDialogDriver::get_handle_decorate_speaking_character_name_func() const
{
   return handle_decorate_speaking_character_name_func;
}


void* BasicCharacterDialogDriver::get_handle_decorate_speaking_character_name_func_user_data() const
{
   return handle_decorate_speaking_character_name_func_user_data;
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

void BasicCharacterDialogDriver::on_switch_out()
{
   if (active_character_staging_layout) active_character_staging_layout->hide();
   return;
}

bool BasicCharacterDialogDriver::on_load_node_bank_from_file(std::string filename, AllegroFlare::DialogTree::NodeBank* node_bank_to_load_into)
{
   if (!(node_bank_to_load_into))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::on_load_node_bank_from_file]: error: guard \"node_bank_to_load_into\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::on_load_node_bank_from_file: error: guard \"node_bank_to_load_into\" not met");
   }
   bool handled = true;
   if (handle_load_node_bank_from_file_func)
   {
      handled = handle_load_node_bank_from_file_func(
         filename,
         node_bank_to_load_into,
         handle_load_node_bank_from_file_func_user_data
         //user_data
      );

      // TODO: Consider adding "handled == false" error throwing here
   }
   return handled;
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

void BasicCharacterDialogDriver::on_raw_script_line_activate(AllegroFlare::DialogSystem::DialogSystem* dialog_system, std::string activating_node_name, AllegroFlare::DialogTree::Nodes::Base* activating_node, void* user_data)
{
   // TODO: Will you need the dialog node name?
   if (handle_activate_dialog_from_raw_script_line_func)
   {
      handle_activate_dialog_from_raw_script_line_func(
         dialog_system,
         activating_node_name,
         activating_node,
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

bool BasicCharacterDialogDriver::on_activate_dialog_node_type_unhandled(AllegroFlare::DialogSystem::DialogSystem* dialog_system, std::string active_dialog_node_name, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node)
{
   // TODO: If you want handle custom dialog nodes, consider adding the properties below to this class, and
   // calling/using them here in this function:

   //- name: activate_dialog_node_type_unhandled_func
      //type: std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)>
      //init_with: ''
      //getter: true
      //setter: true

   //- name: activate_dialog_node_type_unhandled_func_user_data
      //type: void*
      //init_with: nullptr
      //getter: true
      //setter: true
   return false;
}

std::string BasicCharacterDialogDriver::decorate_speaking_character_name(std::string speaking_character_identifier)
{
   // TODO: Consider asking for find_character_by_identifier_as_Basic and use "display_name" as return value
   // if present
   std::string result = speaking_character_identifier;
   if (handle_decorate_speaking_character_name_func)
   {
      result = handle_decorate_speaking_character_name_func(
         this,
         speaking_character_identifier,
         handle_decorate_speaking_character_name_func_user_data
      );
   }
   return result;
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
   if (!active_character_staging_layout)
   {
      return; // TODO: Hack, not sure if this is expected behavior
      throw std::runtime_error("expecting type bbbbb");
   }

   AllegroFlare::DialogSystem::CharacterStagingLayouts::Base *layout = active_character_staging_layout;

   ALLEGRO_BITMAP *speaking_character_bitmap = lookup_speaking_character_avatar(
      speaking_character_identifier,
      speaking_character_expression
   );

   if (!speaking_character_bitmap)
   {
      layout->clear();
   }
   else
   {
      layout->set_speaking_character_bitmap(speaking_character_bitmap);
   }

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


