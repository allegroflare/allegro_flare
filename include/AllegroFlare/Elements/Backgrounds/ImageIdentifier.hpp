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
         class ImageIdentifier : public AllegroFlare::Elements::Backgrounds::Base
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string image_filename;
            float reveal_counter;
            float reveal_speed;
            ALLEGRO_BITMAP* obtain_background_bitmap();

         protected:


         public:
            ImageIdentifier(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string image_filename="[image-filename-not-set]");
            virtual ~ImageIdentifier();

            float get_reveal_counter() const;
            void render() override;
            virtual void activate() override;
            virtual void deactivate() override;
            virtual void update() override;
            float infer_opacity();
         };
      }
   }
}



