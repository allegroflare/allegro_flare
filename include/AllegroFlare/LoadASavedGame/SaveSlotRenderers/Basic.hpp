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
            float x;
            float y;
            float width;
            float height;
            std::string save_name;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            Basic(AllegroFlare::FontBin* font_bin=nullptr, std::string save_name="Saved Game");
            ~Basic();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_x(float x);
            void set_y(float y);
            void set_width(float width);
            void set_height(float height);
            void set_save_name(std::string save_name);
            float get_x() const;
            float get_y() const;
            float get_width() const;
            float get_height() const;
            std::string get_save_name() const;
            void render();
         };
      }
   }
}



