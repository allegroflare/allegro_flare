

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
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
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectItem.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/EnterRoom.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/InitiateDialog.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


FixedRoom2D::FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::string standard_dialog_box_font_name, int standard_dialog_box_font_size)
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
   , cursor({})
   , starting_room_identifier("[unset-starting_room_identifier]")
   , current_room(nullptr)
   , room_shader(nullptr)
   , initialized(false)
   , dialog_system(nullptr)
   , paused(false)
   , subscribed_to_game_event_names({})
   , standard_dialog_box_font_name(standard_dialog_box_font_name)
   , standard_dialog_box_font_size(standard_dialog_box_font_size)
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


void FixedRoom2D::set_room_shader(AllegroFlare::Shaders::Base* room_shader)
{
   this->room_shader = room_shader;
}


void FixedRoom2D::set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name)
{
   this->standard_dialog_box_font_name = standard_dialog_box_font_name;
}


void FixedRoom2D::set_standard_dialog_box_font_size(int standard_dialog_box_font_size)
{
   this->standard_dialog_box_font_size = standard_dialog_box_font_size;
}


AllegroFlare::Shaders::Base* FixedRoom2D::get_room_shader() const
{
   return room_shader;
}


std::string FixedRoom2D::get_standard_dialog_box_font_name() const
{
   return standard_dialog_box_font_name;
}


int FixedRoom2D::get_standard_dialog_box_font_size() const
{
   return standard_dialog_box_font_size;
}


AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner &FixedRoom2D::get_script_runner_ref()
{
   return script_runner;
}


AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper &FixedRoom2D::get_entity_collection_helper_ref()
{
   return entity_collection_helper;
}


void FixedRoom2D::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

std::set<std::string> FixedRoom2D::get_subscribed_to_game_event_names()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::get_subscribed_to_game_event_names]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::get_subscribed_to_game_event_names]: error: guard \"initialized\" not met");
   }
   return subscribed_to_game_event_names;
}

bool FixedRoom2D::is_subscribed_to_game_event_name(std::string game_event_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::is_subscribed_to_game_event_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::is_subscribed_to_game_event_name]: error: guard \"initialized\" not met");
   }
   return (subscribed_to_game_event_names.count(game_event_name) != 0);
}

void FixedRoom2D::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::initialize]: error: guard \"event_emitter\" not met");
   }
   subscribed_to_game_event_names = {
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::INTERACTION_EVENT_NAME,
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::SCRIPT_EVENT_NAME,
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::DIALOG_EVENT_NAME,
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_IN_NAME,
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_OUT_NAME,
      "pause_game",
      "unpause_game",
   };

   dialog_system.set_bitmap_bin(bitmap_bin);
   dialog_system.set_font_bin(font_bin);
   dialog_system.set_event_emitter(event_emitter);
   dialog_system.set_standard_dialog_box_font_name(standard_dialog_box_font_name);
   dialog_system.set_standard_dialog_box_font_size(standard_dialog_box_font_size);

   dialog_system.initialize();

   entity_collection_helper.set_entity_dictionary(&entity_dictionary);
   entity_collection_helper.set_entity_room_associations(&entity_room_associations);

   script_runner.set_event_emitter(event_emitter);
   script_runner.set_script_dictionary(&script_dictionary);

   cursor.set_font_bin(font_bin);
   cursor.set_cursor_to_pointer();
   cursor.clear_info_text();

   initialized = true;

   return;
}

bool FixedRoom2D::load_configuration(AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::load_configuration]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::load_configuration]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::enter_start_room]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::enter_start_room]: error: guard \"initialized\" not met");
   }
   return enter_room(starting_room_identifier);
}

bool FixedRoom2D::load_gametest_configuration()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::load_gametest_configuration]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::load_gametest_configuration]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::update]: error: guard \"initialized\" not met");
   }
   cursor.update();

   dialog_system.update();

   return;
}

bool FixedRoom2D::enter_room(std::string room_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::enter_room]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::enter_room]: error: guard \"initialized\" not met");
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
   reset_cursor_to_default();

   // set the mouseover if the cursor is currently over an object
   // TODO: Set mouse over on any currently hovered object

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

std::string FixedRoom2D::get_current_room_dictionary_name(AllegroFlare::Prototypes::FixedRoom2D::Room* room)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::get_current_room_dictionary_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::get_current_room_dictionary_name]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::render]: error: guard \"initialized\" not met");
   }
   // render the current room
   if (current_room)
   {
      if (room_shader) room_shader->activate();
      render_entities_in_current_room();
      if (room_shader) room_shader->deactivate();
   }
   else
   {
      render_void_room();
   }

   // Render the cursor (before the dialog system, it is for room interaction only (for now))
   cursor.draw();

   // render the dialog_system
   dialog_system.render();

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
   ALLEGRO_BITMAP *surface = al_get_target_bitmap();
   al_clear_to_color(ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3});

   // Draw some text
   ALLEGRO_FONT *font = obtain_cempty_room_font();
   al_draw_text(
      font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      al_get_bitmap_width(surface)/2,
      al_get_bitmap_height(surface)/2 - al_get_font_line_height(font)/2,
      ALLEGRO_ALIGN_CENTER,
      "There is currently no room loaded"
   );

   return;
}

