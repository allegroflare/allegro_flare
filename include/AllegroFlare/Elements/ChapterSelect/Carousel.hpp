#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class Carousel
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements;

         protected:


         public:
            Carousel(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements={});
            ~Carousel();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> get_elements() const;
            void update();
            void render();
         };
      }
   }
}



