

#include <AllegroFlare/Elements/ImageLayerLoader.hpp>

#include <AllegroFlare/Tiled/TMJImageLayerLoader.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ImageLayerLoader::ImageLayerLoader(std::string filename, AllegroFlare::BitmapBin* bitmap_bin)
   : filename(filename)
   , bitmap_bin(bitmap_bin)
   , image_layers({})
   , loaded(false)
{
}


ImageLayerLoader::~ImageLayerLoader()
{
}


void ImageLayerLoader::set_filename(std::string filename)
{
   this->filename = filename;
}


void ImageLayerLoader::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


bool ImageLayerLoader::get_loaded() const
{
   return loaded;
}


std::vector<AllegroFlare::Tiled::TMJImageLayer> ImageLayerLoader::get_image_layers()
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
   AllegroFlare::Tiled::TMJImageLayerLoader tmj_image_layer_loader(filename);
   tmj_image_layer_loader.load();

   loaded = true;

   return;
}


} // namespace Elements
} // namespace AllegroFlare


