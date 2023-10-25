

#include <AllegroFlare/Elements/DialogBoxRenderers/CharacterFeatureRenderer.hpp>

#include <AllegroFlare/Placement2D.hpp>
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


CharacterFeatureRenderer::CharacterFeatureRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::string character_name, std::string description, std::string character_image_identifier, float duration, float age, std::string character_name_font_name, int character_name_font_size, std::string description_font_name, int description_font_size)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , character_name(character_name)
   , description(description)
   , character_image_identifier(character_image_identifier)
   , duration(duration)
   , age(age)
   , character_name_font_name(character_name_font_name)
   , character_name_font_size(character_name_font_size)
   , description_font_name(description_font_name)
   , description_font_size(description_font_size)
{
}


CharacterFeatureRenderer::~CharacterFeatureRenderer()
{
}


void CharacterFeatureRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void CharacterFeatureRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void CharacterFeatureRenderer::set_character_name(std::string character_name)
{
   this->character_name = character_name;
}


void CharacterFeatureRenderer::set_description(std::string description)
{
   this->description = description;
}


void CharacterFeatureRenderer::set_character_image_identifier(std::string character_image_identifier)
{
   this->character_image_identifier = character_image_identifier;
}


void CharacterFeatureRenderer::set_duration(float duration)
{
   this->duration = duration;
}


void CharacterFeatureRenderer::set_age(float age)
{
   this->age = age;
}


void CharacterFeatureRenderer::set_character_name_font_name(std::string character_name_font_name)
{
   this->character_name_font_name = character_name_font_name;
}


void CharacterFeatureRenderer::set_character_name_font_size(int character_name_font_size)
{
   this->character_name_font_size = character_name_font_size;
}


void CharacterFeatureRenderer::set_description_font_name(std::string description_font_name)
{
   this->description_font_name = description_font_name;
}


void CharacterFeatureRenderer::set_description_font_size(int description_font_size)
{
   this->description_font_size = description_font_size;
}


AllegroFlare::FontBin* CharacterFeatureRenderer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::BitmapBin* CharacterFeatureRenderer::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::string CharacterFeatureRenderer::get_character_name() const
{
   return character_name;
}


std::string CharacterFeatureRenderer::get_description() const
{
   return description;
}


std::string CharacterFeatureRenderer::get_character_image_identifier() const
{
   return character_image_identifier;
}


float CharacterFeatureRenderer::get_duration() const
{
   return duration;
}


float CharacterFeatureRenderer::get_age() const
{
   return age;
}


std::string CharacterFeatureRenderer::get_character_name_font_name() const
{
   return character_name_font_name;
}


int CharacterFeatureRenderer::get_character_name_font_size() const
{
   return character_name_font_size;
}


std::string CharacterFeatureRenderer::get_description_font_name() const
{
   return description_font_name;
}


int CharacterFeatureRenderer::get_description_font_size() const
{
   return description_font_size;
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
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::render: error: guard \"bitmap_bin\" not met");
   }
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

   // Draw the character name
   al_draw_text(
      character_name_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      title_x,
      title_y-text_height,
      ALLEGRO_ALIGN_RIGHT,
      character_name.c_str()
   );

   // Draw the character description
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

   // Draw the featured image
   ALLEGRO_BITMAP* character_image = obtain_character_image();
   if (character_image)
   {
      AllegroFlare::Placement2D placement;
      placement.position = { 1920 / 3 * 2, 1080 / 2 };
      placement.size = { (float)al_get_bitmap_width(character_image), (float)al_get_bitmap_height(character_image) };
      placement.start_transform();
      al_draw_bitmap(character_image, 0, 0, 0);
      placement.restore_transform();
   }

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
   std::stringstream font_identifier;
   font_identifier << character_name_font_name << " " << character_name_font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
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
   std::stringstream font_identifier;
   font_identifier << description_font_name << " " << description_font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}

ALLEGRO_BITMAP* CharacterFeatureRenderer::obtain_character_image()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[CharacterFeatureRenderer::obtain_character_image]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterFeatureRenderer::obtain_character_image: error: guard \"bitmap_bin\" not met");
   }
   if (character_image_identifier.empty()) return nullptr;
   return bitmap_bin->auto_get(character_image_identifier);
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


