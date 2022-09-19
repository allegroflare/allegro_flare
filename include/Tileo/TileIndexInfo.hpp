#pragma once


#include <allegro5/allegro.h>


namespace Tileo
{
   class TileIndexInfo
   {
   private:
      int index_num;
      ALLEGRO_BITMAP* bitmap_source;
      ALLEGRO_BITMAP* sub_bitmap;
      float u1;
      float v1;
      float u2;
      float v2;

   public:
      TileIndexInfo(int index_num=-1, ALLEGRO_BITMAP* bitmap_source=nullptr, ALLEGRO_BITMAP* sub_bitmap=nullptr, float u1=0, float v1=0, float u2=0, float v2=0);
      ~TileIndexInfo();

      void set_index_num(int index_num);
      void set_bitmap_source(ALLEGRO_BITMAP* bitmap_source);
      void set_sub_bitmap(ALLEGRO_BITMAP* sub_bitmap);
      void set_u1(float u1);
      void set_v1(float v1);
      void set_u2(float u2);
      void set_v2(float v2);
      int get_index_num();
      ALLEGRO_BITMAP* get_bitmap_source();
      ALLEGRO_BITMAP* get_sub_bitmap();
      float get_u1();
      float get_v1();
      float get_u2();
      float get_v2();
   };
}



