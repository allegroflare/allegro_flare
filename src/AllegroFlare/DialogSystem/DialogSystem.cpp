

#include <AllegroFlare/DialogSystem/DialogSystem.hpp>

#include <AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogNodeBankFromFile.hpp>
#include <AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName.hpp>
#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ChapterTitle.hpp>
#include <AllegroFlare/DialogTree/Nodes/EmitGameEvent.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/RawScriptLine.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
#include <AllegroFlare/DialogTree/Nodes/YouGotAnItemDialog.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/StringFormatValidator.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <allegro5/allegro_primitives.h>
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
   , selection_cursor_box({})
   , active_dialog_node(nullptr)
   , active_dialog_node_name("[unset-active_dialog_node_name]")
   , active_dialog_box(nullptr)
   , driver(nullptr)
   , switched_in(false)
   , standard_dialog_box_font_name(DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME)
   , standard_dialog_box_font_size(DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE)
   , standard_dialog_box_x(DEFAULT_STANDARD_DIALOG_BOX_X)
   , standard_dialog_box_y(DEFAULT_STANDARD_DIALOG_BOX_Y)
   , standard_dialog_box_width(DEFAULT_STANDARD_DIALOG_BOX_WIDTH)
   , standard_dialog_box_height(DEFAULT_STANDARD_DIALOG_BOX_HEIGHT)
   , initialized(false)
{
}


DialogSystem::~DialogSystem()
{
}


void DialogSystem::set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name)
{
   this->standard_dialog_box_font_name = standard_dialog_box_font_name;
}


void DialogSystem::set_standard_dialog_box_font_size(int standard_dialog_box_font_size)
{
   this->standard_dialog_box_font_size = standard_dialog_box_font_size;
}


void DialogSystem::set_standard_dialog_box_x(float standard_dialog_box_x)
{
   this->standard_dialog_box_x = standard_dialog_box_x;
}


void DialogSystem::set_standard_dialog_box_y(float standard_dialog_box_y)
{
   this->standard_dialog_box_y = standard_dialog_box_y;
}


void DialogSystem::set_standard_dialog_box_width(float standard_dialog_box_width)
{
   this->standard_dialog_box_width = standard_dialog_box_width;
}


void DialogSystem::set_standard_dialog_box_height(float standard_dialog_box_height)
{
   this->standard_dialog_box_height = standard_dialog_box_height;
}


AllegroFlare::EventEmitter* DialogSystem::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::DialogTree::NodeBank DialogSystem::get_dialog_node_bank() const
{
   return dialog_node_bank;
}


AllegroFlare::DialogTree::Nodes::Base* DialogSystem::get_active_dialog_node() const
{
   return active_dialog_node;
}


std::string DialogSystem::get_active_dialog_node_name() const
{
   return active_dialog_node_name;
}


AllegroFlare::Elements::DialogBoxes::Base* DialogSystem::get_active_dialog_box() const
{
   return active_dialog_box;
}


AllegroFlare::DialogSystemDrivers::Base* DialogSystem::get_driver() const
{
   return driver;
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


float DialogSystem::get_standard_dialog_box_x() const
{
   return standard_dialog_box_x;
}


float DialogSystem::get_standard_dialog_box_y() const
{
   return standard_dialog_box_y;
}


float DialogSystem::get_standard_dialog_box_width() const
{
   return standard_dialog_box_width;
}


float DialogSystem::get_standard_dialog_box_height() const
{
   return standard_dialog_box_height;
}


bool DialogSystem::get_initialized() const
{
   return initialized;
}


AllegroFlare::DialogSystemDrivers::Base* &DialogSystem::get_driver_ref()
{
   return driver;
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

void DialogSystem::set_driver(AllegroFlare::DialogSystemDrivers::Base* driver)
{
   // TODO: Consider consequences of assigning the driver mid-flight
   this->driver = driver;
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
   active_dialog_node_name = "";

   dialog_node_bank.delete_all_nodes_and_clear(); // TODO: Consider that pointers contained in this class could
                                                  // potentially be owned or in use by other objects

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
   if (!(driver))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::load_dialog_node_bank_from_file]: error: guard \"driver\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::load_dialog_node_bank_from_file: error: guard \"driver\" not met");
   }
   // TODO: Validate a dialog is not currently running (or something)

   AllegroFlare::DialogTree::NodeBank loader_result_node_bank;
   bool handled = driver->on_load_node_bank_from_file(
      filename,
      &loader_result_node_bank
   );

   if (!handled)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::DialogSystem::DialogSystem::load_dialog_node_bank_from_file"
            // TODO: Update this error message
            "\"on_load_node_bank_from_file\" was called on the driver but it returned false, indicating "
               "that it was not able to load the NodeBank as expected."
         );
   }

   set_dialog_node_bank(loader_result_node_bank);
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
   initialized = true;
   return;
}

