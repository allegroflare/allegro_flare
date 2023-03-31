

#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EventNames.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/InteractionEventData.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Room::Room(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper)
   : font_bin(font_bin)
   , event_emitter(event_emitter)
   , entity_collection_helper(entity_collection_helper)
   , cursor({})
   , min_x(0.0f)
   , min_y(0.0f)
   , max_x(1920.0f)
   , max_y(1080.0f)
   , suspended(false)
   , suspended_at(0.0f)
   , initialized(false)
{
}


Room::~Room()
{
}


void Room::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Room::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Room::set_entity_collection_helper(AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper)
{
   this->entity_collection_helper = entity_collection_helper;
}


void Room::set_min_x(float min_x)
{
   this->min_x = min_x;
}


void Room::set_min_y(float min_y)
{
   this->min_y = min_y;
}


void Room::set_max_x(float max_x)
{
   this->max_x = max_x;
}


void Room::set_max_y(float max_y)
{
   this->max_y = max_y;
}


float Room::get_min_x() const
{
   return min_x;
}


float Room::get_min_y() const
{
   return min_y;
}


float Room::get_max_x() const
{
   return max_x;
}


float Room::get_max_y() const
{
   return max_y;
}


bool Room::get_suspended() const
{
   return suspended;
}


void Room::suspend()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::suspend]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::suspend: error: guard \"initialized\" not met");
   }
   if (suspended) return;
   suspended = true;
   suspended_at = al_get_time();
   return;
}

void Room::resume()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::resume]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::resume: error: guard \"initialized\" not met");
   }
   if (!suspended) return;
   suspended = false;
   suspended_at = 0.0f;
   return;
}

void Room::show()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::show]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::show: error: guard \"initialized\" not met");
   }
   return;
}

void Room::hide()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::hide]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::hide: error: guard \"initialized\" not met");
   }
   return;
}

void Room::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Room::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::initialize: error: guard \"(!initialized)\" not met");
   }
   cursor.set_font_bin(font_bin);

   // setup the objects to good defaults
   cursor.set_cursor_to_pointer();
   cursor.clear_info_text();

   initialized = true;
   return;
}

void Room::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::update: error: guard \"initialized\" not met");
   }
   if (suspended) return;

   // update the entities
   //for (auto &entity : entity_collection_helper.select_all_ordered_by_id())
   //{
      //entity->update();
   //}

   // update the cursor
   cursor.update();

   return;
}

void Room::render(std::string this_rooms_dictionary_name__this_injection_is_temporary_measure)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::render: error: guard \"initialized\" not met");
   }
   // draw the entities
   //for (auto &entity : entity_collection_helper.select_all_ordered_by_id(
   //   this_rooms_dictionary_name__this_injection_is_temporary_measure))
   //{
      //entity->render();
      //entity->get_placement_ref().draw_box(AllegroFlare::Color::DodgerBlue, true);
   //}

   // draw the cursor
   cursor.draw();

   return;
}

void Room::interact_with_item_under_cursor()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::interact_with_item_under_cursor]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::interact_with_item_under_cursor: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Room::interact_with_item_under_cursor]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::interact_with_item_under_cursor: error: guard \"event_emitter\" not met");
   }
   if (!(entity_collection_helper))
   {
      std::stringstream error_message;
      error_message << "[Room::interact_with_item_under_cursor]: error: guard \"entity_collection_helper\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::interact_with_item_under_cursor: error: guard \"entity_collection_helper\" not met");
   }
   std::string name = entity_collection_helper->find_dictionary_name_of_entity_that_cursor_is_now_over();
   emit_interaction_event(name, cursor.get_x(), cursor.get_y());
   return;
}

void Room::move_cursor(float distance_x, float distance_y, std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities_in_this_room)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::move_cursor]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::move_cursor: error: guard \"initialized\" not met");
   }
   cursor.move(distance_x, distance_y);
   cursor.clamp(min_x, min_y, max_x, max_y);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* entity_cursor_was_over = nullptr;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* entity_cursor_is_now_over = nullptr;

   int cursor_x = cursor.get_x();
   int cursor_y = cursor.get_y();

   // update the state of the entities
   for (auto &entity : entities_in_this_room)
   {
      if (entity->get_cursor_is_over()) entity_cursor_was_over = entity;
      if (entity->get_placement_ref().collide_as_if(entity->get_bitmap(), cursor_x, cursor_y)) entity_cursor_is_now_over = entity;
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

void Room::reset_cursor_to_default()
{
   cursor.set_cursor_to_pointer();
   cursor.clear_info_text();
   return;
}

void Room::emit_interaction_event(std::string item_dictionary_name, float cursor_x, float cursor_y)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Room::emit_interaction_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Room::emit_interaction_event: error: guard \"initialized\" not met");
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


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


