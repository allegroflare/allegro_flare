#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class BitmapInfo
   {
   private:
      ALLEGRO_BITMAP* bitmap;
      int width;
      int height;
      int pixel_format;
      int flags;
      int samples;
      bool is_sub_bitmap;
      int sub_bitmap_x;
      int sub_bitmap_y;
      ALLEGRO_BITMAP* parent_bitmap;
      bool initialized;

   protected:


   public:
      BitmapInfo(ALLEGRO_BITMAP* bitmap=nullptr);
      ~BitmapInfo();

      void initialize(ALLEGRO_BITMAP* bitmap=nullptr);
   };
}