void DialogSystem::destroy()
{
   // TODO: This method requires consideration -- particularly active_speaker_layout which is currently owned
   // by this object. Also, this method will need to be called in Frameworks::Full
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
   if (driver) driver->on_switch_in();
   event_emitter->emit_dialog_switched_in_event();
   return;
}

void DialogSystem::switch_in_if_not()
{
   if (!switched_in) switch_in();
   return;
}

void DialogSystem::switch_out()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::switch_out]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::switch_out: error: guard \"initialized\" not met");
   }
   if (!(switched_in))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::switch_out]: error: guard \"switched_in\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::switch_out: error: guard \"switched_in\" not met");
   }
   if (active_dialog_box)
   {
      delete active_dialog_box; // TODO: Consider a less intrusive soft delete (hide motion, with cleanup during update)
      active_dialog_box = nullptr;
   }

   active_dialog_node = nullptr;
   active_dialog_node_name = "";

   if (driver) driver->on_switch_out(); // TODO: This may need to be moved to "switch_out"

   event_emitter->emit_dialog_switched_out_event();

   switched_in = false;
   return;
}

void DialogSystem::activate_EmitGameEvent_dialog_node(AllegroFlare::DialogTree::Nodes::EmitGameEvent* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_EmitGameEvent_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_EmitGameEvent_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node; // TODO: Test this line
   // For now, nullptr data
   event_emitter->emit_game_event(AllegroFlare::GameEvent(node->get_game_event_name(), nullptr));
   if (!node->get_immediate_next_node_identifier().empty())
   {

      // If the "immediate_next_node_identifier" is not blank, activate that node. Note that any
      // expected consequences of the emitted game event will not have had time to process before this
      // "immediate_next_node_identifier" is emitted
      // TODO: Test this immediate next node activation
      // TODO: Consider if this should not be immediate and instead should be emitted as an event
         // (event would be cleaner)
      activate_dialog_node_by_name(node->get_immediate_next_node_identifier());
   }
   return;
}

void DialogSystem::activate_RawScriptLine_dialog_node(AllegroFlare::DialogTree::Nodes::RawScriptLine* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_RawScriptLine_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_RawScriptLine_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node; // TODO: Test this line
   // TODO: Investigate why no properties from RawScriptLine are used in this command
   // TODO: Test with driver and without driver
   if (driver) driver->on_raw_script_line_activate( // could find a better name for this method
      this,
      active_dialog_node_name,
      active_dialog_node
   );
   return;
}

void DialogSystem::activate_Wait_dialog_node(AllegroFlare::DialogTree::Nodes::Wait* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_Wait_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_Wait_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node;
   float duration_seconds = node->get_duration_sec();
   spawn_wait_dialog(duration_seconds);
   return;
}

void DialogSystem::activate_ChapterTitle_dialog_node(AllegroFlare::DialogTree::Nodes::ChapterTitle* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_ChapterTitle_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_ChapterTitle_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node;
   spawn_chapter_title_dialog(node->get_title_text(), node->get_duration());
   return;
}

void DialogSystem::activate_ExitDialog_dialog_node(AllegroFlare::DialogTree::Nodes::ExitDialog* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_ExitDialog_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_ExitDialog_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node; // Mostly redundant (shutdown_dialog will clear this value anyway)
   shutdown(); // TODO: See if this is a correct action for this event, e.g.
                      //       should it be "switch_out" or "shutdown", etc
   return;
}

