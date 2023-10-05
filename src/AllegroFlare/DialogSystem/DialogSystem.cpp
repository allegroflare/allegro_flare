

#include <AllegroFlare/DialogSystem/DialogSystem.hpp>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogYAMLFile.hpp>
#include <AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName.hpp>
#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/YAMLLoader.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/StringFormatValidator.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <allegro5/allegro_primitives.h>
#include <filesystem>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{


DialogSystem::DialogSystem(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::DialogSystem::CharacterRoster* character_roster)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , dialog_node_bank({})
   , character_roster(character_roster)
   , active_dialog_box(nullptr)
   , selection_cursor_box({})
   , active_dialog_node(nullptr)
   , active_dialog_node_name("[unset-active_dialog_node_name]")
   , active_character_staging_layout(nullptr)
   , load_node_bank_func()
   , dialog_roll()
   , load_node_bank_func_user_data(nullptr)
   , activate_dialog_node_by_name_func()
   , activate_dialog_node_by_name_func_user_data(nullptr)
   , activate_dialog_node_type_unhandled_func()
   , activate_dialog_node_type_unhandled_func_user_data(nullptr)
   , dialog_advance_is_finished_node_type_unhandled_func()
   , dialog_advance_is_finished_node_type_unhandled_func_user_data(nullptr)
   , switched_in(false)
   , standard_dialog_box_font_name(DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME)
   , standard_dialog_box_font_size(DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE)
   , initialized(false)
{
}


DialogSystem::~DialogSystem()
{
}


void DialogSystem::set_character_roster(AllegroFlare::DialogSystem::CharacterRoster* character_roster)
{
   this->character_roster = character_roster;
}


void DialogSystem::set_load_node_bank_func(std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> load_node_bank_func)
{
   this->load_node_bank_func = load_node_bank_func;
}


void DialogSystem::set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll)
{
   this->dialog_roll = dialog_roll;
}


void DialogSystem::set_load_node_bank_func_user_data(void* load_node_bank_func_user_data)
{
   this->load_node_bank_func_user_data = load_node_bank_func_user_data;
}


void DialogSystem::set_activate_dialog_node_by_name_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*)> activate_dialog_node_by_name_func)
{
   this->activate_dialog_node_by_name_func = activate_dialog_node_by_name_func;
}


void DialogSystem::set_activate_dialog_node_by_name_func_user_data(void* activate_dialog_node_by_name_func_user_data)
{
   this->activate_dialog_node_by_name_func_user_data = activate_dialog_node_by_name_func_user_data;
}


void DialogSystem::set_activate_dialog_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func)
{
   this->activate_dialog_node_type_unhandled_func = activate_dialog_node_type_unhandled_func;
}


void DialogSystem::set_activate_dialog_node_type_unhandled_func_user_data(void* activate_dialog_node_type_unhandled_func_user_data)
{
   this->activate_dialog_node_type_unhandled_func_user_data = activate_dialog_node_type_unhandled_func_user_data;
}


void DialogSystem::set_dialog_advance_is_finished_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> dialog_advance_is_finished_node_type_unhandled_func)
{
   this->dialog_advance_is_finished_node_type_unhandled_func = dialog_advance_is_finished_node_type_unhandled_func;
}


void DialogSystem::set_dialog_advance_is_finished_node_type_unhandled_func_user_data(void* dialog_advance_is_finished_node_type_unhandled_func_user_data)
{
   this->dialog_advance_is_finished_node_type_unhandled_func_user_data = dialog_advance_is_finished_node_type_unhandled_func_user_data;
}


void DialogSystem::set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name)
{
   this->standard_dialog_box_font_name = standard_dialog_box_font_name;
}


void DialogSystem::set_standard_dialog_box_font_size(int standard_dialog_box_font_size)
{
   this->standard_dialog_box_font_size = standard_dialog_box_font_size;
}


AllegroFlare::EventEmitter* DialogSystem::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::DialogTree::NodeBank DialogSystem::get_dialog_node_bank() const
{
   return dialog_node_bank;
}


AllegroFlare::DialogSystem::CharacterRoster* DialogSystem::get_character_roster() const
{
   return character_roster;
}


std::string DialogSystem::get_active_dialog_node_name() const
{
   return active_dialog_node_name;
}


std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> DialogSystem::get_load_node_bank_func() const
{
   return load_node_bank_func;
}


AllegroFlare::Elements::DialogRoll DialogSystem::get_dialog_roll() const
{
   return dialog_roll;
}


