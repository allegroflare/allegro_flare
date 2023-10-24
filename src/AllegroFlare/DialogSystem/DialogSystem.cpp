

#include <AllegroFlare/DialogSystem/DialogSystem.hpp>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered.hpp>
#include <AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogNodeBankFromFile.hpp>
#include <AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName.hpp>
#include <AllegroFlare/DialogSystem/NodeStates/Wait.hpp>
#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>
#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
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


DialogSystem::DialogSystem(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , dialog_node_bank({})
   , active_dialog_box(nullptr)
   , selection_cursor_box({})
   , active_dialog_node(nullptr)
   , active_dialog_node_name("[unset-active_dialog_node_name]")
   , active_dialog_node_state(nullptr)
   , _driver(nullptr)
   , load_node_bank_func()
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


void DialogSystem::set_active_dialog_node_state(AllegroFlare::DialogSystem::NodeStates::Base* active_dialog_node_state)
{
   this->active_dialog_node_state = active_dialog_node_state;
}


void DialogSystem::set_load_node_bank_func(std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> load_node_bank_func)
{
   this->load_node_bank_func = load_node_bank_func;
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


std::string DialogSystem::get_active_dialog_node_name() const
{
   return active_dialog_node_name;
}


std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> DialogSystem::get_load_node_bank_func() const
{
   return load_node_bank_func;
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


bool DialogSystem::get_initialized() const
{
   return initialized;
}


AllegroFlare::DialogSystemDrivers::Base* &DialogSystem::get__driver_ref()
{
   return _driver;
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

void DialogSystem::set_activate_dialog_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func)
{
   if (!(_driver))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::set_activate_dialog_node_type_unhandled_func]: error: guard \"_driver\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::set_activate_dialog_node_type_unhandled_func: error: guard \"_driver\" not met");
   }
   this->activate_dialog_node_type_unhandled_func = activate_dialog_node_type_unhandled_func;
   if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      driver->set_activate_dialog_node_type_unhandled_func(activate_dialog_node_type_unhandled_func);
   }
   else
   {
      throw std::runtime_error("Uknonwn type here (1)");
      // TODO: Throw
   }
   return;
}

void DialogSystem::set_activate_dialog_node_type_unhandled_func_user_data(void* activate_dialog_node_type_unhandled_func_user_data)
{
   if (!(_driver))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::set_activate_dialog_node_type_unhandled_func_user_data]: error: guard \"_driver\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::set_activate_dialog_node_type_unhandled_func_user_data: error: guard \"_driver\" not met");
   }
   this->activate_dialog_node_type_unhandled_func_user_data = activate_dialog_node_type_unhandled_func_user_data;
   if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      driver->set_activate_dialog_node_type_unhandled_func_user_data(
            activate_dialog_node_type_unhandled_func_user_data
         );
   }
   else
   {
      throw std::runtime_error("Uknonwn type here (2)");
      // TODO: Throw
   }
   return;
}

AllegroFlare::DialogSystemDrivers::Base* DialogSystem::get__driver()
{
   if (!((initialized)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::get__driver]: error: guard \"(initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::get__driver: error: guard \"(initialized)\" not met");
   }
   return _driver;
}

void DialogSystem::clear_and_reset()
{
   if (active_dialog_box)
   {
      delete active_dialog_box;
      active_dialog_box = nullptr;
   }

   // TODO: Hide selection cursor box (if showing)

   if (active_dialog_node)
   {
      active_dialog_node = nullptr;
   }

   dialog_node_bank.delete_all_nodes_and_clear();
   // TODO: Destroy dialog_node_bank

   active_dialog_node_name = "";
   if (active_dialog_node_state)
   {
      delete active_dialog_node_state;
      active_dialog_node_state = nullptr;
   }
   return;
}

