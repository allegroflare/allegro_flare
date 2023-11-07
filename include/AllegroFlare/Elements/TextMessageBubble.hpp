#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class TextMessageBubble
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         float width;
         float height;
         bool callout_on_left;
         ALLEGRO_FONT* obtain_text_font();

      protected:


      public:
         TextMessageBubble(AllegroFlare::FontBin* font_bin=nullptr, std::string text="", float width=1, float height=1, bool callout_on_left=false);
         ~TextMessageBubble();

         void render();
      };
   }
}



