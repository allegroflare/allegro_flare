

#include <AllegroFlare/FrameAnimation/Book.hpp>

#include <AllegroFlare/Errors.hpp>
#include <AllegroFlare/FrameAnimation/AsepriteSpriteSheetJSONLoader.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace FrameAnimation
{


Book::Book(std::string png_source_filename, std::string json_source_filename, int sprite_sheet_scale, int sprite_sheet_cell_width, int sprite_sheet_cell_height)
   : png_source_filename(png_source_filename)
   , json_source_filename(json_source_filename)
   , sprite_sheet_scale(sprite_sheet_scale)
   , sprite_sheet_cell_width(sprite_sheet_cell_width)
   , sprite_sheet_cell_height(sprite_sheet_cell_height)
   , sprite_sheet(nullptr)
   , dictionary({})
   , initialized(false)
{
}


Book::~Book()
{
}


void Book::set_dictionary(std::map<std::string, AllegroFlare::FrameAnimation::Animation> dictionary)
{
   this->dictionary = dictionary;
}


int Book::get_sprite_sheet_scale() const
{
   return sprite_sheet_scale;
}


int Book::get_sprite_sheet_cell_width() const
{
   return sprite_sheet_cell_width;
}


int Book::get_sprite_sheet_cell_height() const
{
   return sprite_sheet_cell_height;
}


void Book::set_png_source_filename(std::string png_source_filename)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_png_source_filename]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_png_source_filename]: error: guard \"(!initialized)\" not met");
   }
   this->png_source_filename = png_source_filename;
   return;
}

void Book::set_json_source_filename(std::string json_source_filename)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_json_source_filename]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_json_source_filename]: error: guard \"(!initialized)\" not met");
   }
   this->json_source_filename = json_source_filename;
   return;
}

void Book::set_sprite_sheet_scale(int sprite_sheet_scale)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_scale]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_scale]: error: guard \"(!initialized)\" not met");
   }
   if (!((sprite_sheet_scale > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_scale]: error: guard \"(sprite_sheet_scale > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_scale]: error: guard \"(sprite_sheet_scale > 0)\" not met");
   }
   this->sprite_sheet_scale = sprite_sheet_scale;
   return;
}

void Book::set_sprite_sheet_cell_width(int sprite_sheet_cell_width)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_width]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_width]: error: guard \"(!initialized)\" not met");
   }
   if (!((sprite_sheet_cell_width > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_width]: error: guard \"(sprite_sheet_cell_width > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_width]: error: guard \"(sprite_sheet_cell_width > 0)\" not met");
   }
   this->sprite_sheet_cell_width = sprite_sheet_cell_width;
   return;
}

void Book::set_sprite_sheet_cell_height(int sprite_sheet_cell_height)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_height]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_height]: error: guard \"(!initialized)\" not met");
   }
   if (!((sprite_sheet_cell_height > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_height]: error: guard \"(sprite_sheet_cell_height > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::set_sprite_sheet_cell_height]: error: guard \"(sprite_sheet_cell_height > 0)\" not met");
   }
   this->sprite_sheet_cell_height = sprite_sheet_cell_height;
   return;
}

AllegroFlare::FrameAnimation::SpriteSheet* Book::get_sprite_sheet()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::get_sprite_sheet]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::get_sprite_sheet]: error: guard \"initialized\" not met");
   }
   return sprite_sheet;
}

void Book::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((sprite_sheet_scale > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::initialize]: error: guard \"(sprite_sheet_scale > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::initialize]: error: guard \"(sprite_sheet_scale > 0)\" not met");
   }
   // TODO: rename this function to initialize
   // build the sprite sheet
   if (!AllegroFlare::php::file_exists(png_source_filename))
   {
      AllegroFlare::Errors::throw_missing_file_error("AllegroFlare::FrameAnimation::Book::initialize",
            png_source_filename,
            "png"
      );
   }

   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap(png_source_filename.c_str());
   // TODO: add validation for unloadable sprite_sheet_bitmap
   sprite_sheet = new SpriteSheet(
      sprite_sheet_bitmap,
      sprite_sheet_cell_width,
      sprite_sheet_cell_height,
      sprite_sheet_scale
   );
   sprite_sheet->initialize();
   al_destroy_bitmap(sprite_sheet_bitmap);

   // load the data

   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader loader(json_source_filename, sprite_sheet);
   dictionary = loader.load();

   initialized = true;
   return;
}

ALLEGRO_BITMAP* Book::get_still_frame(std::string tag_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::get_still_frame]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::get_still_frame]: error: guard \"initialized\" not met");
   }
   // Is this depreciated?
   return find_animation_by_name(tag_name).get_bitmap_at_frame_num(0);
}

bool Book::animation_exists(std::string name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::animation_exists]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::animation_exists]: error: guard \"initialized\" not met");
   }
   return (dictionary.count(name) > 0);
}

AllegroFlare::FrameAnimation::Animation Book::find_animation_by_name(std::string name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Book::find_animation_by_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Book::find_animation_by_name]: error: guard \"initialized\" not met");
   }
   if (dictionary.count(name) == 0)
   {
      std::stringstream error_message;
      error_message << "No animation exists for name \"" << name << "\"";
      AllegroFlare::Errors::throw_error(
         "AllegroFlare::FrameAnimation::Book::find_animation_by_name",
         error_message.str()
      );
   }
   return dictionary[name];
}

void Book::_build_placeholder_dictionary()
{
   dictionary =  {
      { "blob", AllegroFlare::FrameAnimation::Animation(
            sprite_sheet,
            "blob",
            std::vector<AllegroFlare::FrameAnimation::Frame>{
               { 1, 0.200f },
               { 2, 0.100f },
               { 3, 0.200f },
            }, AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_PING_PONG
      )},
   };
   return;
}


} // namespace FrameAnimation
} // namespace AllegroFlare


