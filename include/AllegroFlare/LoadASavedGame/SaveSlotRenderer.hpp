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

         void render(AllegroFlare::LoadASavedGame::SaveSlots::Base* save_slot=nullptr, float x=0, float y=0);
      };
   }
}



