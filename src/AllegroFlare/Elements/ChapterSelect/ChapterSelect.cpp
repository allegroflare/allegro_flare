

#include <AllegroFlare/Elements/ChapterSelect/ChapterSelect.hpp>

#include <allegro5/allegro_font.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


ChapterSelect::ChapterSelect(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::Elements::ChapterSelect::Carousel carousel, AllegroFlare::Elements::ChapterSelect::PaginationBar pagination_bar)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , carousel(carousel)
   , pagination_bar(pagination_bar)
   , initialized(false)
{
}


ChapterSelect::~ChapterSelect()
{
}


void ChapterSelect::set_carousel(AllegroFlare::Elements::ChapterSelect::Carousel carousel)
{
   this->carousel = carousel;
}


void ChapterSelect::set_pagination_bar(AllegroFlare::Elements::ChapterSelect::PaginationBar pagination_bar)
{
   this->pagination_bar = pagination_bar;
}


AllegroFlare::BitmapBin* ChapterSelect::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* ChapterSelect::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Elements::ChapterSelect::Carousel ChapterSelect::get_carousel() const
{
   return carousel;
}


AllegroFlare::Elements::ChapterSelect::PaginationBar ChapterSelect::get_pagination_bar() const
{
   return pagination_bar;
}


void ChapterSelect::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void ChapterSelect::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void ChapterSelect::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::initialize: error: guard \"(!initialized)\" not met");
   }
   carousel.set_bitmap_bin(bitmap_bin);
   carousel.set_font_bin(font_bin);
   initialized = true;
   return;
}

void ChapterSelect::set_carousel_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> carousel_elements)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::set_carousel_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::set_carousel_elements: error: guard \"initialized\" not met");
   }
   carousel.set_elements(carousel_elements);
   carousel.refresh_element_dimensions();
   refresh_pagination_bar_elements();
   refresh_cursor_position_on_pagination_bar();
   return;
}

bool ChapterSelect::has_no_elements()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::has_no_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::has_no_elements: error: guard \"initialized\" not met");
   }
   return (carousel.get_num_elements() == 0);
}

void ChapterSelect::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::update: error: guard \"initialized\" not met");
   }
   carousel.update();
   pagination_bar.update();
   return;
}

void ChapterSelect::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::render: error: guard \"initialized\" not met");
   }
   // Draw the carousel
   AllegroFlare::Placement2D carousel_placement;
   carousel_placement.position.x = 1920/2;
   carousel_placement.position.y = 1080/2 - 30;
   carousel_placement.size = { 0, 0 };
   carousel_placement.start_transform();
   carousel.render();
   carousel_placement.restore_transform();

   // Draw the pagination bar
   AllegroFlare::Placement2D pagination_bar_placement;
   pagination_bar_placement.position.x = 1920/2;
   pagination_bar_placement.position.y = 1080/5*4 - 50;
   pagination_bar_placement.size = { 0, 0 };
   pagination_bar_placement.start_transform();
   pagination_bar.render();
   pagination_bar_placement.restore_transform();

   draw_title_text();
   return;
}

void ChapterSelect::rotate_carousel_right()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::rotate_carousel_right]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::rotate_carousel_right: error: guard \"initialized\" not met");
   }
   carousel.rotate_carousel_right();
   refresh_cursor_position_on_pagination_bar();
   return;
}

void ChapterSelect::rotate_carousel_left()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::rotate_carousel_left]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::rotate_carousel_left: error: guard \"initialized\" not met");
   }
   carousel.rotate_carousel_left();
   refresh_cursor_position_on_pagination_bar();
   return;
}

void ChapterSelect::draw_title_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::draw_title_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::draw_title_text: error: guard \"initialized\" not met");
   }
   ALLEGRO_FONT *title_font = obtain_title_font();
   al_draw_text(title_font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 100, ALLEGRO_ALIGN_LEFT, "CHAPTER SELECT");
   return;
}

void ChapterSelect::refresh_pagination_bar_elements()
{
   // TODO: Find a mechanism to store and obtain the "status" of a Chapter as hidden or unhidden, etc
   std::vector<bool> pagination_bar_elements(carousel.get_num_elements(), true);
   pagination_bar.set_elements(pagination_bar_elements);
   pagination_bar.fit_placement_width_and_height();
   return;
}

void ChapterSelect::set_pagination_bar_element_at(int position, bool value)
{
   pagination_bar.set_element_at(position, value);
   return;
}

void ChapterSelect::refresh_cursor_position_on_pagination_bar()
{
   int focused_element_position = carousel.get_focused_element_position();
   pagination_bar.set_cursor_position(focused_element_position);
   return;
}

ALLEGRO_FONT* ChapterSelect::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::obtain_title_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -46");
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


