#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      class SaveSlotRenderer
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         float slot_width;
         float slot_height;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         SaveSlotRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, float slot_width=1920/2, float slot_height=1080/8);
         ~SaveSlotRenderer();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_slot_width(float slot_width);
         void set_slot_height(float slot_height);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::FontBin* get_font_bin() const;
         float get_slot_width() const;
         float get_slot_height() const;
         void render(AllegroFlare::LoadASavedGame::SaveSlots::Base* save_slot=nullptr, float x=1920/2, float y=1080/8);
      };
   }
}