void DialogSystem::activate_ExitProgram_dialog_node(AllegroFlare::DialogTree::Nodes::ExitProgram* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_ExitProgram_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_ExitProgram_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node;
   get_event_emitter()->emit_exit_game_event();
   return;
}

void DialogSystem::activate_YouGotAnItemDialog_dialog_node(AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_YouGotAnItemDialog_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_YouGotAnItemDialog_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node;
   std::string item_name = node->get_item_name();
   std::string item_bitmap_identifier = node->get_item_bitmap_identifier();
   spawn_you_got_an_item_dialog(item_name, item_bitmap_identifier);
   return;
}

void DialogSystem::activate_MultipageWithOptions_dialog_node(AllegroFlare::DialogTree::Nodes::MultipageWithOptions* node, std::string node_identifier)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_MultipageWithOptions_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_MultipageWithOptions_dialog_node: error: guard \"node\" not met");
   }
   active_dialog_node = node; // TODO: Test this line
   // NOTE: The actual technique used to handle the "MutlipageWithOptions" node will vary depending on the
   //       content of the node.
   //    1) If it has a only one choice, then only a BasicDialog will be spawned
   //       and on advance(), will activate the choice as if it were the only choice. This was done for downstream
   //       simplicity, but should likely be fixed.
   //    2) If no options are listed at all, will throw an error
   //    3) When options are present, only 1 page of dialog is allowed. Again, this was probably for downstream
   //       simplicity, and should likely be fixed.

   // NOTE: Additional side-effects include:
   //    1) A callback is used on the driver (on_before_spawn_basic_dialog) and (on_before_spawn_choice_dialog),
   //       typically used for changing the layout. TODO: Consider alternative placement for this feature. I don't
   //       think it should go into the spawning of the dialog box itself.
   //    2) The dialog box speaking characters are decorated (via a deletgated call to the driver) before being
   //       passed along to the dialog box on the creation call
   //    3) Consider where/when any spoken text should be appended to the dialog roll
            

   // TODO: Consider making node const (will require const on "build_options_as_text")
   // TODO: Consider removing "node_identifier" from this method, it's present only for debugging reasons
   // TODO: Unindent this method
   //AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as_multipage_with_options =
         //static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(active_dialog_node);


   std::string node_pages_speaker = node->get_speaker();
   std::vector<std::string> node_pages = node->get_pages();
   std::vector<std::string> node_options_as_text = node->build_options_as_text();
   int cursor_position_on_spawn = node->infer_cursor_position_on_spawn();

   if (node_options_as_text.empty())
   {
      throw std::runtime_error(
         "DialogSystem::DialogSystem::activate_dialog_node_by_name: error: Expecting 1 or many options on "
            "node with node_identifier \"" + node_identifier + "\" but there are no options."
      );
   }
   else if (node_options_as_text.size() == 1)
   {
      // If dialog has only one option, spawn a basic dialog
      if (driver) driver->on_before_spawn_basic_dialog(node_pages_speaker);
      spawn_basic_dialog(
         driver ? driver->decorate_speaking_character_name(node_pages_speaker) : node_pages_speaker,
         //node_pages_speaker,
         node_pages
      );
      //append_to_dialog_roll(node_pages_speaker, node_pages[0]); // TODO: join(node_pages);
   }
   else // (node_options_as_text.size() > 1)
   {
      // If dialog has multiple options, spawn a "choice" dialog
      if (node_pages.size() != 1)
      {
         throw std::runtime_error(
            "DialogSystem::DialogSystem::activate_dialog_node_by_name: error: Expecting only 1 page for dialog "
               "node (with identifier \"" + node_identifier + "\") because it is going to be used to build a "
               "Choice dialog, however there are \"" + std::to_string(node_pages.size()) + "\" pages."
         );
      }
      if (driver) driver->on_before_spawn_choice_dialog(node_pages_speaker);
      spawn_choice_dialog(
         driver ? driver->decorate_speaking_character_name(node_pages_speaker) : node_pages_speaker,
         node_pages[0],
         node_options_as_text,
         cursor_position_on_spawn
      );
      //append_to_dialog_roll(node_pages_speaker, node_pages[0]); // TODO: join(node_pages);
   }
   return;
}

