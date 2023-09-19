

#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>




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
   if (suspended) return;
   suspended = true;
   suspended_at = al_get_time();
   return;
}

void Room::resume()
{
   if (!suspended) return;
   suspended = false;
   suspended_at = 0.0f;
   return;
}

void Room::show()
{
   return;
}

void Room::hide()
{
   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


