

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <AllegroFlare/InventoryDictionaryItems/WithAttributes.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ConfigurationFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ConfigurationLoader.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CloseDialog.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EventNames.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/InteractionEventData.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectEvidence.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectItem.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/EnterRoom.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/SpawnDialog.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


FixedRoom2D::FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , inventory_index()
   , af_inventory({})
   , flags({})
   , entity_dictionary({})
   , room_dictionary({})
   , entity_room_associations({})
   , script_dictionary({})
   , script_runner({})
   , entity_collection_helper({})
   , starting_room_identifier("[unset-starting_room_identifier]")
   , current_room(nullptr)
   , room_shader(nullptr)
   , initialized(false)
   , dialog_system(nullptr)
   , active_dialog(nullptr)
   , paused(false)
   , subscribed_to_game_event_names({})
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


void FixedRoom2D::set_room_shader(AllegroFlare::Shader* room_shader)
{
   this->room_shader = room_shader;
}


AllegroFlare::Shader* FixedRoom2D::get_room_shader() const
{
   return room_shader;
}


AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper &FixedRoom2D::get_entity_collection_helper_ref()
{
   return entity_collection_helper;
}


void FixedRoom2D::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;

   //inventory_window.set_font_bin(font_bin);

   // set the font_bin in each of the rooms (likely the font_bin dependency should be moved to a RoomRenderer)
   for (auto &room_dictionary_listing : room_dictionary)
   {
      AllegroFlare::Prototypes::FixedRoom2D::Room* room = room_dictionary_listing.second;
      if (room) room->set_font_bin(font_bin);
      else
      {
         std::string room_name = room_dictionary_listing.first;
         std::cout << "Weird error, could not set_font_bin in room \"" << room_name << "\" because "
                   << "it is nullptr." << std::endl;
      }
   }
   return;
}

std::set<std::string> FixedRoom2D::get_subscribed_to_game_event_names()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "get_subscribed_to_game_event_names" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return subscribed_to_game_event_names;
}

bool FixedRoom2D::is_subscribed_to_game_event_name(std::string game_event_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "is_subscribed_to_game_event_name" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return (subscribed_to_game_event_names.count(game_event_name) != 0);
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
   subscribed_to_game_event_names = {
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::INTERACTION_EVENT_NAME,
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::SCRIPT_EVENT_NAME,
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::DIALOG_EVENT_NAME,
      "pause_game",
      "unpause_game",
   };

   dialog_system.set_bitmap_bin(bitmap_bin);
   dialog_system.set_font_bin(font_bin);
   dialog_system.initialize();

   //inventory_window.set_font_bin(font_bin);
   //inventory_window.set_bitmap_bin(bitmap_bin);
   //inventory_window.set_event_emitter(event_emitter);
   //inventory_window.set_af_inventory(&af_inventory);
   //inventory_window.set_inventory_index(&inventory_index);

   entity_collection_helper.set_entity_dictionary(&entity_dictionary);
   entity_collection_helper.set_entity_room_associations(&entity_room_associations);

   script_runner.set_event_emitter(event_emitter);
   script_runner.set_script_dictionary(&script_dictionary);

   initialized = true;

   return;
}

bool FixedRoom2D::load_configuration(AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "load_configuration" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Prototypes::FixedRoom2D::ConfigurationLoader configuration_loader;
   configuration_loader.set_source_configuration(&configuration);

   configuration_loader.set_destination_inventory_index(&inventory_index);
   configuration_loader.set_destination_af_inventory(&af_inventory);
   configuration_loader.set_destination_flags(&flags);
   configuration_loader.set_destination_entity_dictionary(&entity_dictionary);
   configuration_loader.set_destination_room_dictionary(&room_dictionary);
   configuration_loader.set_destination_entity_room_associations(&entity_room_associations);
   configuration_loader.set_destination_script_dictionary(&script_dictionary);
   configuration_loader.set_destination_starting_room_identifier(&starting_room_identifier);

   bool load_was_successful = configuration_loader.load_from_source_configuration();

   if (!load_was_successful)
   {
      std::cout << "[FixedRoom2D::FixedRoom2D::load_configuration]: ERROR: there was an "
                << "error loading the configuration."
                << std::endl;
   }

   return load_was_successful;
}

bool FixedRoom2D::enter_start_room()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "enter_start_room" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return enter_room(starting_room_identifier);
}

