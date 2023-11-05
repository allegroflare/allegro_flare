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
         class Empty
         {
         private:
            AllegroFlare::FontBin* font_bin;
            float x;
            float y;
            float width;
            float height;
            std::string text;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            Empty(AllegroFlare::FontBin* font_bin=nullptr, std::string text="Empty");
            ~Empty();

            void set_x(float x);
            void set_y(float y);
            void set_width(float width);
            void set_height(float height);
            float get_x() const;
            float get_y() const;
            float get_width() const;
            float get_height() const;
            void render();
         };
      }
   }
}



