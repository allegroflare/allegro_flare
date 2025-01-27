#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ImageLayer.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class ImageLayerLoader
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         std::string filename;
         int pixel_scale;
         std::vector<AllegroFlare::Elements::ImageLayer> image_layers;
         bool loaded;

      protected:


      public:
         ImageLayerLoader(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string filename="[unset-filename]", int pixel_scale=3);
         ~ImageLayerLoader();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_filename(std::string filename);
         void set_pixel_scale(int pixel_scale);
         bool get_loaded() const;
         std::vector<AllegroFlare::Elements::ImageLayer> get_image_layers();
         void load();
         static ALLEGRO_BITMAP* clone_and_scale(ALLEGRO_BITMAP* bitmap=nullptr, int pixel_scale=1);
      };
   }
}



