

#include <AllegroFlare/DialogSystem/DialogSystem.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/YAMLLoader.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
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


DialogSystem::DialogSystem(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::string standard_dialog_box_font_name, int standard_dialog_box_font_size)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , dialog_node_bank({})
   , active_dialog_box(nullptr)
   , active_dialog_node(nullptr)
   , active_dialog_node_name("[unset-active_dialog_node_name]")
   , switched_in(false)
   , standard_dialog_box_font_name(standard_dialog_box_font_name)
   , standard_dialog_box_font_size(standard_dialog_box_font_size)
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


AllegroFlare::DialogTree::NodeBank DialogSystem::get_dialog_node_bank() const
{
   return dialog_node_bank;
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
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   yaml_loader.load_file(filename);
   dialog_node_bank = yaml_loader.get_node_bank();
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

void DialogSystem::spawn_named_dialog(std::string dialog_name)
{
   active_dialog_node = dialog_node_bank.find_node_by_name(dialog_name);
   active_dialog_node_name = dialog_name;

   // NOTE: The branching below is not needed because find_node_by_name will throw if not found
   //if (!active_dialog_node)
   //{
      //throw std::runtime_error(
         //"DialogSystem::spawn_named_dialog: error: no dialog exists with the name \"" + dialog_name + "\""
      //);
   //}
   //else
   //{
   std::string node_pages_speaker = active_dialog_node->get_speaker();
   std::vector<std::string> node_pages = active_dialog_node->get_pages();
   std::vector<std::string> node_options_as_text = active_dialog_node->build_options_as_text();

   if (node_options_as_text.empty())
   {
      throw std::runtime_error(
         "DialogSystem::spawn_named_dialog: error: Expecting 1 or many options for node named \""
            + dialog_name + "\" but there are no options."
      );
   }
   else if (node_options_as_text.size() == 1)
   {
      // If dialog has only one option, spawn a basic dialog
      spawn_basic_dialog(node_pages);
   }
   else // (node_options_as_text.size() > 1)
   {
      // TODO: Here, if dialog has multiple options, spawn a "choice" dialog
   }
   return;
}

void DialogSystem::spawn_basic_dialog(std::vector<std::string> pages)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog_box) delete active_dialog_box; // TODO: address concern that this could clobber an active dialog

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog_box = dialog_box_factory.create_basic_dialog(pages);

   // TODO: Address when and where a switch_in should occur
   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      switch_in();
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
   if (active_dialog_box)
   {
      AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(font_bin, bitmap_bin, active_dialog_box);
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
         if (active_dialog_node->num_options() == 0)
         {
            // If this dialog node has no options, then proceed to a "shutdown" state

            // TODO: Replace this throw with a shutdown
            throw std::runtime_error(
               "DialogSystem::dialog_advance: error: Expecting 1 or many options for node named \""
                  + active_dialog_node_name + "\" but there are no options."
            );
         }
         else if (active_dialog_node->num_options() == 1)
         {
            // If the dialog node has 1 option, "activate" it
            int current_dialog_selection_choice = 0;
            activate_dialog_option(current_dialog_selection_choice);
         }
         else // if (active_dialog_node.num_options() > 1)
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
   if (!((selection_choice >= 0)))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_dialog_option]: error: guard \"(selection_choice >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_dialog_option: error: guard \"(selection_choice >= 0)\" not met");
   }
   if (!((selection_choice < active_dialog_node->num_options())))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::activate_dialog_option]: error: guard \"(selection_choice < active_dialog_node->num_options())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::activate_dialog_option: error: guard \"(selection_choice < active_dialog_node->num_options())\" not met");
   }
   // TODO: Consider case where dialog node has no (empty) options

   AllegroFlare::DialogTree::NodeOptions::Base* node_option =
      active_dialog_node->get_option_num(selection_choice).second;
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
         spawn_named_dialog(target_node_name);
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
   delete active_dialog_box; // TODO: Consider a less intrusive soft delete (with cleanup during update)
   active_dialog_box = nullptr;
   active_dialog_node = nullptr;
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
   if (active_dialog_box) active_dialog_box->move_cursor_position_up();
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
   if (active_dialog_box) active_dialog_box->move_cursor_position_down();
   return;
}

void DialogSystem::move_dialog_cursor_position_left()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::move_dialog_cursor_position_left]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::move_dialog_cursor_position_left: error: guard \"initialized\" not met");
   }
   if (active_dialog_box) active_dialog_box->move_cursor_position_left();
   return;
}

void DialogSystem::move_dialog_cursor_position_right()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::move_dialog_cursor_position_right]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::move_dialog_cursor_position_right: error: guard \"initialized\" not met");
   }
   if (active_dialog_box) active_dialog_box->move_cursor_position_right();
   return;
}


} // namespace DialogSystem
} // namespace AllegroFlare


