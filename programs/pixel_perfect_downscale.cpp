#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/ImageProcessing/ImageReduction.hpp>


/***********************************

This program works in conjunction with Adobe Illustrator, scripts/Illustrator/export_* files.

- To use, the entry point is "scripts/Illustrator/export_ui_glyphs.sh"
- Adobe Illustrator is assumed to be open with the illustrator file you wish to process

The Script will
  1) Export an Illustrator file at a higher resolution
  2) Resize the image using AllegroFlare's ImageReduction

*************************************/


int main(int argc, char **argv)
{
   std::string source_image_filename = "/Users/markoates/Repos/Layouts/project_files/ascii_glyphs_12x16-11-1000x.png";
   //std::string source_image_filename = "/Users/markoates/Desktop/ascii_glyphs_12x16-10-1000x.png";
   std::string result_image_filename = source_image_filename + "-result.png";

   al_init();
   al_init_image_addon();

   al_set_new_display_flags(ALLEGRO_OPENGL); // | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   ALLEGRO_BITMAP *source_image = al_load_bitmap(source_image_filename.c_str());
   if (!source_image)
   {
      AllegroFlare::Logger::throw_error(
         "allegro_flare/programs/pixel_perfect_downscale"
         "Could not load image \"" + source_image_filename + "\"."
      );
   }
   else
   {
      AllegroFlare::Logger::info_from(
         "allegro_flare/programs/pixel_perfect_downscale",
         "Successfully loaded image \"" + source_image_filename + "\"."
      );
   }

   int width = 360;
   int height = 416;

   ALLEGRO_BITMAP *result =
      AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction(source_image, width, height);
   if (!result)
   {
      AllegroFlare::Logger::throw_error(
         "allegro_flare/programs/pixel_perfect_downscale"
         "Could not produce the image \"" + result_image_filename + "\"."
      );
   }

   al_save_bitmap(result_image_filename.c_str(), result);

   // Cleanup
   al_destroy_bitmap(result);
   al_destroy_bitmap(source_image);

   AllegroFlare::Logger::info_from(
      "allegro_flare/programs/pixel_perfect_downscale",
      "Image processing complete."
   );

   al_shutdown_image_addon();
   al_uninstall_system();

   return 0;
}


