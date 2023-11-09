

#include <AllegroFlare/Elements/DialogBoxRenderers/IntertitleRenderer.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>
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


IntertitleRenderer::IntertitleRenderer(AllegroFlare::FontBin* font_bin, std::string text, int revealed_characters_count)
   : font_bin(font_bin)
   , text(text)
   , revealed_characters_count(revealed_characters_count)
   , surface_width(1920)
   , surface_height(1080)
   , top_padding(400)
   , left_padding(360)
   , right_padding(360)
   , bottom_padding(400)
   , line_height_multiplier(1.75f)
   , line_height_padding(0.0f)
   , font_name(DEFAULT_FONT_NAME)
   , font_size(DEFAULT_FONT_SIZE)
   , text_color(ALLEGRO_COLOR{1, 1, 1, 1})
{
}


IntertitleRenderer::~IntertitleRenderer()
{
}


void IntertitleRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void IntertitleRenderer::set_text(std::string text)
{
   this->text = text;
}


void IntertitleRenderer::set_revealed_characters_count(int revealed_characters_count)
{
   this->revealed_characters_count = revealed_characters_count;
}


void IntertitleRenderer::set_surface_width(float surface_width)
{
   this->surface_width = surface_width;
}


void IntertitleRenderer::set_surface_height(float surface_height)
{
   this->surface_height = surface_height;
}


void IntertitleRenderer::set_top_padding(float top_padding)
{
   this->top_padding = top_padding;
}


void IntertitleRenderer::set_left_padding(float left_padding)
{
   this->left_padding = left_padding;
}


void IntertitleRenderer::set_right_padding(float right_padding)
{
   this->right_padding = right_padding;
}


void IntertitleRenderer::set_bottom_padding(float bottom_padding)
{
   this->bottom_padding = bottom_padding;
}


void IntertitleRenderer::set_line_height_multiplier(float line_height_multiplier)
{
   this->line_height_multiplier = line_height_multiplier;
}


void IntertitleRenderer::set_line_height_padding(float line_height_padding)
{
   this->line_height_padding = line_height_padding;
}


void IntertitleRenderer::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void IntertitleRenderer::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void IntertitleRenderer::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


AllegroFlare::FontBin* IntertitleRenderer::get_font_bin() const
{
   return font_bin;
}


std::string IntertitleRenderer::get_text() const
{
   return text;
}


int IntertitleRenderer::get_revealed_characters_count() const
{
   return revealed_characters_count;
}


float IntertitleRenderer::get_surface_width() const
{
   return surface_width;
}


float IntertitleRenderer::get_surface_height() const
{
   return surface_height;
}


float IntertitleRenderer::get_top_padding() const
{
   return top_padding;
}


float IntertitleRenderer::get_left_padding() const
{
   return left_padding;
}


float IntertitleRenderer::get_right_padding() const
{
   return right_padding;
}


float IntertitleRenderer::get_bottom_padding() const
{
   return bottom_padding;
}


float IntertitleRenderer::get_line_height_multiplier() const
{
   return line_height_multiplier;
}


float IntertitleRenderer::get_line_height_padding() const
{
   return line_height_padding;
}


std::string IntertitleRenderer::get_font_name() const
{
   return font_name;
}


int IntertitleRenderer::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR IntertitleRenderer::get_text_color() const
{
   return text_color;
}


void IntertitleRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[IntertitleRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("IntertitleRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[IntertitleRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("IntertitleRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[IntertitleRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("IntertitleRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *text_font = obtain_font();

   // Draw a backfill (consider alternative options like graphic or fadeout gradient on top/bottom)



   al_draw_filled_rectangle(
      0,
      top_padding / 2,
      surface_width,
      surface_height - bottom_padding / 2,
      ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.7}
   );

   // Draw the text
   std::string revealed_text = generate_revealed_text();
   if (!revealed_text.empty())
   {
      float box_width = surface_width - (left_padding + right_padding);
      al_draw_multiline_text(
         text_font,
         text_color,
         left_padding,
         top_padding,
         box_width,
         al_get_font_line_height(text_font)*line_height_multiplier + line_height_padding,
         0,
         revealed_text.c_str()
      );
   }

   return;
}

std::string IntertitleRenderer::generate_revealed_text()
{
   return text.substr(0, revealed_characters_count);
}

void IntertitleRenderer::draw_gradient_prim(float y1, float y2, ALLEGRO_COLOR top_color, ALLEGRO_COLOR bottom_color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[IntertitleRenderer::draw_gradient_prim]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("IntertitleRenderer::draw_gradient_prim: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!((y2 > y1)))
   {
      std::stringstream error_message;
      error_message << "[IntertitleRenderer::draw_gradient_prim]: error: guard \"(y2 > y1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("IntertitleRenderer::draw_gradient_prim: error: guard \"(y2 > y1)\" not met");
   }
   ALLEGRO_VERTEX v[4];
   float padding = 0;
   float w = surface_width;
   float h = y2-y1;

   v[0] = AllegroFlare::build_vertex(0+padding, y1+0+padding, 0, top_color, 0, 0);
   v[1] = AllegroFlare::build_vertex(w-padding, y1+0+padding, 0, top_color, 0, 0);
   v[2] = AllegroFlare::build_vertex(w-padding, y1+h-padding, 0, bottom_color, 0, 0);
   v[3] = AllegroFlare::build_vertex(0+padding, y1+h-padding, 0, bottom_color, 0, 0);

   // draw it to the surface
   al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
   return;
}

bool IntertitleRenderer::all_characters_are_revealed()
{
   return revealed_characters_count >= text.size();
}

ALLEGRO_FONT* IntertitleRenderer::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[IntertitleRenderer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("IntertitleRenderer::obtain_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* IntertitleRenderer::obtain_next_button_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[IntertitleRenderer::obtain_next_button_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("IntertitleRenderer::obtain_next_button_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size+20;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