void DialogSystem::activate_dialog_node(AllegroFlare::DialogTree::Nodes::Base* dialog_node)
{
   if (!(dialog_node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_dialog_node]: error: guard \"dialog_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_dialog_node: error: guard \"dialog_node\" not met");
   }
   // TODO: Conaider that "active_dialog_node" is assigned inside each of the activate_TypeOfNode... methods and
   // this seems like a lot of duplicate logic (and also a bit brittle for refactoring and modification). Possibly
   // a better pattern is to set "active_dialog_node" here at the top (or at the bottom). I don't think any of
   // the methods in question have any specific behavior for assignment. I also think they are probably internal.
   // Also note that there is an assinment to "active_dialog_node" in the last else statement in this method.

   if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::EmitGameEvent::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::EmitGameEvent *as =
         static_cast<AllegroFlare::DialogTree::Nodes::EmitGameEvent*>(dialog_node);
      activate_EmitGameEvent_dialog_node(as);
   }
   else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::RawScriptLine::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::RawScriptLine *as =
         static_cast<AllegroFlare::DialogTree::Nodes::RawScriptLine*>(dialog_node);
      activate_RawScriptLine_dialog_node(as);
   }
   else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as =
         static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(dialog_node);
      activate_MultipageWithOptions_dialog_node(as);
   }
   else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog *as =
         static_cast<AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog*>(dialog_node);
      activate_YouGotAnItemDialog_dialog_node(as);
   }
   else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::Wait::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::Wait *as =
         static_cast<AllegroFlare::DialogTree::Nodes::Wait*>(dialog_node);
      activate_Wait_dialog_node(as);
   }
   else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ChapterTitle::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::ChapterTitle *as =
         static_cast<AllegroFlare::DialogTree::Nodes::ChapterTitle*>(dialog_node);
      activate_ChapterTitle_dialog_node(as);
   }
   else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::ExitDialog *as =
         static_cast<AllegroFlare::DialogTree::Nodes::ExitDialog*>(dialog_node);
      activate_ExitDialog_dialog_node(as);
   }
   else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitProgram::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::ExitProgram *as =
         static_cast<AllegroFlare::DialogTree::Nodes::ExitProgram*>(dialog_node);
      activate_ExitProgram_dialog_node(as);
   }
   else
   {
      active_dialog_node = dialog_node; // NOTE: Unsure if assignment should occour here
      bool handled = false;
      if (driver)
      {
         // TODO: Test calling on this "unhandled" case
         handled = driver->on_activate_dialog_node_type_unhandled(this, active_dialog_node);
      }

      // TODO: Test throwing of this when not handled
      if (!handled)
      {
         throw std::runtime_error(
            "DialogSystem::DialogSystem::activate_dialog_node: error: "
               "Unable to handle dialog node activation on type \""
               + active_dialog_node->get_type() + "\". A condition is not provided to handle this type."
         );
      }
   }
   return;
}

void DialogSystem::activate_dialog_node_by_name(std::string dialog_name)
{
   AllegroFlare::DialogTree::Nodes::Base *found_dialog_node = dialog_node_bank.find_node_by_name(dialog_name);
   if (!found_dialog_node)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DialogSystem::DialogSystem::activate_dialog_node_by_name",
         "Could not find node with identifier \"" + dialog_name + "\". "
            "The node bank contains " + std::to_string(dialog_node_bank.num_nodes()) + " nodes."
      );
   }
   active_dialog_node_name = dialog_name;
   activate_dialog_node(found_dialog_node);
   return;
}

