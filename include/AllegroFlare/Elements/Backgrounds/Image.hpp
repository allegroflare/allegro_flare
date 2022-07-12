#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class Image : public AllegroFlare::Elements::Backgrounds::Base
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string image_filename;
            std::string image_file_location_prefix;

         public:
            Image(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string image_filename="[image-filename-not-set]");
            ~Image();

            void render() override;
            ALLEGRO_BITMAP* obtain_background_bitmap();
            float infer_opacity();
         };
      }
   }
}



