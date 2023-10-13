

#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderer.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


Carousel::Carousel(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , elements(elements)
{
}


Carousel::~Carousel()
{
}


void Carousel::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Carousel::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Carousel::set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements)
{
   this->elements = elements;
}


AllegroFlare::BitmapBin* Carousel::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* Carousel::get_font_bin() const
{
   return font_bin;
}


std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> Carousel::get_elements() const
{
   return elements;
}


void Carousel::update()
{
   for (auto &element : elements) element->update();
   return;
}

void Carousel::render()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Carousel::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::render: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Carousel::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::render: error: guard \"font_bin\" not met");
   }
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer renderer(bitmap_bin, font_bin);
   for (auto &element : elements) renderer.render(element);
   return;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


