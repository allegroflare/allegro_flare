

#include <AllegroFlare/Elements/ImageLayerLoader.hpp>

#include <AllegroFlare/ImageProcessing/ImageProcessor.hpp>
#include <AllegroFlare/Tiled/TMJImageLayerLoader.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ImageLayerLoader::ImageLayerLoader(AllegroFlare::BitmapBin* bitmap_bin, std::string filename, int pixel_scale)
   : bitmap_bin(bitmap_bin)
   , filename(filename)
   , pixel_scale(pixel_scale)
   , image_layers({})
   , loaded(false)
{
}


ImageLayerLoader::~ImageLayerLoader()
{
}


void ImageLayerLoader::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void ImageLayerLoader::set_filename(std::string filename)
{
   this->filename = filename;
}


void ImageLayerLoader::set_pixel_scale(int pixel_scale)
{
   this->pixel_scale = pixel_scale;
}


bool ImageLayerLoader::get_loaded() const
{
   return loaded;
}


std::vector<AllegroFlare::Elements::ImageLayer> &ImageLayerLoader::get_image_layers_ref()
{
   return image_layers;
}


std::vector<AllegroFlare::Elements::ImageLayer> ImageLayerLoader::get_image_layers()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::get_image_layers]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::get_image_layers]: error: guard \"loaded\" not met");
   }
   return image_layers;
}

void ImageLayerLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"(!loaded)\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"bitmap_bin\" not met");
   }
   if (!((pixel_scale > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"(pixel_scale > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"(pixel_scale > 0)\" not met");
   }
   if (!((pixel_scale <= 5)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"(pixel_scale <= 5)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::load]: error: guard \"(pixel_scale <= 5)\" not met");
   }
   AllegroFlare::Tiled::TMJImageLayerLoader tmj_image_layer_loader(filename);
   tmj_image_layer_loader.load();

   int num_image_layers = tmj_image_layer_loader.get_num_image_layers();
   image_layers.reserve(num_image_layers);

   tmj_image_layer_loader.for_each_image_layer([this](
      AllegroFlare::Tiled::TMJImageLayer* tmj_image_layer,
      void* user_data) {
         // TODO: Consider deleting the bitmap from the bitmap_bin if it was not already loaded before this function
         ALLEGRO_BITMAP *initial_bitmap = bitmap_bin->auto_get(tmj_image_layer->image_filename);
         ALLEGRO_BITMAP *scaled_bitmap = clone_and_scale(initial_bitmap, pixel_scale);

         image_layers.emplace_back(//AllegroFlare::Elements::ImageLayer(
            tmj_image_layer->id,
            tmj_image_layer->name,
            tmj_image_layer->image_filename,
            scaled_bitmap,
            true, // bitmap_is_owned
            pixel_scale,
            tmj_image_layer->offset_x,
            tmj_image_layer->offset_y,
            tmj_image_layer->parallax_x,
            tmj_image_layer->parallax_y,
            tmj_image_layer->repeat_x,
            tmj_image_layer->repeat_y,
            tmj_image_layer->opacity,
            tmj_image_layer->tint_color_is_set,
            tmj_image_layer->tint_color
         );
         //));
      }
   );

   loaded = true;

   return;
}

ALLEGRO_BITMAP* ImageLayerLoader::clone_and_scale(ALLEGRO_BITMAP* bitmap, int pixel_scale)
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::clone_and_scale]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::clone_and_scale]: error: guard \"bitmap\" not met");
   }
   if (!((pixel_scale >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::clone_and_scale]: error: guard \"(pixel_scale >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::clone_and_scale]: error: guard \"(pixel_scale >= 1)\" not met");
   }
   if (!((pixel_scale < 5)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayerLoader::clone_and_scale]: error: guard \"(pixel_scale < 5)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayerLoader::clone_and_scale]: error: guard \"(pixel_scale < 5)\" not met");
   }
   AllegroFlare::ImageProcessing::ImageProcessor image_processor(bitmap);
   return image_processor.create_pixel_perfect_scaled_render(pixel_scale);
}


} // namespace Elements
} // namespace AllegroFlare


