#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/Elements/ChapterSelect/PaginationBar.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <vector>


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
            ALLEGRO_FONT* obtain_title_font();

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
            void set_carousel_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> carousel_elements={});
            bool has_no_elements();
            void update();
            void render();
            void rotate_carousel_right();
            void rotate_carousel_left();
            void draw_title_text();
            void refresh_pagination_bar_elements();
            void set_pagination_bar_element_at(int position=0, bool value=false);
            void refresh_cursor_position_on_pagination_bar();
         };
      }
   }
}



