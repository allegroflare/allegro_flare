#pragma once


#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class Storyboard
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages;
         AllegroFlare::Elements::Backgrounds::Base* background;
         int button_font_size;
         intptr_t current_page_num;
         bool can_advance_to_next_page;
         float can_advance_started_at;
         bool finished;
         void render_next_button();
         ALLEGRO_FONT* obtain_next_button_font();

      protected:


      public:
         Storyboard(AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages={}, AllegroFlare::Elements::Backgrounds::Base* background=nullptr);
         ~Storyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_pages(std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages);
         void set_background(AllegroFlare::Elements::Backgrounds::Base* background);
         void set_button_font_size(int button_font_size);
         std::vector<AllegroFlare::Elements::StoryboardPages::Base *> get_pages() const;
         AllegroFlare::Elements::Backgrounds::Base* get_background() const;
         int get_button_font_size() const;
         intptr_t get_current_page_num() const;
         bool get_can_advance_to_next_page() const;
         float get_can_advance_started_at() const;
         bool get_finished() const;
         void update();
         void render();
         void reset();
         bool permit_advancing_page();
         bool deny_advancing_page();
         bool advance();
         bool advance_page();
         bool infer_has_no_pages();
         bool infer_at_last_page();
         bool infer_at_or_past_last_page();
         bool infer_at_last_advance();
         AllegroFlare::Elements::StoryboardPages::Base* infer_current_page();
      };
   }
}



