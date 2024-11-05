

#include <AllegroFlare/ImageProcessing/ImageReduction.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace ImageProcessing
{


ImageReduction::ImageReduction()
{
}


ImageReduction::~ImageReduction()
{
}


ALLEGRO_BITMAP* ImageReduction::create_pixel_perfect_reduction(ALLEGRO_BITMAP* source_image, int width, int height)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(source_image))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"source_image\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"source_image\" not met");
   }
   if (!((width != 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"(width != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"(width != 0)\" not met");
   }
   if (!((height != 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"(height != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"(height != 0)\" not met");
   }
   if (!(validate_pixel_perfect_fit(source_image, width, height)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"validate_pixel_perfect_fit(source_image, width, height)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction]: error: guard \"validate_pixel_perfect_fit(source_image, width, height)\" not met");
   }
   // TODO: Ensure correct bitmap flags
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   // TODO: Restore previous bitmap target
   int pixels_per_column = al_get_bitmap_width(source_image) / width;
   int pixels_per_row = al_get_bitmap_height(source_image) / height;
   int num_columns = width;
   int num_rows = height;

   AllegroFlare::Logger::info_from(
      "AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction",
      "Creating an image where each pixel is average of " + std::to_string(pixels_per_column) + "x"
         + std::to_string(pixels_per_row) + " pixels. Starting processing."
   );
   double start_time = al_get_time();

   ALLEGRO_BITMAP *result = al_create_bitmap(width, height);
   al_set_target_bitmap(result);
   al_clear_to_color(ALLEGRO_COLOR{0.0, 0.0, 0.0, 1});

   al_lock_bitmap(source_image, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
   al_lock_bitmap(result, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

   for (int row=0; row<num_rows; row++)
   {
      for (int column=0; column<num_columns; column++)
      {
         std::vector<ALLEGRO_COLOR> samples_for_this_result_pixel;
         for (int y=0; y<pixels_per_row; y++)
         {
            for (int x=0; x<pixels_per_column; x++)
            {
               samples_for_this_result_pixel.push_back(
                  al_get_pixel(source_image, x + column * pixels_per_column, y + row * pixels_per_row)
               );
            }
         }
         al_put_pixel(column, row, blend_pixels(&samples_for_this_result_pixel));
      }
   }

   al_unlock_bitmap(source_image);
   al_unlock_bitmap(result);

   double end_time = al_get_time();
   AllegroFlare::Logger::info_from(
      "AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction",
      "Image processing finished (" + std::to_string(end_time - start_time) + " seconds)."
   );

   al_restore_state(&previous_state);

   return result;
}

ALLEGRO_COLOR ImageReduction::blend_pixels(std::vector<ALLEGRO_COLOR>* colors_)
{
   if (!(colors_))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::blend_pixels]: error: guard \"colors_\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::blend_pixels]: error: guard \"colors_\" not met");
   }
   if (!((!colors_->empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::blend_pixels]: error: guard \"(!colors_->empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::blend_pixels]: error: guard \"(!colors_->empty())\" not met");
   }
   std::vector<ALLEGRO_COLOR> &colors = *colors_;
   double r = 0.0, g = 0.0, b = 0.0, a = 0.0, size = (double)colors.size();

   // Mix the pixels with highest precision
   for (auto &color : colors)
   {
      r += (double)color.r;
      g += (double)color.g;
      b += (double)color.b;
      a += (double)color.a;
   }

   r /= size;
   g /= size;
   b /= size;
   a /= size;

   return ALLEGRO_COLOR{(float)r, (float)g, (float)b, (float)a};
}

bool ImageReduction::validate_pixel_perfect_fit(ALLEGRO_BITMAP* source_image, int width, int height)
{
   if (!(source_image))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"source_image\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"source_image\" not met");
   }
   if (!((width != 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(width != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(width != 0)\" not met");
   }
   if (!((height != 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(height != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(height != 0)\" not met");
   }
   if (!((al_get_bitmap_width(source_image) % width == 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(al_get_bitmap_width(source_image) % width == 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(al_get_bitmap_width(source_image) % width == 0)\" not met");
   }
   if (!((al_get_bitmap_height(source_image) % height == 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(al_get_bitmap_height(source_image) % height == 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(al_get_bitmap_height(source_image) % height == 0)\" not met");
   }
   if (!((al_get_bitmap_width(source_image) / width == al_get_bitmap_height(source_image) / height)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(al_get_bitmap_width(source_image) / width == al_get_bitmap_height(source_image) / height)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ImageProcessing::ImageReduction::validate_pixel_perfect_fit]: error: guard \"(al_get_bitmap_width(source_image) / width == al_get_bitmap_height(source_image) / height)\" not met");
   }
   return true;
}


} // namespace ImageProcessing
} // namespace AllegroFlare


