

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


Book::Book(std::string png_source_filename, std::string json_source_filename)
   : png_source_filename(png_source_filename)
   , json_source_filename(json_source_filename)
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


AllegroFlare::FrameAnimation::SpriteSheet* Book::get_sprite_sheet()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Book::get_sprite_sheet]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Book::get_sprite_sheet: error: guard \"initialized\" not met");
   }
   return sprite_sheet;
}

void Book::init()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Book::init]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Book::init: error: guard \"(!initialized)\" not met");
   }
   // TODO: rename this function to initialize
   // build the sprite sheet
   if (!AllegroFlare::php::file_exists(png_source_filename))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::AnimationBook::init] error: "
                    << "expected png file does not exist. Looking in \"" << png_source_filename << "\".";
      throw std::runtime_error(error_message.str());
   }

   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap(png_source_filename.c_str());
   // TODO: add validation for unloadable sprite_sheet_bitmap
   sprite_sheet = new SpriteSheet(sprite_sheet_bitmap, 48, 48, 5); // auto-inits
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
      error_message << "[Book::get_still_frame]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Book::get_still_frame: error: guard \"initialized\" not met");
   }
   return get_animation_by_name(tag_name).get_bitmap_at_frame_num(0);
}

AllegroFlare::FrameAnimation::Animation Book::get_animation_by_name(std::string name)
{
   if (dictionary.count(name) == 0)
   {
      std::stringstream error_message;
      error_message << "No animation exists for name \"" << name << "\"";
      AllegroFlare::Errors::throw_error("DungeonPlus::AnimationBook::get_animation_by_name", error_message.str());
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


