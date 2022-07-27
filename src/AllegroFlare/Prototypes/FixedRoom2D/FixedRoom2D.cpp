

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


FixedRoom2D::FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , entity_dictionary({})
   , script_dictionary({})
   , script_runner({})
   , entity_collection_helper({})
   , room({})
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


void FixedRoom2D::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
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
   AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(bitmap_bin);

   entity_dictionary = {
      { "door", entity_factory.create_entity("download-door-png-transparent-image-and-clipart-3.png", 1400, 800, 0.85) },
      { "chair", entity_factory.create_entity("wooden-chair-png-transparent-image-pngpix-0.png", 600, 800, 0.168) },
      { "table", entity_factory.create_entity("download-wooden-table-png-image-png-image-pngimg-3.png", 900, 800, 0.4) },
      { "keys", entity_factory.create_entity(
            "key-keychain-house-keys-door-photo-pixabay-25.png", 940, 590, 0.05, "keys", "say_hello") },
   };

   script_dictionary = {
      { "say_hello", AllegroFlare::Prototypes::FixedRoom2D::Script({"SIGNAL: Hello!"}) },
   };

   entity_collection_helper.set_entity_dictionary(&entity_dictionary);

   room.set_font_bin(font_bin);
   room.set_event_emitter(event_emitter);
   room.set_entity_dictionary(&entity_dictionary);
   room.initialize();

   script_runner.set_audio_controller(nullptr); // TODO
   script_runner.set_af_inventory(nullptr); // TODO
   script_runner.set_inventory_window(nullptr); // TODO
   script_runner.set_script_dictionary(&script_dictionary);
   script_runner.set_flags(nullptr); // TODO

   //script_runner.set

   initialized = true;
   return;
}

void FixedRoom2D::update()
{
   room.update();

   return;
}

void FixedRoom2D::render()
{
   room.render();

   return;
}

void FixedRoom2D::process_interaction_event(AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData* interaction_event_data)
{
   std::string name = entity_collection_helper.find_dictionary_name_of_entity_that_cursor_is_now_over();
   if (name.empty())
   {
      // TODO: spawn some dialog that says "there is nothing here"
   }
   else
   {
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* interacting_entity = entity_dictionary.at(name);
      std::string script = interacting_entity->get_on_cursor_interact_script_name();
      
      script_runner.load_script_by_dictionary_name(script);

      script_runner.play_current_script_line();
   }
   return;
}

void FixedRoom2D::activate_primary_action()
{
   room.interact_with_item_under_cursor();
   return;
}

void FixedRoom2D::move_cursor(float distance_x, float distance_y)
{
   room.move_cursor(distance_x, distance_y);
   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