void FixedRoom2D::process_subscribed_to_game_event(AllegroFlare::GameEvent* game_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::process_subscribed_to_game_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::process_subscribed_to_game_event]: error: guard \"initialized\" not met");
   }
   if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::INTERACTION_EVENT_NAME))
   {
      process_interaction_event(game_event->get_data());
   }
   else if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::SCRIPT_EVENT_NAME))
   {
      process_script_event(game_event->get_data());
   }
   else if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_IN_NAME))
   {
      suspend_all_rooms();
   }
   else if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::EVENT_DIALOG_SWITCH_OUT_NAME))
   {
      resume_all_rooms();
      if (script_runner.get_paused_for_dialog_to_finish()) script_runner.play_or_resume();
   }
   else if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::DIALOG_EVENT_NAME))
   {
      // TODO: Address how this current design requires calling these two methods here, specifically delegating
      // to dialog_system to process_dialog_event(). It's more likely that the dialog_system will need to
      // consume the incoming game_event on its own, rather than have FixedRoom2D dispatch/delegeate to it here
      // like it's doing now.  Please review and improve.
      // HERE:
      dialog_system.process_dialog_event(game_event->get_data());
      // TODO: remove this: process_dialog_event(game_event->get_data());
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::process_interaction_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::process_interaction_event]: error: guard \"initialized\" not met");
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

void FixedRoom2D::process_script_event(AllegroFlare::GameEventDatas::Base* game_event_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::process_script_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::process_script_event]: error: guard \"initialized\" not met");
   }
   //bool a_new_dialog_was_spawned = false;
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
      else if (game_event_data->is_type(ScriptEventDatas::InitiateDialog::TYPE))
      {
         AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::InitiateDialog* spawn_dialog_event_data =
             static_cast<AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::InitiateDialog*>(game_event_data);
         std::vector<std::string> pages = spawn_dialog_event_data->get_dialog_pages();

         // TODO: move this to emitting an event
         dialog_system.spawn_basic_dialog(pages);
      }
      else if (game_event_data->is_type(ScriptEventDatas::CollectItem::TYPE))
      {
         AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectItem* collect_item_event_data =
             static_cast<AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectItem*>(game_event_data);

         // TODO: move this to emitting an event
         dialog_system.spawn_you_got_an_item_dialog(
               "Keys",
               "key-keychain-house-keys-door-photo-pixabay-25.png"
            );
      }
      else
      {
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::pause_game]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::pause_game]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::unpause_game]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::unpause_game]: error: guard \"initialized\" not met");
   }
   if (!paused) return;
   resume_all_rooms();
   paused = false;
   return;
}

void FixedRoom2D::dialog_cursor_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_cursor_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_cursor_up]: error: guard \"initialized\" not met");
   }
   dialog_system.dialog_cursor_up();
   return;
}

void FixedRoom2D::dialog_cursor_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_cursor_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_cursor_down]: error: guard \"initialized\" not met");
   }
   dialog_system.dialog_cursor_down();
   return;
}

bool FixedRoom2D::dialog_is_finished()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_is_finished]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::dialog_is_finished]: error: guard \"initialized\" not met");
   }
   return dialog_system.dialog_is_finished();
}

void FixedRoom2D::activate_primary_action()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::activate_primary_action]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::activate_primary_action]: error: guard \"initialized\" not met");
   }
   // TODO: probably remove this branching logic here and have the dialog_system manage the active/deactive
   // emit closing dialog logic.  The FixedRoom2D should be "suspended"/"unsuspended" while control is handed
   // off to the dialog_system.
   if (dialog_system.a_dialog_is_active())
   {
      dialog_system.dialog_advance();
      if (dialog_system.dialog_is_finished())
      {
         emit_close_current_active_dialog_event(); //(active_dialog)
      }
   }
   else if (current_room && !current_room->get_suspended())
   {
      interact_with_item_under_cursor();
   }

   return;
}

void FixedRoom2D::interact_with_item_under_cursor()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::interact_with_item_under_cursor]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::interact_with_item_under_cursor]: error: guard \"initialized\" not met");
   }
   if (!(current_room))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::interact_with_item_under_cursor]: error: guard \"current_room\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::interact_with_item_under_cursor]: error: guard \"current_room\" not met");
   }
   if (!((!current_room->get_suspended())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::interact_with_item_under_cursor]: error: guard \"(!current_room->get_suspended())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::interact_with_item_under_cursor]: error: guard \"(!current_room->get_suspended())\" not met");
   }
   int x = cursor.get_x();
   int y = cursor.get_y();
   std::string name = entity_collection_helper.find_dictionary_name_of_entity_that_cursor_is_now_over();
   emit_interaction_event(name, x, y);
}

