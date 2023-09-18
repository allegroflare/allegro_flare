#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Cursor.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class Room
         {
         private:
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper;
            AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor;
            float min_x;
            float min_y;
            float max_x;
            float max_y;
            bool suspended;
            float suspended_at;
            bool initialized;

         protected:


         public:
            Room(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper=nullptr);
            ~Room();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_entity_collection_helper(AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper);
            void set_min_x(float min_x);
            void set_min_y(float min_y);
            void set_max_x(float max_x);
            void set_max_y(float max_y);
            float get_min_x() const;
            float get_min_y() const;
            float get_max_x() const;
            float get_max_y() const;
            bool get_suspended() const;
            AllegroFlare::Prototypes::FixedRoom2D::Cursor &get_cursor_ref();
            void suspend();
            void resume();
            void show();
            void hide();
            void initialize();
            void update();
            void render(std::string this_rooms_dictionary_name__this_injection_is_temporary_measure="[unset-this_rooms_dictionary_name__this_injection_is_temporary_measure]");
            void move_cursor(float distance_x=0.0, float distance_y=0.0, std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities_in_this_room={});
            void reset_cursor_to_default();
         };
      }
   }
}