void DialogSystem::set_dialog_node_bank(AllegroFlare::DialogTree::NodeBank dialog_node_bank)
{
   // TODO: Test the expected conditions when calling "set_dialog_node_bank" after init and/or when the node bank
   // is currently loaded (is it cleared? Does the active_dialog_box become nullptr, active_dialog_name empty, etc..)
   clear_and_reset(); // This step includes deleting all the nodes* in the node_bank
   this->dialog_node_bank = dialog_node_bank;
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

      set_dialog_node_bank(loader_result_node_bank);
   }
   else
   {
      AllegroFlare::StringFormatValidator validator(filename);

      if (validator.ends_with(".screenplay.txt"))
      {
         AllegroFlare::DialogTree::BasicScreenplayTextLoader loader;
         loader.load_file(filename);
         set_dialog_node_bank(loader.get_node_bank());
      }
      //else if (validator.ends_with(".yml") || validator.ends_with(".yaml"))
      //{
         //AllegroFlare::DialogTree::YAMLLoader yaml_loader;
         //yaml_loader.load_file(filename);
         //dialog_node_bank = yaml_loader.get_node_bank();
      //}
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
   _driver = new AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver();
      //{
         //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *as =
            //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(base);
      //}

   if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      driver->set_bitmap_bin(bitmap_bin);
      driver->initialize();
   }

   //_driver->initialize();
   //driver.active_character_staging_layout = new AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered();
   initialized = true;
   return;
}

void DialogSystem::destroy()
{
   // TODO: This method requires consideration -- particularly active_speaker_layout which is currently owned
   // by this object. Also, this method will need to be called in Frameworks::Full
   if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      driver->destroy();
      //driver->initialize();
   }
   //if (_driver) _driver->destroy();
   //delete driver.active_character_staging_layout;
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

void DialogSystem::activate_dialog_node_by_name(std::string dialog_name)
{
   active_dialog_node = dialog_node_bank.find_node_by_name(dialog_name);
   active_dialog_node_name = dialog_name;
   if (active_dialog_node_state)
   {
      delete active_dialog_node_state;
      active_dialog_node_state = nullptr;
   }

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

   if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);

      bool handled = driver->activate_dialog_node_by_name_func(
            this,
            active_dialog_node_name,
            active_dialog_node,
            activate_dialog_node_by_name_func_user_data
         );

      if (!handled)
      {
         throw std::runtime_error(
               "DialogSystem::activate_dialog_node_by_name: error: the driver activate_dialog_node_by_name_func"
                  "was called, but it returned false, indicating that it was not able to handle the "
                  "node activation."
            );
      }
   }

   return;
}

void DialogSystem::spawn_basic_dialog(std::string speaking_character, std::vector<std::string> pages)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_basic_dialog(speaking_character, pages);

   // TODO: Address when and where a switch_in should occur
   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      switch_in();
      // TODO: Consider alternative place for this show() call
      if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      {
         AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         driver->active_character_staging_layout->show(); // TODO: Test the show occurs
      }
      //driver.active_character_staging_layout->show(); // TODO: Test the show occurs
      event_emitter->emit_dialog_switch_in_event();
   }
   return;
}

void DialogSystem::spawn_wait_dialog(float duration_seconds)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_wait_dialog(duration_seconds);

   // TODO: Address when and where a switch_in should occur
   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      switch_in();
      // TODO: Consider alternative place for this show() call
      if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      {
         AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         driver->active_character_staging_layout->show(); // TODO: Test the show occurs
      }
      //driver.active_character_staging_layout->show(); // TODO: Test the show occurs
      event_emitter->emit_dialog_switch_in_event();
   }
   return;
}

