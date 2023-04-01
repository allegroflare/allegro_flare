#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Storyboard.hpp>
#include <AllegroFlare/StoryboardPageFactory.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class StoryboardFactory
   {
   private:
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::StoryboardPageFactory page_factory;

   protected:


   public:
      StoryboardFactory(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
      ~StoryboardFactory();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
      AllegroFlare::Screens::Storyboard* create_images_storyboard_screen(std::vector<ALLEGRO_BITMAP*> source_bitmaps={}, int button_font_size=-40);
      AllegroFlare::Screens::Storyboard* create_advancing_text_storyboard_screen(std::vector<std::string> pages_text={}, int button_font_size=-40, float page_top_padding=400, float page_left_padding=400, float page_right_padding=400, int page_text_font_size=-40, std::string page_text_font_name="Inter-Medium.ttf", float page_text_line_height_multiplier=1.5);
   };
}



