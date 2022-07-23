

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


FixedRoom2D::FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , room_dictionary({})
   , entity_dictionary({})
   , entity_collection_helper(&entity_dictionary)
   , cursor({})
   , initialized(false)
{
}


FixedRoom2D::~FixedRoom2D()
{
}


void FixedRoom2D::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void FixedRoom2D::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void FixedRoom2D::set_room_dictionary(AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary room_dictionary)
{
   this->room_dictionary = room_dictionary;
}


AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary FixedRoom2D::get_room_dictionary()
{
   return room_dictionary;
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
   AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(bitmap_bin);
   cursor.set_font_bin(font_bin);

   entity_dictionary = {
      { "door", entity_factory.create_entity("download-door-png-transparent-image-and-clipart-3.png", 1400, 800, 0.85) },
      { "chair", entity_factory.create_entity("wooden-chair-png-transparent-image-pngpix-0.png", 600, 800, 0.168) },
      { "table", entity_factory.create_entity("download-wooden-table-png-image-png-image-pngimg-3.png", 900, 800, 0.4) },
      { "keys", entity_factory.create_entity("key-keychain-house-keys-door-photo-pixabay-25.png", 940, 590, 0.05) },
   };

   cursor.set_cursor_to_pointer();
   cursor.clear_info_text();

   initialized = true;
   return;
}

void FixedRoom2D::update()
{
   // update the entities
   for (auto &entity : entity_collection_helper.select_all_ordered_by_id())
   {
      entity->update();
   }

   // update the cursor
   cursor.update();

   return;
}

void FixedRoom2D::render()
{
   // draw the entities
   for (auto &entity : entity_collection_helper.select_all_ordered_by_id())
   {
      entity->render();
      //entity->get_placement_ref().draw_box(AllegroFlare::Color::DodgerBlue, true);
   }

   // draw the cursor
   cursor.draw();

   return;
}

void FixedRoom2D::interact_with_item_under_cursor()
{
   // TODO: ellaborate here
   std::string name = entity_collection_helper.find_dictionary_name_of_entity_that_cursor_is_now_over();
   if (name.empty()) cursor.set_info_text("there is nothing here");
   else cursor.set_info_text(name);
   return;
}

void FixedRoom2D::move_cursor(float distance_x, float distance_y)
{
   cursor.move(distance_x, distance_y);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* entity_cursor_was_over = nullptr;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* entity_cursor_is_now_over = nullptr;

   int cursor_x = cursor.get_x();
   int cursor_y = cursor.get_y();

   // update the state of the entities
   for (auto &entity : entity_collection_helper.select_all_ordered_by_id())
   {
      if (entity->get_cursor_is_over()) entity_cursor_was_over = entity;
      if (entity->get_placement_ref().collide(cursor_x, cursor_y)) entity_cursor_is_now_over = entity;
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
         cursor.set_cursor_to_pointer();
         cursor.set_info_text("inspect");
      }
      else
      {
         // cursor is now over nothing
         cursor.set_cursor_to_pointer();
         cursor.clear_info_text();
      }
   }

   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