void* DialogSystem::get_load_node_bank_func_user_data() const
{
   return load_node_bank_func_user_data;
}


std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*)> DialogSystem::get_activate_dialog_node_by_name_func() const
{
   return activate_dialog_node_by_name_func;
}


void* DialogSystem::get_activate_dialog_node_by_name_func_user_data() const
{
   return activate_dialog_node_by_name_func_user_data;
}


std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> DialogSystem::get_activate_dialog_node_type_unhandled_func() const
{
   return activate_dialog_node_type_unhandled_func;
}


void* DialogSystem::get_activate_dialog_node_type_unhandled_func_user_data() const
{
   return activate_dialog_node_type_unhandled_func_user_data;
}


std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> DialogSystem::get_dialog_advance_is_finished_node_type_unhandled_func() const
{
   return dialog_advance_is_finished_node_type_unhandled_func;
}


void* DialogSystem::get_dialog_advance_is_finished_node_type_unhandled_func_user_data() const
{
   return dialog_advance_is_finished_node_type_unhandled_func_user_data;
}


bool DialogSystem::get_switched_in() const
{
   return switched_in;
}


std::string DialogSystem::get_standard_dialog_box_font_name() const
{
   return standard_dialog_box_font_name;
}


int DialogSystem::get_standard_dialog_box_font_size() const
{
   return standard_dialog_box_font_size;
}


AllegroFlare::Elements::DialogRoll &DialogSystem::get_dialog_roll_ref()
{
   return dialog_roll;
}


void DialogSystem::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
}

void DialogSystem::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
}

void DialogSystem::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
}

void DialogSystem::load_dialog_node_bank_from_file(std::string filename)
{
   if (!(std::filesystem::exists(filename)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::load_dialog_node_bank_from_file]: error: guard \"std::filesystem::exists(filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::load_dialog_node_bank_from_file: error: guard \"std::filesystem::exists(filename)\" not met");
   }
   // TODO: Validate a dialog is not currently running (or something)
   // TODO: Test these cases for loading multiple file formats with these extensions
   AllegroFlare::StringFormatValidator validator(filename);

   if (load_node_bank_func)
   {
      // TODO: Test the case where "load_node_bank_func"
      AllegroFlare::DialogTree::NodeBank loader_result_node_bank;
      bool handled = load_node_bank_func(filename, &loader_result_node_bank, load_node_bank_func_user_data);

      if (!handled)
      {
         AllegroFlare::Logger::throw_error(
               "AllegroFlare::DialogSystem::DialogSystem::load_dialog_node_bank_from_file"
               "a user \"load_node_bank_func\" has been provided, but it returned false when called, indicating "
                  "that it was not able to load the NodeBank as expected."
            );
      }

      dialog_node_bank = loader_result_node_bank;
   }
   else
   {
      if (validator.ends_with(".screenplay.txt"))
      {
         AllegroFlare::DialogTree::BasicScreenplayTextLoader loader;
         loader.load_file(filename);
         dialog_node_bank = loader.get_node_bank();
      }
      else if (validator.ends_with(".yml") || validator.ends_with(".yaml"))
      {
         AllegroFlare::DialogTree::YAMLLoader yaml_loader;
         yaml_loader.load_file(filename);
         dialog_node_bank = yaml_loader.get_node_bank();
      }
      else
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::DialogSystem::DialogSystem::load_dialog_node_bank_from_file",
            "Cannot load file. Unable to know what loader should be used for filename \"" + filename + "\""
         );
      }
   }
   return;
}

void DialogSystem::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::initialize: error: guard \"font_bin\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::initialize: error: guard \"event_emitter\" not met");
   }
   active_character_staging_layout = new AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered();
   initialized = true;
   return;
}

void DialogSystem::destroy()
{
   // TODO: This method requires consideration -- particularly active_speaker_layout which is currently owned
   // by this object. Also, this method will need to be called in Frameworks::Full
   delete active_character_staging_layout;
   return;
}

void DialogSystem::switch_in()
{
   if (!((!switched_in)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::switch_in]: error: guard \"(!switched_in)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::switch_in: error: guard \"(!switched_in)\" not met");
   }
   switched_in = true;
   return;
}

void DialogSystem::switch_out()
{
   if (!((switched_in)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::switch_out]: error: guard \"(switched_in)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::switch_out: error: guard \"(switched_in)\" not met");
   }
   switched_in = false;
   return;
}

