#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/Elements/ChapterSelect/PaginationBar.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class ChapterSelect
         {
         public:
            static constexpr char* DEFAULT_TITLE_FONT_IDENTIFIER = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_TITLE_FONT_SIZE = -46;
            static constexpr char* DEFAULT_CAROUSEL_ELEMENT_FONT_IDENTIFIER = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_CAROUSEL_ELEMENT_FONT_SIZE = -46;
            static constexpr char* DEFAULT_CAROUSEL_SOUND_EFFECT_IDENTIFIER = (char*)"ChapterSelect::ChapterSelect::rotate_carousel";

         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Elements::ChapterSelect::Carousel carousel;
            AllegroFlare::Elements::ChapterSelect::PaginationBar pagination_bar;
            std::string title_font_identifier;
            int title_font_size;
            bool initialized;
            void refresh_pagination_bar_elements();
            void refresh_cursor_position_on_pagination_bar();
            ALLEGRO_FONT* obtain_title_font();

         protected:


         public:
            ChapterSelect(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            ~ChapterSelect();

            void set_carousel(AllegroFlare::Elements::ChapterSelect::Carousel carousel);
            void set_pagination_bar(AllegroFlare::Elements::ChapterSelect::PaginationBar pagination_bar);
            void set_title_font_identifier(std::string title_font_identifier);
            void set_title_font_size(int title_font_size);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::Elements::ChapterSelect::Carousel get_carousel() const;
            AllegroFlare::Elements::ChapterSelect::PaginationBar get_pagination_bar() const;
            std::string get_title_font_identifier() const;
            int get_title_font_size() const;
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void set_rotate_carousel_sound_effect_identifier(std::string rotate_carousel_sound_effect_identifier=DEFAULT_CAROUSEL_SOUND_EFFECT_IDENTIFIER);
            void set_carousel_element_font_identifier(std::string carousel_element_font_identifier=DEFAULT_CAROUSEL_ELEMENT_FONT_IDENTIFIER);
            void set_carousel_element_font_size(int carousel_element_font_size=DEFAULT_CAROUSEL_ELEMENT_FONT_SIZE);
            void initialize();
            void set_carousel_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> carousel_elements={});
            bool has_elements();
            bool has_no_elements();
            AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* get_focused_carousel_element();
            void update();
            void render();
            void rotate_carousel_right();
            void rotate_carousel_left();
            void set_pagination_bar_elements(std::vector<bool> elements={});
            void set_pagination_bar_element_at(int position=0, bool value=false);
            void draw_title_text();
         };
      }
   }
}



