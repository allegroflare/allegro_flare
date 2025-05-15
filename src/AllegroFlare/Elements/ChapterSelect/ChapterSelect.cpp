

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


ChapterSelect::ChapterSelect(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , carousel({})
   , pagination_bar()
   , title_font_identifier(DEFAULT_TITLE_FONT_IDENTIFIER)
   , title_font_size(DEFAULT_TITLE_FONT_SIZE)
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


void ChapterSelect::set_title_font_identifier(std::string title_font_identifier)
{
   this->title_font_identifier = title_font_identifier;
}


void ChapterSelect::set_title_font_size(int title_font_size)
{
   this->title_font_size = title_font_size;
}


AllegroFlare::EventEmitter* ChapterSelect::get_event_emitter() const
{
   return event_emitter;
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


std::string ChapterSelect::get_title_font_identifier() const
{
   return title_font_identifier;
}


int ChapterSelect::get_title_font_size() const
{
   return title_font_size;
}


void ChapterSelect::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_event_emitter]: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void ChapterSelect::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void ChapterSelect::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void ChapterSelect::set_rotate_carousel_sound_effect_identifier(std::string rotate_carousel_sound_effect_identifier)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_rotate_carousel_sound_effect_identifier]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_rotate_carousel_sound_effect_identifier]: error: guard \"(!initialized)\" not met");
   }
   carousel.set_rotate_carousel_sound_effect_identifier(rotate_carousel_sound_effect_identifier);
   return;
}

void ChapterSelect::set_carousel_element_font_identifier(std::string carousel_element_font_identifier)
{
   carousel.set_element_font_identifier(carousel_element_font_identifier);
   return;
}

void ChapterSelect::set_carousel_element_font_size(int carousel_element_font_size)
{
   carousel.set_element_font_size(carousel_element_font_size);
   return;
}

void ChapterSelect::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::initialize]: error: guard \"(!initialized)\" not met");
   }
   carousel.set_event_emitter(event_emitter);
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
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_carousel_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_carousel_elements]: error: guard \"initialized\" not met");
   }
   carousel.set_elements(carousel_elements);
   carousel.refresh_element_dimensions();
   refresh_pagination_bar_elements();
   refresh_cursor_position_on_pagination_bar();
   return;
}

bool ChapterSelect::has_elements()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::has_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::has_elements]: error: guard \"initialized\" not met");
   }
   return (carousel.get_num_elements() != 0);
}

bool ChapterSelect::has_no_elements()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::has_no_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::has_no_elements]: error: guard \"initialized\" not met");
   }
   return (carousel.get_num_elements() == 0);
}

AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* ChapterSelect::get_focused_carousel_element()
{
   if (!(has_elements()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::get_focused_carousel_element]: error: guard \"has_elements()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::get_focused_carousel_element]: error: guard \"has_elements()\" not met");
   }
   // TODO: Test this method
   return carousel.get_element_at_focused_element_position();
}

void ChapterSelect::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::update]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::render]: error: guard \"initialized\" not met");
   }
   // Draw the carousel
   AllegroFlare::Placement2D carousel_placement;
   carousel_placement.position.x = 1920/2;
   carousel_placement.position.y = 1080/2 - 30;
   carousel_placement.size = AllegroFlare::Vec2D{ 0, 0 };
   carousel_placement.start_transform();
   carousel.render();
   carousel_placement.restore_transform();

   // Draw the pagination bar
   AllegroFlare::Placement2D pagination_bar_placement;
   pagination_bar_placement.position.x = 1920/2;
   pagination_bar_placement.position.y = 1080/5*4 - 50;
   pagination_bar_placement.size = AllegroFlare::Vec2D{ 0, 0 };
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
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::rotate_carousel_right]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::rotate_carousel_right]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::rotate_carousel_left]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::rotate_carousel_left]: error: guard \"initialized\" not met");
   }
   carousel.rotate_carousel_left();
   refresh_cursor_position_on_pagination_bar();
   return;
}

void ChapterSelect::set_pagination_bar_elements(std::vector<bool> elements)
{
   if (!((elements.size() == pagination_bar.get_num_elements())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_pagination_bar_elements]: error: guard \"(elements.size() == pagination_bar.get_num_elements())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::set_pagination_bar_elements]: error: guard \"(elements.size() == pagination_bar.get_num_elements())\" not met");
   }
   pagination_bar.set_elements(elements);
   return;
}

void ChapterSelect::set_pagination_bar_element_at(int position, bool value)
{
   pagination_bar.set_element_at(position, value);
   return;
}

void ChapterSelect::draw_title_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::draw_title_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::draw_title_text]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Elements::ChapterSelect::ChapterSelect::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::ChapterSelect::obtain_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get(title_font_identifier + " " + std::to_string(title_font_size));
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


