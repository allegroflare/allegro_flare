

#include <AllegroFlare/BackgroundFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


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
      error_message << "BackgroundFactory" << "::" << "create_monoplex" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "BackgroundFactory" << "::" << "create_image" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Elements::Backgrounds::Image* image_background =
      new AllegroFlare::Elements::Backgrounds::Image(bitmap_bin, image_identifier);
   return image_background;
}
} // namespace AllegroFlare


