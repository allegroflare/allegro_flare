

#include <AllegroFlare/Prototypes/FixedRoom2D/DialogSystem.hpp>

#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CloseDialog.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EventNames.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


DialogSystem::DialogSystem(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , active_dialog(nullptr)
   , initialized(false)
{
}


DialogSystem::~DialogSystem()
{
}


void DialogSystem::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void DialogSystem::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (active_dialog) active_dialog->update();
   return;
}

void DialogSystem::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   // render the active dialog
   if (active_dialog)
   {
      AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(font_bin, bitmap_bin, active_dialog);
      dialog_box_renderer.render();
   }
}

void DialogSystem::process_game_event(AllegroFlare::GameEvent* game_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "process_game_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::INTERACTION_EVENT_NAME))
   //{
      //process_interaction_event(game_event->get_data());
   //}
   //else if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::SCRIPT_EVENT_NAME))
   //{
      //process_script_event(game_event->get_data());
   //}
   if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::DIALOG_EVENT_NAME))
   {
      process_dialog_event(game_event->get_data());
   }
   //else if (game_event->is_type("unpause_game"))
   //{
      //unpause_game();
   //}
   //else if (game_event->is_type("pause_game"))
   //{
      //pause_game();
   //}
   else
   {
      std::cout << "[FixedRoom2D::FixedRoom2D::process_subscribed_to_game_event]: "
                << "error: unexpected game_event type "
                << "\"" << game_event->get_type() << "\". Doing nothing (except outputting this error)."
                << std::endl;
   }
   return;
}

void DialogSystem::process_dialog_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "process_dialog_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   using namespace AllegroFlare::Prototypes::FixedRoom2D;

   if (!game_event_data)
   {
      std::cout << "ERROR: A weird error occurred. In FixedRoom2D/FixedRoom2D::process_dialog_event, sxpecting "
                << "script_event_data to be valid but it is nullptr" << std::endl;
      return;
   }
   else
   {
      if (game_event_data->is_type(DialogEventDatas::CloseDialog::TYPE))
      {
         DialogEventDatas::CloseDialog* close_dialog_event_data =
            static_cast<DialogEventDatas::CloseDialog*>(game_event_data);

         // HERE:
         // TODO: vaildate active_dialog is dialog in event_data (TODO in the future: ensure it is a dialog
         //   in the stack of dialogs.)
         shutdown_dialog();
         // NOTE: artifact from when dialog code was in FixedRoom2D/FixedRoom2D:
         // resume_all_rooms();
         // NOTE: artifact from when dialog code was in FixedRoom2D/FixedRoom2D:
         //if (script_runner.get_paused_for_dialog_to_finish()) script_runner.play_or_resume();
      }
      else
      {
         std::cout << "[FixedRoom2D::FixedRoom2D::process_dialog_event]: error: "
                   << "Unknown game_event_data type "
                   << "\"" << game_event_data->get_type() << "\""
                   << std::endl;
      }
   }
   return;
}

void DialogSystem::dialog_advance()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "dialog_advance" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active()) return;
   if (!active_dialog) return;

   // TODO: modify this branching notation to a map<string, function>
   // TODO: account for different dialog types
   if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::Basic::TYPE))
   {
      dynamic_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(active_dialog)->advance();
   }
   else if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::YouGotAnItem::TYPE))
   {
      dynamic_cast<AllegroFlare::Elements::DialogBoxes::YouGotAnItem*>(active_dialog)->advance();
   }
   else if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::YouGotEvidence::TYPE))
   {
      dynamic_cast<AllegroFlare::Elements::DialogBoxes::YouGotEvidence*>(active_dialog)->advance();
   }
   else
   {
      // TODO: test this condition
      std::stringstream error_message;
      error_message << "AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_advance: ERROR: "
                    << "Unrecognized dialog of type \"" << active_dialog->get_type() << "\". Aborting.";
      throw std::runtime_error(error_message.str());
   }
   return;
}

void DialogSystem::dialog_cursor_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "dialog_cursor_up" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active()) return;
   if (!active_dialog) return;

   // TODO: modify this branching notation to a map<string, function>
   // TODO: account for different dialog types
   if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::Basic::TYPE))
   {
      // do nothing
   }
   else
   {
      // TODO: test this condition
      std::stringstream error_message;
      error_message << "AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_cursor_up: ERROR: "
                    << "Unrecognized dialog of type \"" << active_dialog->get_type() << "\". Aborting.";
      throw std::runtime_error(error_message.str());
   }
   return;
}

void DialogSystem::dialog_cursor_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "dialog_cursor_down" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active()) return;
   if (!active_dialog) return;

   // TODO: modify this branching notation to a map<string, function>
   // TODO: account for different dialog types
   if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::Basic::TYPE))
   {
      // do nothing
   }
   else
   {
      // TODO: test this condition
      std::stringstream error_message;
      error_message << "AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_cursor_down: ERROR: "
                    << "Unrecognized dialog of type \"" << active_dialog->get_type() << "\". Aborting.";
      throw std::runtime_error(error_message.str());
   }
   return;
}

bool DialogSystem::dialog_is_finished()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "dialog_is_finished" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!active_dialog) return true;

   // TODO: modify this branching notation to a map<string, function>
   // TODO: account for different dialog types
   if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::Basic::TYPE))
   {
      return dynamic_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(active_dialog)->get_finished();
   }
   else if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::YouGotAnItem::TYPE))
   {
      return dynamic_cast<AllegroFlare::Elements::DialogBoxes::YouGotAnItem*>(active_dialog)->get_finished();
   }
   else if (active_dialog->is_type(AllegroFlare::Elements::DialogBoxes::YouGotEvidence::TYPE))
   {
      return dynamic_cast<AllegroFlare::Elements::DialogBoxes::YouGotEvidence*>(active_dialog)->get_finished();
   }
   else
   {
      // TODO: test this condition
      std::stringstream error_message;
      error_message << "AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_is_finished: ERROR: "
                    << "Unrecognized dialog of type \"" << active_dialog->get_type() << "\". Aborting.";
      throw std::runtime_error(error_message.str());
   }
   return true;
}

bool DialogSystem::shutdown_dialog()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "shutdown_dialog" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!active_dialog) return false;
   delete active_dialog;
   active_dialog = nullptr;
   return true;
}

void DialogSystem::move_cursor_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "move_cursor_up" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active()) inventory_window.move_cursor_up();
   if (active_dialog) dialog_cursor_up();
   return;
}

void DialogSystem::move_cursor_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "move_cursor_down" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active()) inventory_window.move_cursor_down();
   if (active_dialog) dialog_cursor_down();
   return;
}

ALLEGRO_FONT* DialogSystem::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "DialogSystem" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   return font_bin->auto_get("Inter-Medium.ttf -52");
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


