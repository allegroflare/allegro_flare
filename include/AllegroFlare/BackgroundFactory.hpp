#pragma once


#include <AllegroFlare/Backgrounds/Image.hpp>
#include <AllegroFlare/Backgrounds/Monoplex.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <string>


namespace AllegroFlare
{
   class BackgroundFactory
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;

   public:
      BackgroundFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
      ~BackgroundFactory();

      AllegroFlare::Backgrounds::Monoplex* create_monoplex();
      AllegroFlare::Backgrounds::Image* create_image(std::string image_identifier="[unset-default-image-identifer-for-background-factory]");
   };
}



