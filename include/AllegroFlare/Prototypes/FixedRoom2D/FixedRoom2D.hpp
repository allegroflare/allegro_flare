#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/RoomDictionary.hpp>
#include <vector>


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
            AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary room_dictionary;
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities;
            float cursor_x;
            float cursor_y;
            bool initialized;

         public:
            FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            ~FixedRoom2D();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void initialize();
            void render();
            void update();
            void draw_cursor();
            void move_cursor_x(float distance=0.0);
            void move_cursor_y(float distance=0.0);
         };
      }
   }
}



