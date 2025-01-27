#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Tiled/TMJImageLayer.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class ImageLayerLoader
      {
      private:
         std::string filename;
         AllegroFlare::BitmapBin* bitmap_bin;
         std::vector<AllegroFlare::Tiled::TMJImageLayer*> image_layers;
         bool loaded;

      protected:


      public:
         ImageLayerLoader(std::string filename="[unset-filename]", AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         ~ImageLayerLoader();

         void set_filename(std::string filename);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         bool get_loaded() const;
         std::vector<AllegroFlare::Tiled::TMJImageLayer*> get_image_layers();
         void load();
      };
   }
}