bool FixedRoom2D::load_gametest_configuration()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "load_gametest_configuration" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   // TODO: rename this to build_gametest_configuration
   AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory configuration_factory;
   AllegroFlare::Prototypes::FixedRoom2D::Configuration source_configuration =
     configuration_factory.load_original_gametest_default(
       bitmap_bin, font_bin, event_emitter, &entity_collection_helper);

   return load_configuration(source_configuration);
}

void FixedRoom2D::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //room.update();
   update_all_rooms();

   //if (active_dialog) active_dialog->update();
   dialog_system.update();

   //inventory_window.update();
   return;
}

bool FixedRoom2D::enter_room(std::string room_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "enter_room" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   // find the room name
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>::iterator it =
      room_dictionary.find(room_name);

   // if the room name does not exist, output an error and return false
   if (it == room_dictionary.end())
   {
      std::cout << "[FixedRoom2D::FixedRoom2D::enter_room]: error: attempted to enter room named "
                << "\"" << room_name << "\" but it did not exist." << std::endl;
      return false;
   }

   // output a nice little error showing that the room will be entered
   std::cout << "[FixedRoom2D::FixedRoom2D::enter_room]: info: entering room named "
             << "\"" << room_name << "\"." << std::endl;

   // ensure all the entities do not think they have the cursor over them
   unhover_any_and_all_entities();
   reset_cursors_to_default_in_all_rooms();

   // set the current room
   current_room = it->second;

   return true;
}

void FixedRoom2D::unhover_any_and_all_entities()
{
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> all_entities =
      entity_collection_helper.select_all();

   for (auto &entity : all_entities)
   {
      if (entity->get_cursor_is_over()) entity->on_cursor_leave(); // TODO, consider exiting without "leaving"
   }
   return;
}

void FixedRoom2D::reset_cursors_to_default_in_all_rooms()
{
   for (auto &room_dictionary_listing : room_dictionary)
   {
      AllegroFlare::Prototypes::FixedRoom2D::Room* room = room_dictionary_listing.second;
      if (!room)
      {
         std::string room_name = room_dictionary_listing.first;
         std::cout << "Odd error, when clearing cursors, room listing at \"" << room_name << "\" it is nullptr."
                   << " Skipping." << std::endl;
      }
      else
      {
         room->reset_cursor_to_default();
      }
   }
   return;
}

std::string FixedRoom2D::get_current_room_dictionary_name(AllegroFlare::Prototypes::FixedRoom2D::Room* room)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "get_current_room_dictionary_name" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!current_room) return nullptr;
   for (auto &room_dictionary_listing : room_dictionary)
   {
      if (room_dictionary_listing.second == room) return room_dictionary_listing.first;
   }
   return "";
}

void FixedRoom2D::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   // render the current room
   if (current_room)
   {
      if (room_shader) room_shader->activate();
      render_entities_in_current_room();
      if (room_shader) room_shader->deactivate();

      current_room->render(); // for now, only renders the cursor
   }
   else
   {
      render_void_room();
   }

   // render the active dialog
   //if (active_dialog)
   //{
      //AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(font_bin, bitmap_bin, active_dialog);
      //dialog_box_renderer.render();
   //}
   dialog_system.render();

   //// render the inventory window
   //inventory_window.render();

   // render paused notification
   if (paused)
   {
      AllegroFlare::Elements::DialogBoxFactory factory;
      AllegroFlare::Elements::DialogBoxes::Basic pause_dialog_box = factory.build_basic_dialog(
         {"Paused."});
      pause_dialog_box.set_created_at(0); // so it will show
      pause_dialog_box.reveal_all_characters(); // so it will show
      AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(font_bin, bitmap_bin, &pause_dialog_box);
      dialog_box_renderer.render();
   }

   return;
}

void FixedRoom2D::render_void_room()
{
   al_clear_to_color(ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3});
   return;
}

