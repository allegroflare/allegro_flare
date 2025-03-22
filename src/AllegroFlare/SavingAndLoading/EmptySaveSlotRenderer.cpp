

#include <AllegroFlare/SavingAndLoading/EmptySaveSlotRenderer.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SavingAndLoading
{


EmptySaveSlotRenderer::EmptySaveSlotRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::string text_label)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , text_label(text_label)
   , width(DEFAULT_WIDTH)
   , height(DEFAULT_HEIGHT)
{
}


EmptySaveSlotRenderer::~EmptySaveSlotRenderer()
{
}


void EmptySaveSlotRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void EmptySaveSlotRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void EmptySaveSlotRenderer::set_text_label(std::string text_label)
{
   this->text_label = text_label;
}


void EmptySaveSlotRenderer::set_width(float width)
{
   this->width = width;
}


void EmptySaveSlotRenderer::set_height(float height)
{
   this->height = height;
}


std::string EmptySaveSlotRenderer::get_text_label() const
{
   return text_label;
}


float EmptySaveSlotRenderer::get_width() const
{
   return width;
}


float EmptySaveSlotRenderer::get_height() const
{
   return height;
}


void EmptySaveSlotRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::render]: error: guard \"font_bin\" not met");
   }
   // TODO: Clean this up
   float x = 0; // TODO: Factor out x
   float y = 0; // TODO: Factor out y
   float screenshot_width = 1920/9;
   float screenshot_x_padding = 20;
   float screenshot_height = 1080/9;
   //float x = 1920/2;
   //float y = 1080/3;
   ALLEGRO_FONT *location_name_font = obtain_location_name_font();
   float location_name_font_line_height = al_get_font_line_height(location_name_font);
   ALLEGRO_FONT *details_font = obtain_details_font();
   float details_font_line_height = al_get_font_line_height(details_font);
   //float h_location_name_font_line_height = al_get_font_line_height(location_name_font)/2;
   //float text_width = al_get_text_width(font, quote.c_str());
   //float text_height = al_get_font_line_height(font);
   float h_text_width = width/2;
   float h_text_height = height/2;
   AllegroFlare::Vec2D padding = {0, 0};
   float cumulative_line_spacing = 0;

   float text_x = x + screenshot_width + screenshot_x_padding*2;
   float text_y = y + 12;
   ALLEGRO_COLOR fill_color = al_color_html("1e2325"); // ALLEGRO_COLOR{0.13, 0.13, 0.13, 1.0};
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.35, 0.35, 0.35, 1.0};
   ALLEGRO_COLOR border_color = al_color_html("292e32"); // ALLEGRO_COLOR{0.13*2, 0.13*2, 0.13*2, 1.0};

   { // fill and border
      // Draw the fill
      al_draw_filled_rounded_rectangle(
         x - padding.x,
         y - padding.y,
         x + width + padding.x,
         y + height + padding.y,
         8.0f,
         8.0f,
         fill_color
      );

      // Draw the border
      al_draw_rounded_rectangle(
         x - padding.x,
         y - padding.y,
         x + width + padding.x,
         y + height + padding.y,
         8.0f,
         8.0f,
         border_color,
         3.0f
      );
   }

   cumulative_line_spacing = 0;
   { // save data text
      // The location of the save
      al_draw_text(
         details_font,
         text_color,
         width/2,
         height/2-details_font_line_height / 2,
         ALLEGRO_ALIGN_CENTER,
         text_label.c_str()
      );
   }

   return;
}

ALLEGRO_FONT* EmptySaveSlotRenderer::obtain_location_name_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::obtain_location_name_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::obtain_location_name_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Oswald-Medium.ttf -54");
}

ALLEGRO_FONT* EmptySaveSlotRenderer::obtain_details_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::obtain_details_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer::obtain_details_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("RobotoCondensed-Regular.ttf -32");
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


