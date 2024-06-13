

#include <AllegroFlare/Elements/StoryboardPages/ImageWithAdvancingText.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/MotionKit.hpp>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


ImageWithAdvancingText::ImageWithAdvancingText(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::string image_identifier, std::string text, AllegroFlare::Placement2D image_placement, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float top_padding, float left_padding, float right_padding, float line_height_multiplier, float line_height_padding, float image_fade_in_duration_sec)
   : AllegroFlare::Elements::StoryboardPages::Base(AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::TYPE)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , image_identifier(image_identifier)
   , text(text)
   , image_placement(image_placement)
   , font_name(font_name)
   , font_size(font_size)
   , text_color(text_color)
   , top_padding(top_padding)
   , left_padding(left_padding)
   , right_padding(right_padding)
   , line_height_multiplier(line_height_multiplier)
   , line_height_padding(line_height_padding)
   , image_fade_in_duration_sec(image_fade_in_duration_sec)
   , revealed_characters_count(0)
   , started_at(0.0f)
   , all_characters_revealed_at(0.0f)
   , wait_duration_after_all_characters_are_revealed(3.0f)
{
}


ImageWithAdvancingText::~ImageWithAdvancingText()
{
}


void ImageWithAdvancingText::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void ImageWithAdvancingText::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ImageWithAdvancingText::set_image_identifier(std::string image_identifier)
{
   this->image_identifier = image_identifier;
}


void ImageWithAdvancingText::set_text(std::string text)
{
   this->text = text;
}


void ImageWithAdvancingText::set_image_placement(AllegroFlare::Placement2D image_placement)
{
   this->image_placement = image_placement;
}


void ImageWithAdvancingText::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void ImageWithAdvancingText::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void ImageWithAdvancingText::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void ImageWithAdvancingText::set_top_padding(float top_padding)
{
   this->top_padding = top_padding;
}


void ImageWithAdvancingText::set_left_padding(float left_padding)
{
   this->left_padding = left_padding;
}


void ImageWithAdvancingText::set_right_padding(float right_padding)
{
   this->right_padding = right_padding;
}


void ImageWithAdvancingText::set_line_height_multiplier(float line_height_multiplier)
{
   this->line_height_multiplier = line_height_multiplier;
}


void ImageWithAdvancingText::set_line_height_padding(float line_height_padding)
{
   this->line_height_padding = line_height_padding;
}


void ImageWithAdvancingText::set_image_fade_in_duration_sec(float image_fade_in_duration_sec)
{
   this->image_fade_in_duration_sec = image_fade_in_duration_sec;
}


AllegroFlare::BitmapBin* ImageWithAdvancingText::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* ImageWithAdvancingText::get_font_bin() const
{
   return font_bin;
}


std::string ImageWithAdvancingText::get_image_identifier() const
{
   return image_identifier;
}


std::string ImageWithAdvancingText::get_text() const
{
   return text;
}


AllegroFlare::Placement2D ImageWithAdvancingText::get_image_placement() const
{
   return image_placement;
}


std::string ImageWithAdvancingText::get_font_name() const
{
   return font_name;
}


int ImageWithAdvancingText::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR ImageWithAdvancingText::get_text_color() const
{
   return text_color;
}


float ImageWithAdvancingText::get_top_padding() const
{
   return top_padding;
}


float ImageWithAdvancingText::get_left_padding() const
{
   return left_padding;
}


float ImageWithAdvancingText::get_right_padding() const
{
   return right_padding;
}


float ImageWithAdvancingText::get_line_height_multiplier() const
{
   return line_height_multiplier;
}


float ImageWithAdvancingText::get_line_height_padding() const
{
   return line_height_padding;
}


float ImageWithAdvancingText::get_image_fade_in_duration_sec() const
{
   return image_fade_in_duration_sec;
}


int ImageWithAdvancingText::get_revealed_characters_count() const
{
   return revealed_characters_count;
}


float ImageWithAdvancingText::get_started_at() const
{
   return started_at;
}


float ImageWithAdvancingText::get_all_characters_revealed_at() const
{
   return all_characters_revealed_at;
}


float ImageWithAdvancingText::get_wait_duration_after_all_characters_are_revealed() const
{
   return wait_duration_after_all_characters_are_revealed;
}


void ImageWithAdvancingText::start()
{
   //image_fade_in_duration_sec = 1.5;
   revealed_characters_count = 0;
   all_characters_revealed_at = 0.0f;
   started_at = al_get_time(); // TODO: Consider injecting time
   set_finished(false);
   return;
}

void ImageWithAdvancingText::update()
{
   if (get_finished()) return;

   float time_now = al_get_time();

   if (!all_characters_are_revealed())
   {
      revealed_characters_count++;
      if (revealed_characters_count >= text.size())
      {
         all_characters_revealed_at = time_now;
      }
   }
   else // all characters are revealed
   {
      float all_characters_revealed_age = time_now - all_characters_revealed_at;

      bool should_finish = (all_characters_revealed_age > wait_duration_after_all_characters_are_revealed);

      if (should_finish)
      {
         set_finished(true);
      }
   }
   return;
}

void ImageWithAdvancingText::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::render]: error: guard \"bitmap_bin\" not met");
   }
   // Draw the image
   if (!image_identifier.empty())
   {
      float time_now = al_get_time();
      float age = infer_age(time_now);
      float normalized_fade_age = 1.0f;
      // TODO: Test this case with "image_fade_in_duration_sec" at 0.0f or negative
      if (image_fade_in_duration_sec >= 0.0001f)
      {
         normalized_fade_age =
            AllegroFlare::MotionKit::normalize_age(started_at, started_at+image_fade_in_duration_sec, time_now);
      }
      ALLEGRO_BITMAP *image = bitmap_bin->auto_get(image_identifier);
      if (image) image_placement.size = { (float)al_get_bitmap_width(image), (float)al_get_bitmap_height(image) };
      float opacity = normalized_fade_age; //1.0f;
      ALLEGRO_COLOR tint{opacity, opacity, opacity, opacity};

      image_placement.start_transform();
      al_draw_tinted_bitmap(image, tint, 0, 0, 0);
      image_placement.restore_transform();
   }

   // Draw the text
   ALLEGRO_FONT *text_font = obtain_font();
   std::string revealed_text = generate_revealed_text();
   if (!revealed_text.empty())
   {
      float box_width = 1920 - (left_padding + right_padding);
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

void ImageWithAdvancingText::advance()
{
   float time_now = al_get_time();

   if (get_finished()) return;
   if (!all_characters_are_revealed())
   {
      reveal_image();
      reveal_all_characters();
      all_characters_revealed_at = time_now;
   }
   else
   {
      set_finished(true);
   }

   // TODO - should this also finished = true?
   return;
}

std::string ImageWithAdvancingText::generate_revealed_text()
{
   return text.substr(0, revealed_characters_count);
}

void ImageWithAdvancingText::reveal_all_characters()
{
   revealed_characters_count = text.size();
}

void ImageWithAdvancingText::reveal_image()
{
   image_fade_in_duration_sec = -0.0001f; // TODO: Find out why this needs to be a negative, and how it can be solved
                                          // in a better way.
}

bool ImageWithAdvancingText::all_characters_are_revealed()
{
   return revealed_characters_count >= text.size();
}

float ImageWithAdvancingText::infer_age(float time_now)
{
   return time_now - started_at;
}

ALLEGRO_FONT* ImageWithAdvancingText::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* ImageWithAdvancingText::obtain_next_button_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::obtain_next_button_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::obtain_next_button_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size+20;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


