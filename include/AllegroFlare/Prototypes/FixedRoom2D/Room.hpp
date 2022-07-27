#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Cursor.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <string>


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
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary;
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper;
            AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor;
            bool suspended;
            float suspended_at;
            bool initialized;

         public:
            Room(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary=nullptr);
            ~Room();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary=nullptr);
            void suspend();
            void resume();
            void show();
            void hide();
            void initialize();
            void update();
            void render();
            void interact_with_item_under_cursor();
            void move_cursor(float distance_x=0.0, float distance_y=0.0);
            void emit_interaction_event(std::string item_dictionary_name="[unset-item_dictionary_name]", float cursor_x=0.0, float cursor_y=0.0);
         };
      }
   }
}



