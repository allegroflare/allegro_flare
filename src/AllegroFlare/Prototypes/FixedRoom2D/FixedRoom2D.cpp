

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/InteractionEventData.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/SpawnDialogEventData.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/CollectItemEventData.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


FixedRoom2D::FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::AudioController* audio_controller)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , audio_controller(audio_controller)
   , af_inventory({})
   , inventory_window({})
   , flags({})
   , entity_dictionary({})
   , script_dictionary({})
   , script_runner({})
   , entity_collection_helper({})
   , room({})
   , initialized(false)
   , active_dialog(nullptr)
{
}


FixedRoom2D::~FixedRoom2D()
{
}


void FixedRoom2D::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void FixedRoom2D::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void FixedRoom2D::set_audio_controller(AllegroFlare::AudioController* audio_controller)
{
   this->audio_controller = audio_controller;
}


void FixedRoom2D::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   room.set_font_bin(font_bin);
   this->font_bin = font_bin;
   return;
}

void FixedRoom2D::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "FixedRoom2D" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "FixedRoom2D" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "FixedRoom2D" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(audio_controller))
      {
         std::stringstream error_message;
         error_message << "FixedRoom2D" << "::" << "initialize" << ": error: " << "guard \"audio_controller\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(bitmap_bin);

   inventory_window.set_font_bin(font_bin);
   inventory_window.set_bitmap_bin(bitmap_bin);
   inventory_window.set_af_inventory(&af_inventory);

   entity_dictionary = {
      { "door", entity_factory.create_entity(
            "download-door-png-transparent-image-and-clipart-3.png", 1400, 800, 0.85, "Door", "observe_door") },
      { "chair", entity_factory.create_entity(
            "wooden-chair-png-transparent-image-pngpix-0.png", 600, 800, 0.168, "Chair", "signal_hello") },
      { "table", entity_factory.create_entity(
            "download-wooden-table-png-image-png-image-pngimg-3.png", 900, 800, 0.4, "table", "observe_table") },
      { "keys", entity_factory.create_entity(
            "key-keychain-house-keys-door-photo-pixabay-25.png", 940, 590, 0.05, "keys", "collect_keys") },
   };

   script_dictionary = {
      { "observe_door", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Just a regular door. | It appears to be locked, though."
      })},
      { "signal_hello", AllegroFlare::Prototypes::FixedRoom2D::Script({"SIGNAL: Hello!"}) },
      { "spawn_dialog", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: This was a scripted dialog!"
      })},
      { "collect_keys", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "COLLECT: keys"
      })},
      { "observe_table", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Hmm. Nothing interesting on this table."
      })},
   };

   entity_collection_helper.set_entity_dictionary(&entity_dictionary);

   room.set_font_bin(font_bin);
   room.set_event_emitter(event_emitter);
   room.set_entity_dictionary(&entity_dictionary);
   room.initialize();

   script_runner.set_audio_controller(audio_controller);
   script_runner.set_af_inventory(&af_inventory);
   script_runner.set_event_emitter(event_emitter);
   script_runner.set_inventory_window(&inventory_window);
   script_runner.set_script_dictionary(&script_dictionary);
   script_runner.set_flags(&flags);

   initialized = true;
   return;
}

void FixedRoom2D::update()
{
   room.update();
   if (active_dialog) active_dialog->update();
   inventory_window.update();
   return;
}

void FixedRoom2D::render()
{
   room.render();
   if (active_dialog)
   {
      AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(font_bin, bitmap_bin, active_dialog);
      dialog_box_renderer.render();
   }
   inventory_window.render();

   return;
}

void FixedRoom2D::process_interaction_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   if (game_event_data && game_event_data->get_type() == "InteractionEventData")
   {
      AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData* interaction_event_data =
          static_cast<AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData*>(game_event_data);

      std::string name = entity_collection_helper.find_dictionary_name_of_entity_that_cursor_is_now_over();
      if (name.empty())
      {
         // dialog "there is nothing here"
      }
      else
      {
         AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* interacting_entity = entity_dictionary.at(name);
         std::string script = interacting_entity->get_on_cursor_interact_script_name();
         script_runner.load_script_by_dictionary_name(script);
         script_runner.play_current_script_line();
      }
   }
   else
   {
      std::cout << "Expecting game_event_data to be present but it is a nullptr" << std::endl;
   }
   return;
}

