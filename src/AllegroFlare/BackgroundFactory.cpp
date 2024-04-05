

#include <AllegroFlare/BackgroundFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


BackgroundFactory::BackgroundFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
{
}


BackgroundFactory::~BackgroundFactory()
{
}


AllegroFlare::Elements::Backgrounds::Monoplex* BackgroundFactory::create_monoplex()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[BackgroundFactory::create_monoplex]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BackgroundFactory::create_monoplex: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Elements::Backgrounds::Monoplex* monoplex_background =
      new AllegroFlare::Elements::Backgrounds::Monoplex(bitmap_bin);
   return monoplex_background;
}

AllegroFlare::Elements::Backgrounds::Image* BackgroundFactory::create_image(std::string image_identifier)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[BackgroundFactory::create_image]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BackgroundFactory::create_image: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Elements::Backgrounds::Image* image_background =
      new AllegroFlare::Elements::Backgrounds::Image(bitmap_bin, image_identifier);
   return image_background;
}

AllegroFlare::Elements::Backgrounds::Parallax* BackgroundFactory::create_parallax(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers, float offset_x, float offset_y)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[BackgroundFactory::create_parallax]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BackgroundFactory::create_parallax: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Elements::Backgrounds::Parallax* background =
      new AllegroFlare::Elements::Backgrounds::Parallax(layers, offset_x, offset_y);
   return background;
}


} // namespace AllegroFlare


