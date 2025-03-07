#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlotRenderers
      {
         class Common
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::string location_of_save;
            std::string date_and_time_of_save;
            float x;
            float y;
            float width;
            float height;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            Common(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string location_of_save="Location of Save", std::string date_and_time_of_save="12/14/2024 3:20PM");
            ~Common();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_location_of_save(std::string location_of_save);
            void set_date_and_time_of_save(std::string date_and_time_of_save);
            void set_x(float x);
            void set_y(float y);
            void set_width(float width);
            void set_height(float height);
            std::string get_location_of_save() const;
            std::string get_date_and_time_of_save() const;
            float get_x() const;
            float get_y() const;
            float get_width() const;
            float get_height() const;
            void render();
         };
      }
   }
}



