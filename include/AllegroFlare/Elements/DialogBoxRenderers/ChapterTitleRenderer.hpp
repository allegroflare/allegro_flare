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
         public:
            static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_FONT_SIZE = -52;

         private:
            AllegroFlare::FontBin* font_bin;
            std::string title_text;
            float age;
            float duration;
            std::string font_name;
            int font_size;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            ChapterTitleRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string title_text="[unset-title_text]", float age=999.0f, float duration=6.0f, std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE);
            ~ChapterTitleRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_title_text(std::string title_text);
            void set_age(float age);
            void set_duration(float duration);
            void set_font_name(std::string font_name);
            void set_font_size(int font_size);
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_title_text() const;
            float get_age() const;
            float get_duration() const;
            std::string get_font_name() const;
            int get_font_size() const;
            void render();
         };
      }
   }
}



