#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>
#include <AllegroFlare/Elements/ChapterSelect/PaginationBar.hpp>
#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class ChapterSelect
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Elements::ChapterSelect::Carousel carousel;
            AllegroFlare::Elements::ChapterSelect::PaginationBar pagination_bar;
            bool initialized;

         protected:


         public:
            ChapterSelect(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Elements::ChapterSelect::Carousel carousel={}, AllegroFlare::Elements::ChapterSelect::PaginationBar pagination_bar={});
            ~ChapterSelect();

            void set_carousel(AllegroFlare::Elements::ChapterSelect::Carousel carousel);
            void set_pagination_bar(AllegroFlare::Elements::ChapterSelect::PaginationBar pagination_bar);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::Elements::ChapterSelect::Carousel get_carousel() const;
            AllegroFlare::Elements::ChapterSelect::PaginationBar get_pagination_bar() const;
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void initialize();
            void update();
            void render();
         };
      }
   }
}



