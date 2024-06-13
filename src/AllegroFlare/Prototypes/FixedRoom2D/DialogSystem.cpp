

#include <AllegroFlare/Prototypes/FixedRoom2D/DialogSystem.hpp>

#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CloseDialog.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CreateYouGotAnItemDialog.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CreateYouGotEvidenceDialog.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EventNames.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


DialogSystem::DialogSystem(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::string standard_dialog_box_font_name, int standard_dialog_box_font_size)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , active_dialog(nullptr)
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


std::string DialogSystem::get_standard_dialog_box_font_name() const
{
   return standard_dialog_box_font_name;
}


int DialogSystem::get_standard_dialog_box_font_size() const
{
   return standard_dialog_box_font_size;
}


AllegroFlare::Elements::DialogBoxes::Base* &DialogSystem::get_active_dialog_ref()
{
   return active_dialog;
}


void DialogSystem::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
}

void DialogSystem::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
}

void DialogSystem::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::set_event_emitter]: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
}

void DialogSystem::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize]: error: guard \"event_emitter\" not met");
   }
   initialized = true;
   return;
}

void DialogSystem::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::update]: error: guard \"initialized\" not met");
   }
   if (active_dialog) active_dialog->update();
   return;
}

bool DialogSystem::a_dialog_is_active()
{
   return (active_dialog != nullptr);
}

void DialogSystem::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::render]: error: guard \"initialized\" not met");
   }
   if (active_dialog)
   {
      AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(font_bin, bitmap_bin, active_dialog);
      dialog_box_renderer.set_standard_dialog_box_font_name(standard_dialog_box_font_name);
      dialog_box_renderer.set_standard_dialog_box_font_size(standard_dialog_box_font_size);
      dialog_box_renderer.render();
   }
}

void DialogSystem::process_dialog_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::process_dialog_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::process_dialog_event]: error: guard \"initialized\" not met");
   }
   using namespace AllegroFlare::Prototypes::FixedRoom2D;
   // NOTE: there is currently no way to know if "game_event_data" comes from a DIALOG_EVENT_NAME type.
   // It might not be important:
   // if (!game_event_data->is_type(FixedRoom2D::EventNames::DIALOG_EVENT_NAME))

   if (!game_event_data)
   {
      std::cout << "ERROR: A weird error occurred. In FixedRoom2D/DialogSystem::process_dialog_event, expecting "
                << "script_event_data to be valid but it is nullptr" << std::endl;
      return;
   }

   // handle *all* the different DIALOG_EVENT_NAME types

   if (game_event_data->is_type(DialogEventDatas::CloseDialog::TYPE))
   {
      shutdown_dialog(); // TODO: address the difference between "shutdown_dialog" and
                         // a theoretical "destroy_and_create_a_new_dialog_simultaniously"
   }
   else if (game_event_data->is_type(DialogEventDatas::CreateYouGotEvidenceDialog::TYPE))
   {
      DialogEventDatas::CreateYouGotEvidenceDialog *dialog_event_data =
         static_cast<DialogEventDatas::CreateYouGotEvidenceDialog*>(game_event_data);

      spawn_you_got_new_evidence_dialog(
         dialog_event_data->get_evidence_name(),
         dialog_event_data->get_evidence_bitmap_identifier()
      );
   }
   else if (game_event_data->is_type(DialogEventDatas::CreateYouGotAnItemDialog::TYPE))
   {
      DialogEventDatas::CreateYouGotAnItemDialog *dialog_event_data =
         static_cast<DialogEventDatas::CreateYouGotAnItemDialog*>(game_event_data);

      spawn_you_got_an_item_dialog(
         dialog_event_data->get_item_name(),
         dialog_event_data->get_item_bitmap_identifier()
      );
   }
   else
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::process_dialog_event]: error: "
                    << "Unhandled game_event_data type \"" << game_event_data->get_type() << "\". Aborting.";
      throw std::runtime_error(error_message.str());
   }

   return;
}

void DialogSystem::emit_dialog_switch_in_event()
{
   event_emitter->emit_game_event(AllegroFlare::GameEvent(
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_IN_NAME
   ));
   return;
}

void DialogSystem::emit_dialog_switch_out_event()
{
   event_emitter->emit_game_event(AllegroFlare::GameEvent(
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_OUT_NAME
   ));
   return;
}

void DialogSystem::spawn_basic_dialog(std::vector<std::string> pages)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog) delete active_dialog; // TODO: address concern that this could clobber an active dialog

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog = dialog_box_factory.create_basic_dialog("", pages);

   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      emit_dialog_switch_in_event();
   }
   return;
}

void DialogSystem::spawn_you_got_an_item_dialog(std::string item_name, std::string item_bitmap_identifier)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog) delete active_dialog; // TODO: address concern that this could clobber an active dialog

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog = dialog_box_factory.create_you_got_an_item_dialog(
         "Keys",
         "key-keychain-house-keys-door-photo-pixabay-25.png"
      );

   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      emit_dialog_switch_in_event();
   }
   return;
}

void DialogSystem::spawn_you_got_new_evidence_dialog(std::string evidence_name, std::string evidence_bitmap_identifier)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog) delete active_dialog; // TODO: address concern that this could clobber an active dialog

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog = dialog_box_factory.create_you_got_new_evidence_dialog(
         evidence_name,
         evidence_bitmap_identifier
      );

   bool a_new_dialog_was_created_and_dialog_system_is_now_active = !a_dialog_existed_before;
   if (a_new_dialog_was_created_and_dialog_system_is_now_active)
   {
      emit_dialog_switch_in_event();
   }
   return;
}

void DialogSystem::dialog_advance()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_advance]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_advance]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_cursor_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_cursor_up]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_cursor_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_cursor_down]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_is_finished]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::dialog_is_finished]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::shutdown_dialog]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::shutdown_dialog]: error: guard \"initialized\" not met");
   }
   std::cout << "- in DialogSystem::shutdown_dialog()" << std::endl;
   if (!active_dialog) return false;
   delete active_dialog;
   active_dialog = nullptr;
   emit_dialog_switch_out_event();
   return true;
}

void DialogSystem::move_cursor_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::move_cursor_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::move_cursor_up]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::move_cursor_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::move_cursor_down]: error: guard \"initialized\" not met");
   }
   //if (inventory_window.get_active()) inventory_window.move_cursor_down();
   if (active_dialog) dialog_cursor_down();
   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


