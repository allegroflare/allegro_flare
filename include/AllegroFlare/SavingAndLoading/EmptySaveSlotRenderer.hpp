#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class EmptySaveSlotRenderer
      {
      public:
         static constexpr int DEFAULT_WIDTH = 640;
         static constexpr int DEFAULT_HEIGHT = 155;

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::string text_label;
         float width;
         float height;
         ALLEGRO_FONT* obtain_location_name_font();
         ALLEGRO_FONT* obtain_details_font();

      protected:


      public:
         EmptySaveSlotRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string text_label="Empty");
         ~EmptySaveSlotRenderer();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_text_label(std::string text_label);
         void set_width(float width);
         void set_height(float height);
         std::string get_text_label() const;
         float get_width() const;
         float get_height() const;
         void render();
      };
   }
}