void DialogSystem::set_speaking_character(std::string speaking_character_identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::set_speaking_character]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::set_speaking_character: error: guard \"initialized\" not met");
   }
   if (active_character_staging_layout->is_type(
            AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered::TYPE
         ))
   {
      AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered *as =
         static_cast<AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered*>(
            active_character_staging_layout
         );
      ALLEGRO_BITMAP *speaking_character_bitmap = lookup_speaking_character_avatar(speaking_character_identifier);
      if (!speaking_character_bitmap) as->clear_speaking_character_bitmap();
      else as->set_speaking_character_bitmap(speaking_character_bitmap);
      // TODO: Set the character
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

ALLEGRO_BITMAP* DialogSystem::lookup_speaking_character_avatar(std::string speaking_character_identifier)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::lookup_speaking_character_avatar]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::lookup_speaking_character_avatar: error: guard \"bitmap_bin\" not met");
   }
   if (character_roster)
   {
      if (!character_roster->character_exists_by_name(speaking_character_identifier))
      {
         // Throw for now
         throw std::runtime_error("Roster is present, but character \"" + speaking_character_identifier + "\" "
                                  "does not exist in roster");
      }

      AllegroFlare::DialogSystem::Characters::Base *base =
         character_roster->find_character_by_name(speaking_character_identifier);

      if (base->is_type(AllegroFlare::DialogSystem::Characters::Basic::TYPE))
      {
         AllegroFlare::DialogSystem::Characters::Basic *as =
            static_cast<AllegroFlare::DialogSystem::Characters::Basic*>(base);
         return bitmap_bin->auto_get(as->get_avatar_portrait_identifier());
      }
      else
      {
         throw std::runtime_error("DialogSystem: unknown handled character type");
      }
   }
   return nullptr;
}

void DialogSystem::activate_dialog_node_by_name(std::string dialog_name)
{
   active_dialog_node = dialog_node_bank.find_node_by_name(dialog_name);
   active_dialog_node_name = dialog_name;

   if (activate_dialog_node_by_name_func)
   {
      bool handled = activate_dialog_node_by_name_func(
            this,
            active_dialog_node_name,
            active_dialog_node,
            activate_dialog_node_by_name_func_user_data
         );

      if (!handled)
      {
         throw std::runtime_error(
               "DialogSystem::activate_dialog_node_by_name: error: a user \"activate_dialog_node_by_name_func\" has "
                  "been provided, but it returned false when called, indicating that it was not able to handle the "
                  "node activation."
            );
      }
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as_multipage_with_options =
         static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(active_dialog_node);

      std::string node_pages_speaker = as_multipage_with_options->get_speaker();
      std::vector<std::string> node_pages = as_multipage_with_options->get_pages();
      std::vector<std::string> node_options_as_text = as_multipage_with_options->build_options_as_text();

      if (node_options_as_text.empty())
      {
         throw std::runtime_error(
            "DialogSystem::activate_dialog_node_by_name: error: Expecting 1 or many options for node named \""
               + dialog_name + "\" but there are no options."
         );
      }
      else if (node_options_as_text.size() == 1)
      {
         // If dialog has only one option, spawn a basic dialog
         set_speaking_character(node_pages_speaker);
         spawn_basic_dialog(node_pages);
      }
      else // (node_options_as_text.size() > 1)
      {
         // TODO: Here, if dialog has multiple options, spawn a "choice" dialog
         if (node_pages.size() != 1)
         {
            throw std::runtime_error(
               "DialogSystem::activate_dialog_node_by_name: error: Expecting only 1 page for dialog node \""
                  + dialog_name + "\" (because it is going to be used to build a Choice dialog, "
                  "but there are \"" + std::to_string(node_pages.size()) + "\" pages."
            );
         }
         set_speaking_character(node_pages_speaker);
         spawn_choice_dialog(node_pages[0], node_options_as_text);
      }
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
   {
      //AllegroFlare::DialogTree::Nodes::ExitDialog *as =
         //static_cast<AllegroFlare::DialogTree::Nodes::ExitDialog*>(base);
      shutdown_dialog(); // TODO: See if this is a correct expectation for this event
   }
   else
   {
      bool handled = false;
      if (activate_dialog_node_type_unhandled_func)
      {
         handled = activate_dialog_node_type_unhandled_func(
               this,
               activate_dialog_node_type_unhandled_func_user_data
         );
      }

      if (!handled)
      {
         throw std::runtime_error(
            "DialogSystem::activate_dialog_node_by_name: error: Unable to handle dialog node activation on type \""
               + active_dialog_node->get_type() + "\". A condition is not provided to handle this type."
         );
      }
   }
   return;
}

void DialogSystem::spawn_basic_dialog(std::vector<std::string> pages)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_basic_dialog(pages);

   // TODO: Address when and where a switch_in should occur
   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      switch_in();
      active_character_staging_layout->show(); // TODO: Test the show occurs
      event_emitter->emit_dialog_switch_in_event();
   }
   return;
}

