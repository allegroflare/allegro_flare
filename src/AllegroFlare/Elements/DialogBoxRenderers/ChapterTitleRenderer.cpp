

#include <AllegroFlare/Elements/DialogBoxRenderers/ChapterTitleRenderer.hpp>

#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxRenderers
{


ChapterTitleRenderer::ChapterTitleRenderer(AllegroFlare::FontBin* font_bin, std::string title_text, float age, float duration, std::string font_name, int font_size)
   : font_bin(font_bin)
   , title_text(title_text)
   , age(age)
   , duration(duration)
   , font_name(font_name)
   , font_size(font_size)
{
}


ChapterTitleRenderer::~ChapterTitleRenderer()
{
}


void ChapterTitleRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ChapterTitleRenderer::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void ChapterTitleRenderer::set_age(float age)
{
   this->age = age;
}


void ChapterTitleRenderer::set_duration(float duration)
{
   this->duration = duration;
}


void ChapterTitleRenderer::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void ChapterTitleRenderer::set_font_size(int font_size)
{
   this->font_size = font_size;
}


AllegroFlare::FontBin* ChapterTitleRenderer::get_font_bin() const
{
   return font_bin;
}


std::string ChapterTitleRenderer::get_title_text() const
{
   return title_text;
}


float ChapterTitleRenderer::get_age() const
{
   return age;
}


float ChapterTitleRenderer::get_duration() const
{
   return duration;
}


std::string ChapterTitleRenderer::get_font_name() const
{
   return font_name;
}


int ChapterTitleRenderer::get_font_size() const
{
   return font_size;
}


void ChapterTitleRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ChapterTitleRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterTitleRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ChapterTitleRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterTitleRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ChapterTitleRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterTitleRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ChapterTitleRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterTitleRenderer::render: error: guard \"font_bin\" not met");
   }
   float fade_in_duration = 2.0f;
   float fade_out_duration = 2.0f;
   float opacity = 1.0f;

   if (age <= fade_in_duration)
   {
      float normalized_fade_in = age / fade_in_duration;
      opacity = (normalized_fade_in);
   }
   else if (age >= (duration-fade_out_duration))
   {
      float end = duration;
      float start = duration - fade_out_duration;
      float in_pos = age - start;
      float length = end - start;
      float normalized = in_pos / length;

      opacity = (1.0 - normalized);
   }
   else if (age >= duration)
   {
      opacity = 0.0f;
   }

   ALLEGRO_FONT *font = obtain_font();
   float x = 1920/2;
   float y = 1080/2 - al_get_font_line_height(font)/2;
   float text_width = al_get_text_width(font, title_text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};

   ALLEGRO_COLOR color = ALLEGRO_COLOR{opacity, opacity, opacity, opacity};

   al_draw_text(font, color, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, title_text.c_str());

   float line_full_width = 300;
   float line_width = line_full_width * AllegroFlare::interpolator::slow_in_out(opacity);
   float h_line_width = line_width / 2;
   float y_offset = al_get_font_line_height(font);
   float line_thickness = 4.0f;
   al_draw_line(x-h_line_width, y+y_offset, x+h_line_width, y+y_offset, ALLEGRO_COLOR{1, 1, 1, 1}, line_thickness);

   return;
}

ALLEGRO_FONT* ChapterTitleRenderer::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ChapterTitleRenderer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterTitleRenderer::obtain_font: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


