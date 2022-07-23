#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Cursor.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/RoomDictionary.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class FixedRoom2D
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary room_dictionary;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary;
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper;
            AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor;
            bool initialized;

         public:
            FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            ~FixedRoom2D();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_room_dictionary(AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary room_dictionary);
            AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary get_room_dictionary();
            void initialize();
            void update();
            void render();
            void interact_cursor();
            void move_cursor(float distance_x=0.0, float distance_y=0.0);
         };
      }
   }
}