void FixedRoom2D::process_subscribed_to_game_event(AllegroFlare::GameEvent* game_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "process_subscribed_to_game_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::INTERACTION_EVENT_NAME))
   {
      process_interaction_event(game_event->get_data());
   }
   else if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::SCRIPT_EVENT_NAME))
   {
      process_script_event(game_event->get_data());
   }
   else if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::DIALOG_EVENT_NAME))
   {
      process_dialog_event(game_event->get_data());
      dialog_system.process_dialog_event(game_event->get_data());
   }
   else if (game_event->is_type("unpause_game"))
   {
      unpause_game();
   }
   else if (game_event->is_type("pause_game"))
   {
      pause_game();
   }
   else
   {
      std::cout << "[FixedRoom2D::FixedRoom2D::process_subscribed_to_game_event]: "
                << "error: unexpected game_event type "
                << "\"" << game_event->get_type() << "\". Doing nothing (except outputting this error)."
                << std::endl;
   }
   return;
}

void FixedRoom2D::process_interaction_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "process_interaction_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (game_event_data && game_event_data->get_type() == "InteractionEventData")
   {
      AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData* interaction_event_data =
          static_cast<AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData*>(game_event_data);

      std::string name = entity_collection_helper.find_dictionary_name_of_entity_that_cursor_is_now_over();
      if (name.empty())
      {
         script_runner.load_script_lines({"DIALOG: There's nothing here."});
         script_runner.play_or_resume();
      }
      else
      {
         // assume the interaction is a script (for now)
         // execute the script
         AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* interacting_entity = entity_dictionary.at(name);
         std::string script = interacting_entity->get_on_cursor_interact_script_name();
         script_runner.load_script_by_dictionary_name(script);
         script_runner.play_or_resume();
      }
   }
   else
   {
      std::cout << "Expecting game_event_data to be present but it is a nullptr" << std::endl;
   }
   return;
}

void FixedRoom2D::process_dialog_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "process_dialog_event" << ": error: " << "guard \"initialized\" not met";
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
         //DialogEventDatas::CloseDialog* close_dialog_event_data =
            //static_cast<DialogEventDatas::CloseDialog*>(game_event_data);

         //shutdown_dialog();

         // HERE: handle this event:
         resume_all_rooms();
         // HERE: handle this event:
         if (script_runner.get_paused_for_dialog_to_finish()) script_runner.play_or_resume();
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

void FixedRoom2D::process_script_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "process_script_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   using namespace AllegroFlare::Prototypes::FixedRoom2D;

   if (!game_event_data)
   {
      std::cout << "A weird error occurred. Expecting script_event_data to be valid but it is nullptr" << std::endl;
      return;
   }
   else
   {
      if (game_event_data->is_type(ScriptEventDatas::EnterRoom::TYPE))
      {
         AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::EnterRoom* enter_room_event_data =
             static_cast<AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::EnterRoom*>(game_event_data);
         std::string room_name_to_enter = enter_room_event_data->get_room_dictionary_name_to_enter();

         enter_room(room_name_to_enter);
      }
      else
      {
         bool a_new_dialog_was_spawned = dialog_system.process_script_event(game_event_data);
         if (a_new_dialog_was_spawned) suspend_all_rooms();

         // TODO: fix this design flaw:
         // NOTE: this cout section below represents a fracture in design since delegating dialog management to
         // the dialog_system.  There's currently no way to know if the "process_script_event" was handled
         // by either this FixedRoom2D or by any delegates.

         std::cout << "[FixedRoom2D::FixedRoom2D::process_script_event]: error: "
                   << "Unknown game_event_data type "
                   << "\"" << game_event_data->get_type() << "\""
                   << std::endl;
      }
   }
   return;
}

void FixedRoom2D::render_entities_in_current_room()
{
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities = get_entities_in_current_room();
   for (auto &entity : entities)
   {
      // NOTE: some entities are set to "hidden=-true" and they will not actually render if called to
      if (entity) entity->render();
   }
   return;
}

std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> FixedRoom2D::get_entities_in_current_room()
{
   return entity_collection_helper.select_all_in_room_ordered_by_id(get_dictionary_name_of_current_room());
}

std::string FixedRoom2D::get_dictionary_name_of_current_room()
{
   if (!current_room) return "";
   for (auto &room_dictionary_listing : room_dictionary)
   {
      if (current_room == room_dictionary_listing.second) return room_dictionary_listing.first;
   }
   return "";
}

void FixedRoom2D::update_all_rooms()
{
   for (auto &room_dictionary_listing : room_dictionary)
   {
      AllegroFlare::Prototypes::FixedRoom2D::Room* room = room_dictionary_listing.second;
      if (room) room->update();
      else
      {
         std::string room_name = room_dictionary_listing.first;
         std::cout << "Weird error, could not update room at \"" << room_name << "\", it is nullptr." << std::endl;
      }
   }
}