void FixedRoom2D::process_script_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   using namespace AllegroFlare::Prototypes::FixedRoom2D;

   if (!game_event_data)
   {
      // weird error;
      std::cout << "A weird error occurred. Expecting script_event_data to be valid but it is nullptr" << std::endl;
      return;
   }
   else
   {
      if (game_event_data->get_type() == "SpawnDialogEventData")
      {
         AllegroFlare::Prototypes::FixedRoom2D::SpawnDialogEventData* spawn_dialog_event_data =
             static_cast<AllegroFlare::Prototypes::FixedRoom2D::SpawnDialogEventData*>(game_event_data);
         std::vector<std::string> pages = spawn_dialog_event_data->get_dialog_pages();

         AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
         if (active_dialog) delete active_dialog;

         active_dialog = dialog_box_factory.create_basic_dialog(pages);
         room.suspend();
         //spawn_dialog_box();
      }
      if (game_event_data->get_type() == "CollectItemEventData")
      {
         AllegroFlare::Prototypes::FixedRoom2D::CollectItemEventData* collect_item_event_data =
             static_cast<AllegroFlare::Prototypes::FixedRoom2D::CollectItemEventData*>(game_event_data);

         AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;
         if (active_dialog) delete active_dialog;

         active_dialog = dialog_box_factory.create_you_got_an_item_dialog(
               "Keys",
               "key-keychain-house-keys-door-photo-pixabay-25.png"
            );
         room.suspend();
         // TODO: spawn dialog
      }
      else
      {
         std::cout << "Unknown event_data type for SCRIPT_EVENT_NAME" << std::endl;
      }
   }
   return;
}

void FixedRoom2D::show_inventory()
{
   inventory_window.show();
   room.suspend();
   return;
}

void FixedRoom2D::hide_inventory()
{
   inventory_window.hide();
   room.resume();
   return;
}

void FixedRoom2D::toggle_inventory()
{
   if (inventory_window.get_active()) hide_inventory();
   else show_inventory();
   return;
}

void FixedRoom2D::spawn_dialog_box()
{
   if (inventory_window.get_active()) return;

   AllegroFlare::Elements::DialogBoxFactory dialog_box_factory;

   if (active_dialog) delete active_dialog;
   {
      active_dialog = dialog_box_factory.create_basic_test_dialog();
      room.suspend();
   }

   return;
}

void FixedRoom2D::advance_dialog()
{
   if (inventory_window.get_active()) return;

   if (!active_dialog) return;
   if (active_dialog->is_type("Basic"))
   {
      dynamic_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(active_dialog)->next_page();
   }
   return;
}

bool FixedRoom2D::dialog_is_finished()
{
   if (!active_dialog) return true;
   if (active_dialog->is_type("Basic"))
   {
      return dynamic_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(active_dialog)->get_finished();
   }
   return true;
}

bool FixedRoom2D::shutdown_dialog()
{
   if (!active_dialog) return false;
   delete active_dialog;
   active_dialog = nullptr;
   return true;
}

void FixedRoom2D::activate_primary_action()
{
   if (inventory_window.get_active())
   {
      // inventory_window.select_item_currently_under_cursor();
   }
   else if (active_dialog)
   {
      advance_dialog();
      if (dialog_is_finished())
      {
         shutdown_dialog();
         room.resume();
      }
   }
   else if (!room.get_suspended())
   {
      room.interact_with_item_under_cursor();
   }

   return;
}

void FixedRoom2D::move_cursor_up()
{
   if (inventory_window.get_active()) inventory_window.move_cursor_up();
   return;
}

void FixedRoom2D::move_cursor_down()
{
   if (inventory_window.get_active()) inventory_window.move_cursor_down();
   return;
}

void FixedRoom2D::move_cursor_left()
{
   if (inventory_window.get_active()) inventory_window.move_cursor_left();
   return;
}

void FixedRoom2D::move_cursor_right()
{
   if (inventory_window.get_active()) inventory_window.move_cursor_right();
   return;
}

void FixedRoom2D::move_cursor(float distance_x, float distance_y)
{
   if (!room.get_suspended())
   { 
      room.move_cursor(distance_x, distance_y);
   }
   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


