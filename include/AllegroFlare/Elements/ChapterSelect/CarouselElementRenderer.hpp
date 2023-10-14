#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <string>
#include <utility>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class CarouselElementRenderer
         {
         public:
            static constexpr char* DEFAULT_FONT_IDENTIFIER = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_FONT_SIZE = -46;

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::string element_font_identifier;
            int element_font_size;

         protected:


         public:
            CarouselElementRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string element_font_identifier=DEFAULT_FONT_IDENTIFIER, int element_font_size=DEFAULT_FONT_SIZE);
            ~CarouselElementRenderer();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_element_font_identifier(std::string element_font_identifier);
            void set_element_font_size(int element_font_size);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_element_font_identifier() const;
            int get_element_font_size() const;
            void render(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element=nullptr);
            std::pair<float, float> calculate_dimensions(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element=nullptr);
            std::pair<float, float> render_or_calculate_dimensions(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element=nullptr, bool only_calculate_dimensions=false);
            std::pair<float, float> render_or_calculate_dimensions_for__ThumbnailWithLabel(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel* element=nullptr, bool only_calculate_dimensions=false);
            std::pair<float, float> render_or_calculate_dimensions_for__ThumbnailWithLabelUnlockable(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable* element=nullptr, bool only_calculate_dimensions=false);
         };
      }
   }
}