void DialogSystem::spawn_choice_dialog(std::string prompt, std::vector<std::string> options)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog

   // NOTE: In order to be compatable with "create_choice_dialog", we will fill with some dummy values.
   // For now, we use the cursor position of the choice dialog to pick the option. Consider revising or cleaning up
   std::vector<std::pair<std::string, std::string>> options_that_are_also_values;
   for (auto &option : options)
   {
      options_that_are_also_values.push_back({option, option});
   }

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   AllegroFlare::Elements::DialogBoxes::Choice *choice_dialog_box =
         dialog_box_factory.create_choice_dialog(prompt, options_that_are_also_values);
   active_dialog_box = choice_dialog_box;


   // Set the cursor selection box position to this point
   AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer_for_dimensions(
      font_bin,
      bitmap_bin,
      choice_dialog_box
   );

   std::tuple<float, float, float, float> selection_dimensions =
         choice_renderer_for_dimensions.calculate_dimensions_of_current_selection();
   choice_renderer_for_dimensions.helper__set_selection_cursor_box_dimensions_to(
         &selection_cursor_box,
         selection_dimensions
      );

   // TODO: Address when and where a switch_in should occur
   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      switch_in();
      active_character_staging_layout->show(); // TODO: Test the show occurs
      event_emitter->emit_dialog_switch_in_event();
   }
   return;
}

void DialogSystem::update(float time_now)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::update: error: guard \"initialized\" not met");
   }
   // TODO: Ensure time_now does not accidentally become 0 by not being noticed as an argument
   // TODO: Ensure time_now is passed down to active dialog updates()
   if (active_dialog_box) active_dialog_box->update();
   selection_cursor_box.update();
   return;
}

void DialogSystem::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::render: error: guard \"initialized\" not met");
   }
   if (active_character_staging_layout)
   {
      active_character_staging_layout->render();
   }

   if (active_dialog_box)
   {
      AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(
            font_bin,
            bitmap_bin,
            active_dialog_box,
            &selection_cursor_box
         );
      dialog_box_renderer.set_standard_dialog_box_font_name(standard_dialog_box_font_name);
      dialog_box_renderer.set_standard_dialog_box_font_size(standard_dialog_box_font_size);
      dialog_box_renderer.render();
   }
}

bool DialogSystem::a_dialog_is_active()
{
   return (active_dialog_box != nullptr);
}

