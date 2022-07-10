#pragma once


#include <AllegroFlare/Elements/StoryboardPages/AdvancingText.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Storyboard.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class StoryboardFactory
   {
   private:
      AllegroFlare::FontBin* font_bin;

   public:
      StoryboardFactory(AllegroFlare::FontBin* font_bin=nullptr);
      ~StoryboardFactory();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      AllegroFlare::Elements::StoryboardPages::Text* create_text_page(std::string text="[unset-text]");
      AllegroFlare::Elements::StoryboardPages::AdvancingText* create_advancing_text_page(std::string text="[unset-text]");
      AllegroFlare::Elements::StoryboardPages::Image* create_image_page(ALLEGRO_BITMAP* image=nullptr);
      AllegroFlare::Screens::Storyboard* create_advancing_text_storyboard_screen(AllegroFlare::EventEmitter* event_emitter=nullptr, std::vector<std::string> pages_text={}, int button_font_size=-40, float page_top_padding=400, float page_left_padding=400, float page_right_padding=400, int page_text_font_size=-40, float page_text_line_height_multiplier=1.5);
   };
}



