

#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderer.hpp>
#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


Carousel::Carousel(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , elements({})
   , rotate_carousel_sound_effect_identifier("Carousel::rotate_carousel")
   , focused_element_position(0)
   , element_dimensions({})
   , element_dimensions_refreshed(false)
   , camera()
   , camera_target()
{
}


Carousel::~Carousel()
{
}


void Carousel::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Carousel::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Carousel::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Carousel::set_rotate_carousel_sound_effect_identifier(std::string rotate_carousel_sound_effect_identifier)
{
   this->rotate_carousel_sound_effect_identifier = rotate_carousel_sound_effect_identifier;
}


void Carousel::set_camera(AllegroFlare::Placement2D camera)
{
   this->camera = camera;
}


void Carousel::set_camera_target(AllegroFlare::Placement2D camera_target)
{
   this->camera_target = camera_target;
}


AllegroFlare::EventEmitter* Carousel::get_event_emitter() const
{
   return event_emitter;
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


std::string Carousel::get_rotate_carousel_sound_effect_identifier() const
{
   return rotate_carousel_sound_effect_identifier;
}


AllegroFlare::Placement2D Carousel::get_camera() const
{
   return camera;
}


AllegroFlare::Placement2D Carousel::get_camera_target() const
{
   return camera_target;
}


void Carousel::set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements)
{
   this->elements = elements;
   element_dimensions.clear();
   element_dimensions_refreshed = false;
   focused_element_position = 0;
   return;
}

int Carousel::get_num_elements()
{
   return elements.size();
}

void Carousel::rotate_carousel_left()
{
   if (elements.empty()) return;
   bool rotation_was_successful = true;
   focused_element_position -= 1; if (focused_element_position < 0) focused_element_position += elements.size();
   if (rotation_was_successful) { emit_rotation_sound_effect(); reposition_camera_position_to_focused_element(); } return;
}

void Carousel::rotate_carousel_right()
{
   if (elements.empty()) return;

   bool rotation_was_successful = true;

   focused_element_position += 1;
   if (focused_element_position >= elements.size()) focused_element_position -= elements.size();

   if (rotation_was_successful)
   {
      emit_rotation_sound_effect();
      reposition_camera_position_to_focused_element();
   }
   return;
}

void Carousel::reposition_camera_position_to_focused_element()
{
   camera_target.position.x = get_element_x_position_for(focused_element_position);
   return;
}

void Carousel::update_camera_position()
{
   float refresh_rate = 0.185f;
   camera.position.x = (camera_target.position.x - camera.position.x) * refresh_rate + camera.position.x;
}

void Carousel::update()
{
   for (auto &element : elements) element->update();
   update_camera_position();
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
   list_element_placement.align = AllegroFlare::Vec2D(0.5, 0.5);
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer renderer(bitmap_bin, font_bin);
   int position = 0;
   for (auto &element : elements)
   {
      std::tuple<float, float, float, float> element_dimensions = get_element_dimensions(element);

      list_element_placement.position.x = std::get<0>(element_dimensions);
      list_element_placement.position.y = std::get<1>(element_dimensions);
      list_element_placement.size.x = std::get<2>(element_dimensions);
      list_element_placement.size.y = std::get<3>(element_dimensions);

      list_element_placement.start_transform();
      renderer.render(element);
      // for debugging
      //al_draw_rectangle(
            //0,
            //0,
            //list_element_placement.size.x,
            //list_element_placement.size.y,
            //ALLEGRO_COLOR{0.6, 0.2, 0.2, 0.2},
            //2.0f
         //);
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
   std::tuple<float, float, float, float> this_element_dimensions = get_element_dimensions_at_position(position);
   return std::get<0>(this_element_dimensions);
}

AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* Carousel::get_element_at_position(int position)
{
   if (!((position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_at_position]: error: guard \"(position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_at_position: error: guard \"(position >= 0)\" not met");
   }
   if (!((position <= elements.size())))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_at_position]: error: guard \"(position <= elements.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_at_position: error: guard \"(position <= elements.size())\" not met");
   }
   return elements[position];
}

std::tuple<float, float, float, float> Carousel::get_element_dimensions_at_position(int position)
{
   if (!((position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_dimensions_at_position]: error: guard \"(position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_dimensions_at_position: error: guard \"(position >= 0)\" not met");
   }
   if (!((position <= elements.size())))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_dimensions_at_position]: error: guard \"(position <= elements.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_dimensions_at_position: error: guard \"(position <= elements.size())\" not met");
   }
   if (!(element_dimensions_refreshed))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_dimensions_at_position]: error: guard \"element_dimensions_refreshed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_dimensions_at_position: error: guard \"element_dimensions_refreshed\" not met");
   }
   AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element = get_element_at_position(position);
   if (element_dimensions.count(element) == 0)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::ChapterSelect::Carousel::get_element_dimensions_at_position",
            "Unexpected error: Could not find element_dimensions on for this element."
         );
   }
   return element_dimensions[element];
}

std::tuple<float, float, float, float> Carousel::get_element_dimensions(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[Carousel::get_element_dimensions]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::get_element_dimensions: error: guard \"element\" not met");
   }
   if (element_dimensions.count(element) == 0)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::ChapterSelect::Carousel::get_element_dimensions_at_position",
            "Unexpected error: Could not find element_dimensions on for this element."
         );
   }
   return element_dimensions[element];
}

void Carousel::refresh_element_dimensions()
{
   element_dimensions.clear();
   float arbitrary_element_spacing = 1200;
   float cursor_x = 0;
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer renderer(bitmap_bin, font_bin);
   for (auto &element : elements)
   {
      // TODO: Use Renderer and calculate dimensions on these elements
      std::pair<float, float> this_element_dimensions = renderer.calculate_dimensions(element);
      float element_width = this_element_dimensions.first;
      float element_height = this_element_dimensions.second; //200;
      float element_spacing = 80; // TODO: make this a property on the class

      element_dimensions[element] = std::make_tuple(cursor_x, 0, element_width, element_height);

      cursor_x += element_width + element_spacing;
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

void Carousel::emit_rotation_sound_effect()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Carousel::emit_rotation_sound_effect]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Carousel::emit_rotation_sound_effect: error: guard \"event_emitter\" not met");
   }
   // TODO: test this event emission
   event_emitter->emit_play_sound_effect_event(rotate_carousel_sound_effect_identifier);
   return;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


