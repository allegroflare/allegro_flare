#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class ChapterTitleRenderer
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::string title_text;
            float age;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            ChapterTitleRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string title_text="[unset-title_text]", float age=999.0f);
            ~ChapterTitleRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_title_text(std::string title_text);
            void set_age(float age);
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_title_text() const;
            float get_age() const;
            void render();
         };
      }
   }
}



