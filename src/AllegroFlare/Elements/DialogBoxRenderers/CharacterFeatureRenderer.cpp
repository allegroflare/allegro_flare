

#include <AllegroFlare/Elements/DialogBoxRenderers/CharacterFeatureRenderer.hpp>

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


CharacterFeatureRenderer::CharacterFeatureRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::string character_name, std::string description, std::string character_image_identifier, float age)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , character_name(character_name)
   , description(description)
   , character_image_identifier(character_image_identifier)
   , age(age)
{
}


CharacterFeatureRenderer::~CharacterFeatureRenderer()
{
}


void CharacterFeatureRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::render: error: guard \"font_bin\" not met");
   }
   // Draw Title
   float title_x = 875;
   float title_y = 500;
   float y_gutter = 60;
   float description_max_width = 700;
   ALLEGRO_FONT *character_name_font = obtain_character_name_font();
   ALLEGRO_FONT *font = obtain_description_font();
   //float text_width = al_get_text_width(character_name_font, quote.c_str());
   float text_height = al_get_font_line_height(character_name_font);
   //float h_text_width = text_width/2;
   //float h_text_height = text_height/2;
   //AllegroFlare::Vec2D padding = {30, 20};

   al_draw_text(
      character_name_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      title_x,
      title_y-text_height,
      ALLEGRO_ALIGN_RIGHT,
      character_name.c_str()
   );

   al_draw_multiline_text(
      font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      title_x,
      title_y+y_gutter,
      description_max_width,
      al_get_font_line_height(font),
      ALLEGRO_ALIGN_RIGHT,
      description.c_str()
   );

   return;
}

ALLEGRO_FONT* CharacterFeatureRenderer::obtain_character_name_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::obtain_character_name_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::obtain_character_name_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -72");
}

ALLEGRO_FONT* CharacterFeatureRenderer::obtain_description_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::obtain_description_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::obtain_description_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -42");
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


