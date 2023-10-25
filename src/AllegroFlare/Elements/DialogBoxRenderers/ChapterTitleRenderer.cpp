

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


ChapterTitleRenderer::ChapterTitleRenderer(AllegroFlare::FontBin* font_bin, std::string title_text, float age)
   : font_bin(font_bin)
   , title_text(title_text)
   , age(age)
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
   float x = 1920/2;
   float y = 1080/9*4;
   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, title_text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};

   /*
   al_draw_rounded_rectangle(
      x-h_text_width - padding.x,
      y-h_text_height - padding.y,
      x+h_text_width + padding.x,
      y+h_text_height + padding.y,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{1, 1, 1, 1},
      8.0f
   );
   */
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, title_text.c_str());
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


