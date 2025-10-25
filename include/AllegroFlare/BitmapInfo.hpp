#pragma once


#include <AllegroFlare/AllegroUnstable.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   class BitmapInfo
   {
   private:
      ALLEGRO_BITMAP* bitmap;
      int width;
      int height;
      int depth;
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

      void set_bitmap(ALLEGRO_BITMAP* bitmap);
      bool get_initialized() const;
      void initialize();
      std::string build_report();
      std::string format_table(std::vector<std::tuple<std::string, std::string>> data={}, int label_width=16, int number_width=10);
      std::string decode_bitmap_flags(int bitmap_flags=0);
      std::string get_pixel_format_name(ALLEGRO_PIXEL_FORMAT pixel_format=ALLEGRO_PIXEL_FORMAT_ANY);
   };
}



