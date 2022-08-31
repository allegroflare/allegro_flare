#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Image.hpp>
#include <AllegroFlare/Elements/Backgrounds/Monoplex.hpp>
#include <string>


namespace AllegroFlare
{
   class BackgroundFactory
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;

   protected:


   public:
      BackgroundFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
      ~BackgroundFactory();

      AllegroFlare::Elements::Backgrounds::Monoplex* create_monoplex();
      AllegroFlare::Elements::Backgrounds::Image* create_image(std::string image_identifier="[unset-default-image-identifer-for-background-factory]");
   };
}