void DialogSystem::advance_MultipageWithOptions_dialog_node(AllegroFlare::DialogTree::Nodes::MultipageWithOptions* node, int cursor_position)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::advance_MultipageWithOptions_dialog_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::advance_MultipageWithOptions_dialog_node: error: guard \"node\" not met");
   }
   if (!(node->has_options()))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::advance_MultipageWithOptions_dialog_node]: error: guard \"node->has_options()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::advance_MultipageWithOptions_dialog_node: error: guard \"node->has_options()\" not met");
   }
   if (!((cursor_position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::advance_MultipageWithOptions_dialog_node]: error: guard \"(cursor_position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::advance_MultipageWithOptions_dialog_node: error: guard \"(cursor_position >= 0)\" not met");
   }
   if (!((cursor_position < node->num_options())))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::advance_MultipageWithOptions_dialog_node]: error: guard \"(cursor_position < node->num_options())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::advance_MultipageWithOptions_dialog_node: error: guard \"(cursor_position < node->num_options())\" not met");
   }
   activate_dialog_option(cursor_position);
   return;
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
   if (!active_dialog_box->get_finished()) return;
   if (!active_dialog_node)
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::DialogSystem::DialogSystem::dialog_advance",
         "When advancing the dialog box, the dialog indicated it was finished. However, there was no corresponding "
            "active_dialog_node. This may be expected behavior in your case."
      );
   }

   if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as =
         static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(active_dialog_node);

      //if (as->num_options() == 0)
      //{
         //// If this dialog node has no options, then proceed to a "shutdown" state

         //// TODO: Replace this throw with a shutdown
         //throw std::runtime_error(
            //"DialogSystem::dialog_advance: error: Expecting 1 or many options for node named \""
               //+ active_dialog_node_name + "\" but there are no options."
         //);
      //}
      //else if (as->num_options() == 1)
      if (as->num_options() == 1)
      {
         // If the dialog node has 1 option, "activate" it
         int current_dialog_selection_choice = 0;
         advance_MultipageWithOptions_dialog_node(as, current_dialog_selection_choice);
         //activate_dialog_option(current_dialog_selection_choice);
      }
      else
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
            advance_MultipageWithOptions_dialog_node(as, current_dialog_selection_choice);
            //activate_dialog_option(current_dialog_selection_choice);
         }
      }
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::Wait::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::Wait *as =
         static_cast<AllegroFlare::DialogTree::Nodes::Wait*>(active_dialog_node);
      activate_dialog_node_by_name(as->get_next_node_identifier());
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ChapterTitle::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::ChapterTitle *as =
         static_cast<AllegroFlare::DialogTree::Nodes::ChapterTitle*>(active_dialog_node);
      activate_dialog_node_by_name(as->get_next_node_identifier());
   }
   else if (AllegroFlare::DialogTree::Nodes::RawScriptLine::TYPE)
   {
      // TODO: Throw when no driver is present
      if (driver) driver->on_raw_script_line_finished(this, active_dialog_box, active_dialog_node);
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
   {
      shutdown(); // TODO: Verify if this is a correct complete action for this event
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog::TYPE))
   {
      shutdown(); // TODO: Verify if this is a correct complete action for this event
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitProgram::TYPE))
   {
      event_emitter->emit_exit_game_event();
   }
   else
   {
      throw std::runtime_error(
         "DialogSystem::dialog_advance: error: Unable to handle case where dialog *box* is finished when "
            "the dialog *node* type \""
            + active_dialog_node->get_type() + "\". A condition is not provided to handle this type."
      );
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
         std::get<1>(as_multipage_with_options->get_option_num(selection_choice)); //.second;
      std::string node_option_type = node_option->get_type();

      std::map<std::string, std::function<void()>> types_map = {
         { AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE, [this, node_option]() {
            AllegroFlare::DialogTree::NodeOptions::ExitDialog* as_exit_dialog_node_option =
               static_cast<AllegroFlare::DialogTree::NodeOptions::ExitDialog*>(node_option);

            //event_emitter->emit_dialog_close_event();
            shutdown(); // TODO: See if this is a correct expectation for this event
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

void DialogSystem::spawn_basic_dialog(std::string speaking_character, std::vector<std::string> pages)
{
   switch_in_if_not();

   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_basic_dialog(
      speaking_character,
      //speaking_character,
      pages
   );

   // TODO: Address when and where a switch_in should occur
   //bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   //if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   //{
      //switch_in();
   //}
   return;
}

void DialogSystem::spawn_intertitle_dialog(std::string text)
{
   switch_in_if_not();

   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_intertitle_dialog(
      text
      //speaking_character,
      //pages
   );

   // TODO: Address when and where a switch_in should occur
   //bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   //if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   //{
      //switch_in();
   //}
   return;
}

void DialogSystem::spawn_text_messages_dialog(std::vector<std::tuple<std::string, std::string, float>> messages)
{
   switch_in_if_not();

   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_text_messages_dialog(
      messages
      //speaking_character,
      //speaking_character,
      //pages
   );

   // TODO: Address when and where a switch_in should occur
   //bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   //if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   //{
      //switch_in();
   //}
   return;
}

void DialogSystem::spawn_wait_dialog(float duration_seconds)
{
   switch_in_if_not();

   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_wait_dialog(duration_seconds);

   // TODO: Address when and where a switch_in should occur
   //bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   //if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   //{
      //switch_in();
   //}
   return;
}

void DialogSystem::spawn_chapter_title_dialog(std::string title_text, float duration_seconds)
{
   switch_in_if_not();

   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_chapter_title_dialog(
      title_text,
      duration_seconds
   );

   // TODO: Address when and where a switch_in should occur
   //bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   //if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   //{
      //switch_in();
   //}
   return;
}

void DialogSystem::spawn_you_got_an_item_dialog(std::string item_name, std::string item_bitmap_identifier)
{
   switch_in_if_not();

   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_you_got_an_item_dialog(
      item_name,
      item_bitmap_identifier
   );

   return;
}

void DialogSystem::spawn_character_feature_dialog(std::string character_name, std::string character_description, std::string character_image_identifier, float duration_seconds)
{
   switch_in_if_not();

   // TODO: Use a DEFAULT_DURATION_SECONDS
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog
                                                    // And/or address concerns that derived dialog be deleted proper

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_character_feature_dialog(
      //driver ? driver->decorate_speaking_character(speaking_character) : speaking_character,
      character_name,
      character_description,
      character_image_identifier,
      duration_seconds
   );

   // TODO: Address when and where a switch_in should occur
   //bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   //if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   //{
      //switch_in();
   //}
   return;
}

void DialogSystem::spawn_choice_dialog(std::string speaking_character, std::string prompt, std::vector<std::string> options, int cursor_position_on_spawn)
{
   if (!((cursor_position_on_spawn >= 0)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::spawn_choice_dialog]: error: guard \"(cursor_position_on_spawn >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::spawn_choice_dialog: error: guard \"(cursor_position_on_spawn >= 0)\" not met");
   }
   if (!((cursor_position_on_spawn < options.size())))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::spawn_choice_dialog]: error: guard \"(cursor_position_on_spawn < options.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::spawn_choice_dialog: error: guard \"(cursor_position_on_spawn < options.size())\" not met");
   }
   switch_in_if_not();

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
         dialog_box_factory.create_choice_dialog(
            //driver ? driver->decorate_speaking_character_name(speaking_character) : speaking_character,
            speaking_character,
            prompt,
            options_that_are_also_values,
            cursor_position_on_spawn
         );
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
   //bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   //if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   //{
      //switch_in();
   //}
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
   //if (active_dialog_node_state) active_dialog_node_state->update(); // TODO: Pass down time_now

   // TODO: Consider moving this block above with the normal update
   if (active_dialog_box && active_dialog_box->ready_to_auto_advance()) dialog_advance();
   if (driver) driver->update();

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
   if (!(driver))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::render]: error: guard \"driver\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::render: error: guard \"driver\" not met");
   }
   if (driver) driver->on_render();

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
      dialog_box_renderer.set_standard_dialog_box_x(standard_dialog_box_x);
      dialog_box_renderer.set_standard_dialog_box_y(standard_dialog_box_y);
      dialog_box_renderer.set_standard_dialog_box_width(standard_dialog_box_width);
      dialog_box_renderer.set_standard_dialog_box_height(standard_dialog_box_height);
      dialog_box_renderer.render();
   }
}

bool DialogSystem::a_dialog_is_active()
{
   return (active_dialog_box != nullptr);
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

bool DialogSystem::shutdown()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::shutdown]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::shutdown: error: guard \"initialized\" not met");
   }
   if (!(driver))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::shutdown]: error: guard \"driver\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::shutdown: error: guard \"driver\" not met");
   }
   if (!(switched_in))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::shutdown]: error: guard \"switched_in\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::shutdown: error: guard \"switched_in\" not met");
   }
   switch_out();
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


