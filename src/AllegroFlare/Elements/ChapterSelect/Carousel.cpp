

#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderer.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


Carousel::Carousel(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, int focused_element_position)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , elements({})
   , focused_element_position(focused_element_position)
   , element_dimensions({})
   , element_dimensions_refreshed(false)
   , camera()
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


void Carousel::set_focused_element_position(int focused_element_position)
{
   this->focused_element_position = focused_element_position;
}


void Carousel::set_camera(AllegroFlare::Placement2D camera)
{
   this->camera = camera;
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


int Carousel::get_focused_element_position() const
{
   return focused_element_position;
}


AllegroFlare::Placement2D Carousel::get_camera() const
{
   return camera;
}


void Carousel::set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements)
{
   this->elements = elements;
   element_dimensions.clear();
   element_dimensions_refreshed = false;
   focused_element_position = 0;
   return;
}

void Carousel::rotate_carousel_left()
{
   if (elements.empty()) return;

   focused_element_position -= 1;
   if (focused_element_position < 0) focused_element_position += elements.size();

   reposition_camera_position_to_focused_element();
   return;
}

void Carousel::rotate_carousel_right()
{
   if (elements.empty()) return;

   focused_element_position += 1;
   if (focused_element_position >= elements.size()) focused_element_position -= elements.size();

   reposition_camera_position_to_focused_element();
   return;
}

void Carousel::reposition_camera_position_to_focused_element()
{
   camera.position.x = get_element_x_position_for(focused_element_position);
   return;
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
   camera.start_reverse_transform();
   AllegroFlare::Placement2D list_element_placement;
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer renderer(bitmap_bin, font_bin);
   int position = 0;
   for (auto &element : elements)
   {
      list_element_placement.position.x = get_element_x_position_for(position);
      list_element_placement.start_transform();
      renderer.render(element);
      list_element_placement.restore_transform();
      position++;
   }
   camera.restore_transform();
   return;
}

float Carousel::get_element_x_position_for(int position)
{
   if (!((position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_x_position_for]: error: guard \"(position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_x_position_for: error: guard \"(position >= 0)\" not met");
   }
   if (!((position <= elements.size())))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_x_position_for]: error: guard \"(position <= elements.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_x_position_for: error: guard \"(position <= elements.size())\" not met");
   }
   if (!(element_dimensions_refreshed))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_x_position_for]: error: guard \"element_dimensions_refreshed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_x_position_for: error: guard \"element_dimensions_refreshed\" not met");
   }
   float arbitrary_element_spacing = 1200;
   return position * arbitrary_element_spacing;
}

void Carousel::refresh_element_dimensions()
{
   element_dimensions.clear();
   float arbitrary_element_spacing = 1200;
   for (auto &element : elements)
   {
      // TODO: Use Renderer and calculate dimensions on these elements
      element_dimensions[element] = std::make_pair(arbitrary_element_spacing, 200.0f);
   }

   // Sanity check
   if (element_dimensions.size() != elements.size())
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::ChapterSelect::Carousel",
            "Expecting the number of element_dimensions to match number of elements. Expecting unique elements in "
               "the carousel that can be mapped to dimensions, but elements contains a non-unique list."
         );
   }
   element_dimensions_refreshed = true;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


