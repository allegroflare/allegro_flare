#pragma once


#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class StoryboardPlayer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages;
         intptr_t current_page_num;
         bool can_advance_to_next_page;
         float can_advance_started_at;
         bool finished;

      public:
         StoryboardPlayer(AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages={});
         ~StoryboardPlayer();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_pages(std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages);
         intptr_t get_current_page_num();
         bool get_can_advance_to_next_page();
         float get_can_advance_started_at();
         bool get_finished();
         void update();
         void render();
         void reset();
         bool permit_advancing_page();
         bool deny_advancing_page();
         bool advance();
         bool advance_page();
         void render_next_button();
         bool infer_at_last_page();
         bool infer_at_or_past_last_page();
         AllegroFlare::Elements::StoryboardPages::Base* infer_current_page();
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_next_button_font();
      };
   }
}



