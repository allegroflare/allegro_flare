#pragma once


#include <AllegroFlare/Elements/StoryboardPages/AdvancingText.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   class StoryboardPageFactory
   {
   private:
      AllegroFlare::FontBin* font_bin;

   protected:


   public:
      StoryboardPageFactory(AllegroFlare::FontBin* font_bin=nullptr);
      ~StoryboardPageFactory();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      AllegroFlare::Elements::StoryboardPages::Text* create_text_page(std::string text="[unset-text]");
      AllegroFlare::Elements::StoryboardPages::AdvancingText* create_advancing_text_page(std::string text="[unset-text]");
      AllegroFlare::Elements::StoryboardPages::Image* create_image_page(ALLEGRO_BITMAP* image=nullptr);
   };
}