void FixedRoom2D::suspend_all_rooms()
{
   for (auto &room_dictionary_listing : room_dictionary)
   {
      AllegroFlare::Prototypes::FixedRoom2D::Room* room = room_dictionary_listing.second;
      if (room) room->suspend();
      else
      {
         std::string room_name = room_dictionary_listing.first;
         std::cout << "Weird error, could not suspend room at \"" << room_name << "\", it is nullptr." << std::endl;
      }
   }
   return;
}

void FixedRoom2D::resume_all_rooms()
{
   for (auto &room_dictionary_listing : room_dictionary)
   {
      AllegroFlare::Prototypes::FixedRoom2D::Room* room = room_dictionary_listing.second;
      if (room) room->resume();
      else
      {
         std::string room_name = room_dictionary_listing.first;
         std::cout << "Weird error, could not resume room at \"" << room_name << "\", it is nullptr." << std::endl;
      }
   }
   return;
}

void FixedRoom2D::pause_game()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "pause_game" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (paused) return;
   suspend_all_rooms();
   paused = true;
   return;
}

void FixedRoom2D::unpause_game()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "unpause_game" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!paused) return;
   resume_all_rooms();
   paused = false;
   return;
}

void FixedRoom2D::dialog_advance()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "dialog_advance" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   dialog_system.dialog_advance();
   return;

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

void FixedRoom2D::dialog_cursor_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "dialog_cursor_up" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   dialog_system.dialog_cursor_up();
   return;

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

void FixedRoom2D::dialog_cursor_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "dialog_cursor_down" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   dialog_system.dialog_cursor_down();
   return;

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

bool FixedRoom2D::dialog_is_finished()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "dialog_is_finished" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return dialog_system.dialog_is_finished();


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

bool FixedRoom2D::shutdown_dialog()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "shutdown_dialog" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return dialog_system.shutdown_dialog();


   if (!active_dialog) return false;
   delete active_dialog;
   active_dialog = nullptr;
   return true;
}

void FixedRoom2D::activate_primary_action()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "activate_primary_action" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active())
   //{
      //// IDEA: inventory_window.select_item_currently_under_cursor();
   //}
   //else if (active_dialog)
   if (active_dialog)
   {
      //dialog_advance();
      dialog_system.dialog_advance();
      //if (dialog_is_finished())
      if (dialog_system.dialog_is_finished())
      {
         emit_close_dialog_event(active_dialog);
      }
   }
   else if (current_room && !current_room->get_suspended())
   {
      current_room->interact_with_item_under_cursor();
   }

   return;
}

void FixedRoom2D::emit_close_dialog_event(AllegroFlare::Elements::DialogBoxes::Base* dialog)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "emit_close_dialog_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(dialog))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "emit_close_dialog_event" << ": error: " << "guard \"dialog\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "emit_close_dialog_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CloseDialog *close_dialog_event_data = new
     AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CloseDialog(dialog);
   event_emitter->emit_game_event(AllegroFlare::GameEvent(
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::DIALOG_EVENT_NAME,
      close_dialog_event_data
   ));
   return;
}

void FixedRoom2D::move_cursor_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "move_cursor_up" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   dialog_system.move_cursor_up();
   return;

   //if (inventory_window.get_active()) inventory_window.move_cursor_up();
   if (active_dialog) dialog_cursor_up();
   return;
}

void FixedRoom2D::move_cursor_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "move_cursor_down" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   dialog_system.move_cursor_down();
   return;


   //if (inventory_window.get_active()) inventory_window.move_cursor_down();
   if (active_dialog) dialog_cursor_down();
   return;
}

void FixedRoom2D::move_cursor_left()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "move_cursor_left" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active()) inventory_window.move_cursor_left();
   return;
}

void FixedRoom2D::move_cursor_right()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "move_cursor_right" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (inventory_window.get_active()) inventory_window.move_cursor_right();
   return;
}

void FixedRoom2D::move_cursor(float distance_x, float distance_y)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "FixedRoom2D" << "::" << "move_cursor" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (current_room && !current_room->get_suspended())
   { 
      std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities_in_current_room =
          get_entities_in_current_room();
      current_room->move_cursor(distance_x, distance_y, entities_in_current_room);
   }
   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