void DialogSystem::dialog_advance()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::dialog_advance]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::dialog_advance: error: guard \"initialized\" not met");
   }
   if (!(active_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::dialog_advance]: error: guard \"active_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::dialog_advance: error: guard \"active_dialog_box\" not met");
   }
   active_dialog_box->advance();
   if (active_dialog_box->get_finished())
   {
      if (active_dialog_node)
      {
         if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
         {
            AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as_multipage_with_options =
               static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(active_dialog_node);

            if (as_multipage_with_options->num_options() == 0)
            {
               // If this dialog node has no options, then proceed to a "shutdown" state

               // TODO: Replace this throw with a shutdown
               throw std::runtime_error(
                  "DialogSystem::dialog_advance: error: Expecting 1 or many options for node named \""
                     + active_dialog_node_name + "\" but there are no options."
               );
            }
            else if (as_multipage_with_options->num_options() == 1)
            {
               // If the dialog node has 1 option, "activate" it
               int current_dialog_selection_choice = 0;
               activate_dialog_option(current_dialog_selection_choice);
            }
            else // if (as_multipage_with_options.num_options() > 1)
            {
               // If the dialog *node* has more than 1 option, correlate the dialog *box*'s current cursor position
                  // with the result and "activate" it
               if (!active_dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Choice::TYPE))
               {
                  throw std::runtime_error(
                     "DialogSystem::dialog_advance: error: Expecting active_dialog_box (with more than one option) "
                        "to be of type \"AllegroFlare::Elements::DialogBoxes::Choice::TYPE\", but it is of type \""
                        + active_dialog_box->get_type() + "\""
                  );
               }
               else
               {
                  AllegroFlare::Elements::DialogBoxes::Choice *as_choice_dialog_box = 
                     static_cast<AllegroFlare::Elements::DialogBoxes::Choice*>(active_dialog_box);

                  int current_dialog_selection_choice = as_choice_dialog_box->get_cursor_position();
                  activate_dialog_option(current_dialog_selection_choice);
               }
            }
         }
         //else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
         //{
            //AllegroFlare::DialogTree::Nodes::ExitDialog *as =
               //static_cast<AllegroFlare::DialogTree::Nodes::ExitDialog*>(base);
            //shutdown_dialog(); // TODO: See if this is a correct expectation for this event
         //}
         else
         {
            bool handled = false;
            if (dialog_advance_is_finished_node_type_unhandled_func)
            {
               handled = dialog_advance_is_finished_node_type_unhandled_func(
                     this,
                     active_dialog_box,
                     active_dialog_node,
                     dialog_advance_is_finished_node_type_unhandled_func_user_data
                  );
            }

            if (!handled)
            {
               throw std::runtime_error(
                  "DialogSystem::dialog_advance: error: Unable to handle case where dialog *box* is finished when "
                     "the dialog *node* type \""
                     + active_dialog_node->get_type() + "\". A condition is not provided to handle this type."
               );
               //throw std::runtime_error(
                  //"DialogSystem::activate_dialog_node_by_name: error: Unable to handle dialog node activation on type \""
                     //+ active_dialog_node->get_type() + "\". A condition is not provided to handle this type."
               //);
            }

            //throw std::runtime_error(
               //"DialogSystem::dialog_advance: error: Unable to handle case where dialog *box* is finished when "
                  //"the dialog *node* type \""
                  //+ active_dialog_node->get_type() + "\". A condition is not provided to handle this type."
            //);
         }
      }

      // TODO: Figure out what to do when the dialog is finished.
   }
   return;
}

void DialogSystem::activate_dialog_option(int selection_choice)
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_dialog_option]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_dialog_option: error: guard \"event_emitter\" not met");
   }
   if (!(active_dialog_node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_dialog_option]: error: guard \"active_dialog_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_dialog_option: error: guard \"active_dialog_node\" not met");
   }
   if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
   {

      AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as_multipage_with_options =
         static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(active_dialog_node);

      // TODO: Consider case where dialog node has no (empty) options
      if (!(selection_choice >= 0))
      {
         throw std::runtime_error(
            "DialogSystem::activate_dialog_option: error: selection_choice must be >= 0"
         );
      }
      if (!(selection_choice < as_multipage_with_options ->num_options()))
      {
         throw std::runtime_error(
            "DialogSystem::activate_dialog_option: error: selection_choice must be less than the num options"
         );
      }

      AllegroFlare::DialogTree::NodeOptions::Base* node_option =
         as_multipage_with_options->get_option_num(selection_choice).second;
      std::string node_option_type = node_option->get_type();

      std::map<std::string, std::function<void()>> types_map = {
         { AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE, [this, node_option]() {
            AllegroFlare::DialogTree::NodeOptions::ExitDialog* as_exit_dialog_node_option =
               static_cast<AllegroFlare::DialogTree::NodeOptions::ExitDialog*>(node_option);

            //event_emitter->emit_dialog_close_event();
            shutdown_dialog(); // TODO: See if this is a correct expectation for this event
         }},
         { AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE, [this, node_option]() {
            // TODO: Test this case
            AllegroFlare::DialogTree::NodeOptions::GoToNode* as_go_to_node_dialog_node_option =
               static_cast<AllegroFlare::DialogTree::NodeOptions::GoToNode*>(node_option);
            std::string target_node_name = as_go_to_node_dialog_node_option->get_target_node_name();

            //event_emitter->emit_dialog_open_event(target_node_name);
            activate_dialog_node_by_name(target_node_name);
         }},
      };

      // locate and call the function to handle the item
      if (types_map.count(node_option_type) == 0)
      {
         // item not found
         std::stringstream error_message;
         error_message << "[DialogTree::NodeOptionActivator::activate]: error: Cannot activate a node with the "
                       << "node_option_type \"" << node_option_type << "\", a handling for that type does not exist.";
         throw std::runtime_error(error_message.str());
      }
      else
      {
         // call the item
         types_map[node_option_type]();
      }
   }
   else
   {
      throw std::runtime_error(
         "DialogSystem::activate_dialog_option: error: Unable to handle case where dialog *node* is of type \""
            + active_dialog_node->get_type() + "\"."
      );
   }

   return;
}

