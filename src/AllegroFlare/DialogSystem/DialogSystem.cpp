

#include <AllegroFlare/DialogSystem/DialogSystem.hpp>

#include <AllegroFlare/DialogSystem/DialogEventDatas/CloseDialog.hpp>
#include <AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotAnItemDialog.hpp>
#include <AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotEvidenceDialog.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <allegro5/allegro_primitives.h>
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
   , active_dialog(nullptr)
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


AllegroFlare::Elements::DialogBoxes::Base* &DialogSystem::get_active_dialog_ref()
{
   return active_dialog;
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
      error_message << "[DialogSystem::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::render: error: guard \"initialized\" not met");
   }
   if (active_dialog)
   {
      AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(font_bin, bitmap_bin, active_dialog);
      dialog_box_renderer.set_standard_dialog_box_font_name(standard_dialog_box_font_name);
      dialog_box_renderer.set_standard_dialog_box_font_size(standard_dialog_box_font_size);
      dialog_box_renderer.render();
   }
}

void DialogSystem::process_ALLEGRO_FLARE_EVENT_DIALOG_event(AllegroFlare::GameEvent* dialog_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::process_ALLEGRO_FLARE_EVENT_DIALOG_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::process_ALLEGRO_FLARE_EVENT_DIALOG_event: error: guard \"initialized\" not met");
   }
   if (!(dialog_event))
   {
      std::stringstream error_message;
      error_message << "[DialogSystem::process_ALLEGRO_FLARE_EVENT_DIALOG_event]: error: guard \"dialog_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::process_ALLEGRO_FLARE_EVENT_DIALOG_event: error: guard \"dialog_event\" not met");
   }
   //using namespace AllegroFlare::DialogSystem;
   // NOTE: there is currently no way to know if "game_event_data" comes from a DIALOG_EVENT_NAME type.
   // It might not be important:
   // if (!game_event_data->is_type(FixedRoom2D::EventNames::DIALOG_EVENT_NAME))

   AllegroFlare::GameEventDatas::Base* dialog_event_data = dialog_event->get_data();

   if (!dialog_event_data)
   {
      std::cout << "ERROR: A weird error occurred. In FixedRoom2D/DialogSystem::process_dialog_event, expecting "
                << "dialog_event_data to be valid but it is nullptr" << std::endl;
      return;
   }


   // Cases to consider handling (if you might not otherwise simply rely on GameEventData):
   //case ALLEGRO_FLARE_EVENT_DIALOG_OPEN:
   //case ALLEGRO_FLARE_EVENT_DIALOG_ADVANCE:
   //case ALLEGRO_FLARE_EVENT_DIALOG_CLOSE:
   //case ALLEGRO_FLARE_EVENT_DIALOG_SWITCH_IN:
   //case ALLEGRO_FLARE_EVENT_DIALOG_SWITCH_OUT:


   //AllegroFlare::GameEventDatas::Base* game_event_data =
      //static_cast<AllegroFlare::GameEventDatas::Base*>(raw_data1_assumed_to_be_game_event_data);



   // handle *all* the different DIALOG_EVENT_NAME types

   if (dialog_event_data->is_type(AllegroFlare::DialogSystem::DialogEventDatas::CloseDialog::TYPE))
   {
      shutdown_dialog(); // TODO: address the difference between "shutdown_dialog" and
                         // a theoretical "destroy_and_create_a_new_dialog_simultaniously"
   }
   else if (dialog_event_data->is_type(AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotEvidenceDialog::TYPE))
   {
      DialogEventDatas::CreateYouGotEvidenceDialog *local_dialog_event_data =
         static_cast<DialogEventDatas::CreateYouGotEvidenceDialog*>(dialog_event_data);

      spawn_you_got_new_evidence_dialog(
         local_dialog_event_data->get_evidence_name(),
         local_dialog_event_data->get_evidence_bitmap_identifier()
      );
   }
   else if (dialog_event_data->is_type(AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotAnItemDialog::TYPE))
   {
      DialogEventDatas::CreateYouGotAnItemDialog *local_dialog_event_data =
         static_cast<DialogEventDatas::CreateYouGotAnItemDialog*>(dialog_event_data);

      spawn_you_got_an_item_dialog(
         local_dialog_event_data->get_item_name(),
         local_dialog_event_data->get_item_bitmap_identifier()
      );
   }
   else
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::process_dialog_event]: error: "
                    << "Unhandled dialog_event_data type \"" << dialog_event_data->get_type() << "\". Aborting.";
      throw std::runtime_error(error_message.str());
   }

   return;
}

void DialogSystem::emit_dialog_switch_in_event()
{
   event_emitter->emit_game_event(AllegroFlare::GameEvent(
      //AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_IN_NAME
      //AllegroFlare::EventNames::ALEGRO_FLARE_EVENT_DIALOG_SWITCH_IN_NAME
      ALLEGRO_FLARE_EVENT_DIALOG_SWITCH_IN_NAME
   ));
   return;
}

void DialogSystem::emit_dialog_switch_out_event()
{
   event_emitter->emit_game_event(AllegroFlare::GameEvent(
      //AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_OUT_NAME
      //AllegroFlare::EventNames::ALLEGRO_FLARE_EVENT_DIALOG_SWITCH_OUT_NAME
      ALLEGRO_FLARE_EVENT_DIALOG_SWITCH_OUT_NAME
   ));
   return;
}

void DialogSystem::spawn_basic_dialog(std::vector<std::string> pages)
{
   bool a_dialog_existed_before = a_dialog_is_active();
   if (active_dialog) delete active_dialog; // TODO: address concern that this could clobber an active dialog

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
   active_dialog = dialog_box_factory.create_basic_dialog(pages);

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
      error_message << "[DialogSystem::dialog_advance]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::dialog_advance: error: guard \"initialized\" not met");
   }
   //if (inventory_window.get_active()) return;
   if (!active_dialog) return;

   // TODO: modify this branching notation to a map<string, function>
   // TODO: account for different dialog types
   // TODO: Add "advance" to DialogBoxes::Base, or, add custom callback to handle types
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
      error_message << "[DialogSystem::dialog_cursor_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::dialog_cursor_up: error: guard \"initialized\" not met");
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
      error_message << "[DialogSystem::dialog_is_finished]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::dialog_is_finished: error: guard \"initialized\" not met");
   }
   if (!active_dialog) return true;

   // TODO: modify this branching notation to a map<string, function>
   // TODO: account for different dialog types
   // TODO: Consider moving "get_finished" as override function on base class
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
      error_message << "[DialogSystem::shutdown_dialog]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::shutdown_dialog: error: guard \"initialized\" not met");
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
      error_message << "[DialogSystem::move_cursor_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::move_cursor_up: error: guard \"initialized\" not met");
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
      error_message << "[DialogSystem::move_cursor_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogSystem::move_cursor_down: error: guard \"initialized\" not met");
   }
   //if (inventory_window.get_active()) inventory_window.move_cursor_down();
   if (active_dialog) dialog_cursor_down();
   return;
}


} // namespace DialogSystem
} // namespace AllegroFlare


