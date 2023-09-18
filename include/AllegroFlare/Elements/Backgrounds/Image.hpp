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
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/Image";

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string image_filename;
            ALLEGRO_BITMAP* obtain_background_bitmap();

         protected:


         public:
            Image(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string image_filename="[image-filename-not-set]");
            ~Image();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_image_filename(std::string image_filename);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            std::string get_image_filename() const;
            void render() override;
         };
      }
   }
}



