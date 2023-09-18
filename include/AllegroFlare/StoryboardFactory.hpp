#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
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
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::ModelBin* model_bin;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::StoryboardPageFactory page_factory;

   protected:


   public:
      StoryboardFactory();
      ~StoryboardFactory();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
      void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
      AllegroFlare::Screens::Storyboard* create_images_storyboard_screen(std::vector<ALLEGRO_BITMAP*> source_bitmaps={}, int button_font_size=-40);
      AllegroFlare::Screens::Storyboard* create_advancing_text_storyboard_screen(std::vector<std::string> pages_text={}, int button_font_size=-40, float page_top_padding=400, float page_left_padding=400, float page_right_padding=400, int page_text_font_size=AllegroFlare::Elements::StoryboardPages::AdvancingText::DEFAULT_FONT_SIZE, std::string page_text_font_name=AllegroFlare::Elements::StoryboardPages::AdvancingText::DEFAULT_FONT_NAME, float page_text_line_height_multiplier=1.5);
   };
}