bool DialogSystem::dialog_is_finished()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::dialog_is_finished]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::dialog_is_finished: error: guard \"initialized\" not met");
   }
   if (!(active_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::dialog_is_finished]: error: guard \"active_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::dialog_is_finished: error: guard \"active_dialog_box\" not met");
   }
   return active_dialog_box->get_finished();
}

bool DialogSystem::shutdown_dialog()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::shutdown_dialog]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::shutdown_dialog: error: guard \"initialized\" not met");
   }
   if (!active_dialog_box) return false;
   delete active_dialog_box; // TODO: Consider a less intrusive soft delete (hide motion, with cleanup during update)
   active_dialog_box = nullptr;

   active_dialog_node = nullptr;
   active_dialog_node_name = "";

   if (active_character_staging_layout)
   {
      // TODO: Confirm "hide" should occur here
      active_character_staging_layout->hide(); // TODO: Test this hide occurs as expected
   }

   // NOTE: Note that active_dialog_node is not deleted, because any pointer to a dialog node is a pointer
   // to one that is static in the dialog_node_bank
   if (get_switched_in())
   {
      switch_out();
      event_emitter->emit_dialog_switch_out_event();
   }
   return true;
}

void DialogSystem::move_dialog_cursor_position_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::move_dialog_cursor_position_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::move_dialog_cursor_position_up: error: guard \"initialized\" not met");
   }
   if (!active_dialog_box) return;
   active_dialog_box->move_cursor_position_up();
   if (active_dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Choice::TYPE))
   {
      AllegroFlare::Elements::DialogBoxes::Choice *as_choice_dialog_box =
            static_cast<AllegroFlare::Elements::DialogBoxes::Choice*>(active_dialog_box);

      // Set the cursor selection box position to this point
      AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer_for_dimensions(
         font_bin,
         bitmap_bin,
         as_choice_dialog_box
      );

      std::tuple<float, float, float, float> selection_dimensions =
            choice_renderer_for_dimensions.calculate_dimensions_of_current_selection();
      choice_renderer_for_dimensions.helper__reposition_selection_cursor_box_dimensions_to(
            &selection_cursor_box,
            selection_dimensions
         );
   }
   return;
}

void DialogSystem::move_dialog_cursor_position_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::move_dialog_cursor_position_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::move_dialog_cursor_position_down: error: guard \"initialized\" not met");
   }
   if (!active_dialog_box) return;
   active_dialog_box->move_cursor_position_down();
   // TODO: Reposition the cursor
   if (active_dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Choice::TYPE))
   {
      AllegroFlare::Elements::DialogBoxes::Choice *as_choice_dialog_box =
            static_cast<AllegroFlare::Elements::DialogBoxes::Choice*>(active_dialog_box);

      // Set the cursor selection box position to this point
      AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer_for_dimensions(
         font_bin,
         bitmap_bin,
         as_choice_dialog_box
      );

      std::tuple<float, float, float, float> selection_dimensions =
            choice_renderer_for_dimensions.calculate_dimensions_of_current_selection();
      choice_renderer_for_dimensions.helper__reposition_selection_cursor_box_dimensions_to(
            &selection_cursor_box,
            selection_dimensions
         );
   }
   return;
}

void DialogSystem::handle_raw_ALLEGRO_EVENT_that_is_dialog_event(ALLEGRO_EVENT* ev, AllegroFlare::GameEventDatas::Base* data)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::handle_raw_ALLEGRO_EVENT_that_is_dialog_event]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::handle_raw_ALLEGRO_EVENT_that_is_dialog_event: error: guard \"ev\" not met");
   }
   if (!(data))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::handle_raw_ALLEGRO_EVENT_that_is_dialog_event]: error: guard \"data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::handle_raw_ALLEGRO_EVENT_that_is_dialog_event: error: guard \"data\" not met");
   }
   // TODO: Update this to a map caller pattern (static const)
   if (data->is_type(AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogYAMLFile::TYPE))
   {
      auto *as = static_cast<AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogYAMLFile*>(data);
      load_dialog_node_bank_from_file(as->get_yaml_filename());
   }
   // TODO: Rename this SpawnDialogByName to ActivateDialogNodeByName
   else if (data->is_type(AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName::TYPE))
   {
      auto *as = static_cast<AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName*>(data);
      activate_dialog_node_by_name(as->get_name());
   }
   else
   {
      throw std::runtime_error("handle_raw_ALLEGRO_EVENT_that_is_dialog_event unhandled case");
   }
   return;
}


} // namespace DialogSystem
} // namespace AllegroFlare