void FixedRoom2D::emit_interaction_event(std::string item_dictionary_name, float cursor_x, float cursor_y)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::emit_interaction_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::emit_interaction_event]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData *interaction_event_data =
      new AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData(item_dictionary_name, cursor_x, cursor_y);

   AllegroFlare::GameEvent game_event(
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::INTERACTION_EVENT_NAME,
      interaction_event_data
   );

   event_emitter->emit_game_event(game_event);
   return;
}

void FixedRoom2D::emit_close_current_active_dialog_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::emit_close_current_active_dialog_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::emit_close_current_active_dialog_event]: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::emit_close_current_active_dialog_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::emit_close_current_active_dialog_event]: error: guard \"event_emitter\" not met");
   }
   // TODO: probably remove this function and have all the logic surrounding "close_current_active_dialog"
   // to be handled in the dialog_system

   AllegroFlare::Elements::DialogBoxes::Base* dialog_to_close = nullptr;
   // TODO: consider having the dialog_system itself emit the event to close the dialog?
   // the exact ownership of the dialog controls is still up for clarification
   dialog_to_close = dialog_system.get_active_dialog_ref();

   std::cout << "EMITTING in FixedRoom2D emit_close_dialog_event" << std::endl;
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CloseDialog *close_dialog_event_data = new
     AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CloseDialog(dialog_to_close);
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_up]: error: guard \"initialized\" not met");
   }
   dialog_system.move_cursor_up();
   return;
}

void FixedRoom2D::move_cursor_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_down]: error: guard \"initialized\" not met");
   }
   dialog_system.move_cursor_down();
   return;
}

void FixedRoom2D::move_cursor_left()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_left]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_left]: error: guard \"initialized\" not met");
   }
   // TODO: This cursor movement applies to the inventory (if it is open)
   return;
}

void FixedRoom2D::move_cursor_right()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_right]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_right]: error: guard \"initialized\" not met");
   }
   // TODO: This cursor movement applies to the inventory (if it is open)
   return;
}

void FixedRoom2D::move_cursor(float distance_x, float distance_y)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor]: error: guard \"initialized\" not met");
   }
   if (current_room && !current_room->get_suspended())
   { 
      std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities_in_current_room =
          get_entities_in_current_room();
      move_cursor_within_room(distance_x, distance_y, entities_in_current_room);
   }
   return;
}

void FixedRoom2D::move_cursor_within_room(float distance_x, float distance_y, std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities_in_this_room)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_within_room]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::move_cursor_within_room]: error: guard \"initialized\" not met");
   }
   float room_min_x = current_room->get_min_x();
   float room_min_y = current_room->get_min_y();
   float room_max_x = current_room->get_max_x();
   float room_max_y = current_room->get_max_y();

   cursor.move(distance_x, distance_y);
   cursor.clamp(room_min_x, room_min_y, room_max_x, room_max_y); // TODO: Consider not clamping to room, and instead
                                                                 // clamping to screen, and nullifying clicks
                                                                 // or activity that is outside the room bounds

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* entity_cursor_was_over = nullptr;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* entity_cursor_is_now_over = nullptr;

   int cursor_x = cursor.get_x();
   int cursor_y = cursor.get_y();

   // update the state of the entities
   for (auto &entity : entities_in_this_room)
   {
      if (entity->get_cursor_is_over()) entity_cursor_was_over = entity;
      if (entity->get_placement_ref().collide_as_if(entity->get_bitmap(), cursor_x, cursor_y))
      {
         entity_cursor_is_now_over = entity;
      }
   }

   // a change has happened
   if (entity_cursor_was_over != entity_cursor_is_now_over)
   {
      if (entity_cursor_was_over)
      {
         entity_cursor_was_over->on_cursor_leave();
      }

      if (entity_cursor_is_now_over)
      {
         entity_cursor_is_now_over->on_cursor_enter();
         if (entity_cursor_is_now_over->get_cursor_insights_are_hidden())
         {
            reset_cursor_to_default();
         }
         else
         {
            cursor.set_cursor_to_pointer();
            cursor.set_info_text("inspect");
         }
      }
      else
      {
         // cursor is now over nothing
         reset_cursor_to_default();
      }
   }

   return;
}

ALLEGRO_FONT* FixedRoom2D::obtain_cempty_room_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::obtain_cempty_room_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D::obtain_cempty_room_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << "Lora-Medium.ttf -32";
   return font_bin->auto_get(composite_font_str.str());
}

void FixedRoom2D::reset_cursor_to_default()
{
   cursor.set_cursor_to_pointer();
   cursor.clear_info_text();
   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


