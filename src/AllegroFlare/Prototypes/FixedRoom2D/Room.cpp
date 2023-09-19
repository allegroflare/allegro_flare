

#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
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


AllegroFlare::Prototypes::FixedRoom2D::Cursor &Room::get_cursor_ref()
{
   return cursor;
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
   //cursor.update();

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
   throw std::runtime_error("FixedRoom2D::Room::render: error: this method is no longer used");
   // draw the entities
   //for (auto &entity : entity_collection_helper.select_all_ordered_by_id(
   //   this_rooms_dictionary_name__this_injection_is_temporary_measure))
   //{
      //entity->render();
      //entity->get_placement_ref().draw_box(AllegroFlare::Color::DodgerBlue, true);
   //}

   // draw the cursor
   //cursor.draw();

   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


