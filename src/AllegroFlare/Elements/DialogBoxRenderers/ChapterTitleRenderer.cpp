

#include <AllegroFlare/Elements/DialogBoxRenderers/ChapterTitleRenderer.hpp>

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


ChapterTitleRenderer::ChapterTitleRenderer(AllegroFlare::FontBin* font_bin, std::string title_text, float age, float duration)
   : font_bin(font_bin)
   , title_text(title_text)
   , age(age)
   , duration(duration)
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

   float x = 1920/2;
   float y = 1080/9*4;
   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, title_text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};

   ALLEGRO_COLOR color = ALLEGRO_COLOR{opacity, opacity, opacity, opacity};

   al_draw_text(font, color, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, title_text.c_str());
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
   return font_bin->auto_get("Inter-Medium.ttf -52");
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