void DialogSystem::spawn_choice_dialog(std::string speaking_character, std::string prompt, std::vector<std::string> options)
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
         dialog_box_factory.create_choice_dialog(speaking_character, prompt, options_that_are_also_values);
   active_dialog_box = choice_dialog_box;


   // Calculate the dimensions of the box, to set the cursor selection box on it
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
      if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      {
         AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         driver->active_character_staging_layout->show(); // TODO: Test the show occurs
      }
      //driver.active_character_staging_layout->show(); // TODO: Test the show occurs
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
   // TODO: Consider if ordering of events is correct
   if (active_dialog_box) active_dialog_box->update();
   selection_cursor_box.update();
   if (active_dialog_node_state) active_dialog_node_state->update(); // TODO: Pass down time_now

   if (active_dialog_box && active_dialog_box->ready_to_auto_advance()) dialog_advance();

   return;
}

void DialogSystem::evaluate_auto_advance_on_dialog_node_state()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::evaluate_auto_advance_on_dialog_node_state]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::evaluate_auto_advance_on_dialog_node_state: error: guard \"initialized\" not met");
   }
   if (!active_dialog_node_state) return;

   if (active_dialog_node_state->is_type(AllegroFlare::DialogSystem::NodeStates::Wait::TYPE))
   {
      AllegroFlare::DialogSystem::NodeStates::Wait *as =
         static_cast<AllegroFlare::DialogSystem::NodeStates::Wait*>(active_dialog_node_state);
      if (as->get_is_finished())
      {
         activate_dialog_node_by_name(as->get_wait_node()->get_next_node_identifier());
      }
   }
   // TODO: Consider using blacklist for items that are handled, but have no behavior
   // TODO: Consider throwing on unhandled type
   // TODO: Consider user callback for handling unknown node state type

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
   if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      if (driver->active_character_staging_layout)      {
         driver->active_character_staging_layout->render();
      }
   }
   //if (driver.active_character_staging_layout)      {
      //driver.active_character_staging_layout->render();
   //}

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
         else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::Wait::TYPE))
         {
            if (!active_dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Wait::TYPE))
            {
               throw std::runtime_error(
                  "DialogSystem::dialog_advance: error: Expecting active_dialog_box to be a nullptr (when node "
                     "is of type \"AllegroFlare::Elements::DialogBoxes::Wait::TYPE\"), but it is not."
               );
            }

            //if (!active_dialog_node_state->is_type(AllegroFlare::DialogSystem::NodeStates::Wait::TYPE))
            //{
               //throw std::runtime_error(
                  //"DialogSystem::dialog_advance: error: Expecting active_dialog_node_state to be of type "
                     //"\"AllegroFlare::DialogSystem::NodeStates::Wait::TYPE\", but it is of type \""
                     //+ active_dialog_node_state->get_type() + "\""
               //);
            //}

            AllegroFlare::DialogSystem::NodeStates::Wait *as =
               static_cast<AllegroFlare::DialogSystem::NodeStates::Wait*>(active_dialog_node_state);
            activate_dialog_node_by_name(as->get_wait_node()->get_next_node_identifier());
         }
         else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
         {
            //AllegroFlare::DialogTree::Nodes::ExitDialog *as =
               //static_cast<AllegroFlare::DialogTree::Nodes::ExitDialog*>(base);
            shutdown_dialog(); // TODO: Verify if this is a correct complete action for this event
         }
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
      if (!(selection_choice < as_multipage_with_options->num_options()))
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

   if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      // TODO: Confirm "hide" should occur here
      if (driver->active_character_staging_layout)
      {
         driver->active_character_staging_layout->hide();
      }
   }
   //if (driver.active_character_staging_layout)
   //{
      // TODO: Confirm "hide" should occur here
      //driver.active_character_staging_layout->hide(); // TODO: Test this hide occurs as expected
   //}

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
   if (data->is_type(AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogNodeBankFromFile::TYPE))
   {
      auto *as = static_cast<AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogNodeBankFromFile*>(data);
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
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::DialogSystem::DialogSystem::handle_raw_ALLEGRO_EVENT_that_is_dialog_event",
            "Unhandled case on type \"" + data->get_type() + "\"."
         );
   }
   return;
}


} // namespace DialogSystem
} // namespace AllegroFlare


