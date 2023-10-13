

#include <AllegroFlare/Elements/ChapterSelect/ChapterSelect.hpp>

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


void ChapterSelect::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void ChapterSelect::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
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


void ChapterSelect::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ChapterSelect::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterSelect::initialize: error: guard \"(!initialized)\" not met");
   }
   return;
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
   return;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


