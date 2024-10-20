

#include <AllegroFlare/BitmapInfo.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


BitmapInfo::BitmapInfo(ALLEGRO_BITMAP* bitmap)
   : bitmap(bitmap)
   , width(0)
   , height(0)
   , pixel_format(0)
   , flags(0)
   , samples(0)
   , is_sub_bitmap(false)
   , sub_bitmap_x(0)
   , sub_bitmap_y(0)
   , parent_bitmap(nullptr)
   , initialized(false)
{
}


BitmapInfo::~BitmapInfo()
{
}


void BitmapInfo::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   if (get_initialized()) throw std::runtime_error("[BitmapInfo::set_bitmap]: error: guard \"get_initialized()\" not met.");
   this->bitmap = bitmap;
}


bool BitmapInfo::get_initialized() const
{
   return initialized;
}


void BitmapInfo::initialize()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::BitmapInfo::initialize]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::BitmapInfo::initialize]: error: guard \"bitmap\" not met");
   }
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::BitmapInfo::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::BitmapInfo::initialize]: error: guard \"(!initialized)\" not met");
   }
   //this->bitmap = bitmap;
   flags = al_get_bitmap_flags(bitmap);
   pixel_format = al_get_bitmap_format(bitmap);
   //depth = al_get_bitmap_depth(bitmap); // NOTE: Depth cannot be included unless ALLEGRO_UNSTABLE is defined
                                          // before #include <allegro5/allegro.h>. Simply adding AllegroUnstable
                                          // as a dependency here will not get the order correct when the header
                                          // is generated
   width = al_get_bitmap_width(bitmap);
   height = al_get_bitmap_height(bitmap);
   flags = al_get_bitmap_flags(bitmap);
   //samples = al_get_bitmap_samples(bitmap); // Might also require ALLEGRO_UNSTABLE
   is_sub_bitmap = al_is_sub_bitmap(bitmap);
   sub_bitmap_x = al_get_bitmap_x(bitmap);
   sub_bitmap_y = al_get_bitmap_y(bitmap);
   parent_bitmap = al_get_parent_bitmap(bitmap);
   initialized = true;
   return;
}

std::string BitmapInfo::build_report()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::BitmapInfo::build_report]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::BitmapInfo::build_report]: error: guard \"initialized\" not met");
   }
   std::stringstream bitmap_ss;
   bitmap_ss << std::hex << bitmap;

   std::stringstream parent_bitmap_ss;
   parent_bitmap_ss << std::hex << parent_bitmap;

   std::vector<std::tuple<std::string, std::string>> data = {
      { "bitmap", bitmap_ss.str() },
      { "width", std::to_string(width) },
      { "height", std::to_string(height) },
      { "flags", std::to_string(flags) },
      { "pixel_format", std::to_string(pixel_format) },
      { "samples", std::to_string(samples) },
      { "is_sub_bitmap", std::to_string(is_sub_bitmap) },
      { "sub_bitmap_x", std::to_string(sub_bitmap_x) },
      { "sub_bitmap_y", std::to_string(sub_bitmap_y) },
      { "parent_bitmap", parent_bitmap_ss.str() },
   };
   //int longest_label_length = 0;
   //int longest_duration_length_in_chars = 0;
   //for (auto &timer : timers)
   //{
      //int duration = timer.second.get_elapsed_time_milliseconds();

   //data.push_back({timer.first, duration));
   //int duration_length_in_chars = count_digits(duration);

      //if (timer.first.size() > longest_label_length) longest_label_length = timer.first.size();
      //if (duration_length_in_chars > longest_duration_length_in_chars)
      //{
         //longest_duration_length_in_chars = duration_length_in_chars;
      //}
   //}

   return format_table(
      data,
      16,
      10
   );
}

std::string BitmapInfo::format_table(std::vector<std::tuple<std::string, std::string>> data, int label_width, int number_width)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::BitmapInfo::format_table]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::BitmapInfo::format_table]: error: guard \"initialized\" not met");
   }
   std::ostringstream result;

   for (const auto& [label, number] : data)
   {
      // Format each line with right-aligned text, padding with dashes
      result << std::right << std::setw(label_width) << label;
      result << " " << std::right << std::setfill('-') << std::setw(number_width + 1) << " " << number;
      result << std::setfill(' ');
      //result << " " << unit << "\n";
      result << std::endl;
   }

   return result.str();
}


} // namespace AllegroFlare


