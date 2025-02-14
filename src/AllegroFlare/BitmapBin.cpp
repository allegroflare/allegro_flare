

#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
   BitmapBin::BitmapBin()
      : Bin<std::string, ALLEGRO_BITMAP *>("BitmapBin")
   {}


   BitmapBin::~BitmapBin()
   {
      clear();
   }


   bool BitmapBin::validate()
   {
      if (!al_is_image_addon_initialized())
      {
         std::cout << CONSOLE_COLOR_RED
                   << "[AllegroFlare::BitmapBin::validate] not properly initialized (requires al_init_image_addon()). "
                   << " Will crash probably crash."
                   << CONSOLE_COLOR_DEFAULT
                   << std::endl;
         return false;
      }
      return true;
   }


   ALLEGRO_BITMAP *BitmapBin::load_data(std::string identifier)
   {
      validate();
      return al_load_bitmap(identifier.c_str());
   }


   void BitmapBin::destroy_data(ALLEGRO_BITMAP *bmp)
   {
      if (!al_is_system_installed()) // TODO: Check if al_is_image_addon_initialized() is required for destruction
      {
         // TODO: Test this
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::BitmapBin::destroy_data",
            "Cannot call al_destroy_bitmap when system is not installed, this will likely result in a crash. Usually "
               "this occurs when the system has already been shutdown, but BitmapBin::~BitmapBin() is called after."
         );
      }

      al_destroy_bitmap(bmp);
   }


   std::string BitmapBin::build_standard_path(std::string data_folder_path)
   {
      return data_folder_path + "bitmaps/"; // TODO: Consider moving "bitmaps/" to a constant
   }
}


