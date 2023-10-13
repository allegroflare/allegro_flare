#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>
#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class CarouselElementRenderer
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;

         protected:


         public:
            CarouselElementRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            ~CarouselElementRenderer();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            void render_ThumbnailWithLabel(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel* element=nullptr);
            void render(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element=nullptr);
         };
      }
   }
}



