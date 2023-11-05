#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      class SaveSlotRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         SaveSlotRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Hello!");
         ~SaveSlotRenderer();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         AllegroFlare::FontBin* get_font_bin() const;
         void render(AllegroFlare::LoadASavedGame::SaveSlots::Base* save_slot=nullptr, float x=1920/2, float y=1080/8);
      };
   }
}



