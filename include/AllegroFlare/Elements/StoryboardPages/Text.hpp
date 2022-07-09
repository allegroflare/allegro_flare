#pragma once


#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class Text : public AllegroFlare::Elements::StoryboardPages::Base
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::string text;

         public:
            Text(AllegroFlare::FontBin* font_bin=nullptr, std::string text="");
            virtual ~Text();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_text(std::string text);
            std::string get_text();
            virtual void start() override;
            virtual void update() override;
            virtual void render() override;
            virtual void advance() override;
            ALLEGRO_FONT* obtain_font();
         };
      }
   }
}



