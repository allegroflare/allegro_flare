#pragma once


#include <allegro5/allegro.h>
#include <vector>


namespace AllegroFlare
{
   namespace ImageProcessing
   {
      class ImageReduction
      {
      private:

      protected:


      public:
         ImageReduction();
         ~ImageReduction();

         static ALLEGRO_BITMAP* create_pixel_perfect_reduction(ALLEGRO_BITMAP* source_image=nullptr, int width=0, int height=0);
         static ALLEGRO_COLOR blend_pixels(std::vector<ALLEGRO_COLOR>* colors_=nullptr);
         static bool validate_pixel_perfect_fit(ALLEGRO_BITMAP* source_image=nullptr, int width=0, int height=0);
      };
   }
}



