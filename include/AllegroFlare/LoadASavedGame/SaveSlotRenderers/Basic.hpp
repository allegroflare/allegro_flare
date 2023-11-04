#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlotRenderers
      {
         class Basic
         {
         private:
            AllegroFlare::FontBin* font_bin;
            float width;
            float height;
            std::string save_name;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            Basic(AllegroFlare::FontBin* font_bin=nullptr, std::string save_name="Saved Game");
            ~Basic();

            void set_width(float width);
            void set_height(float height);
            float get_width() const;
            float get_height() const;
            void render();
         };
      }
   }
}



