#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/StoryboardPages/AdvancingText.hpp>
#include <AllegroFlare/Elements/StoryboardPages/ClubCattLogo.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>
#include <AllegroFlare/Elements/StoryboardPages/ImageWithAdvancingText.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   class StoryboardPageFactory
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::ModelBin* model_bin;

   protected:


   public:
      StoryboardPageFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
      ~StoryboardPageFactory();

      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_model_bin(AllegroFlare::ModelBin* model_bin);
      AllegroFlare::Elements::StoryboardPages::Text* create_text_page(std::string text="[unset-text]");
      AllegroFlare::Elements::StoryboardPages::AdvancingText* create_advancing_text_page(std::string text="[unset-text]");
      AllegroFlare::Elements::StoryboardPages::Image* create_image_page(ALLEGRO_BITMAP* image=nullptr);
      AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText* create_image_with_advancing_text_page(std::string image_identifier="[unset-image_identifier]", std::string text="[unset-text]");
      AllegroFlare::Elements::StoryboardPages::ClubCattLogo* create_clubcatt_logo_page();
   };
}



