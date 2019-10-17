#pragma once




#include <allegro_flare/surface_area_base.h>




namespace allegro_flare
{
   class UISurfaceAreaBoxPadded : public UISurfaceAreaBase
   {
   private:
      float padding_top;
      float padding_right;
      float padding_bottom;
      float padding_left;

   public:
      UISurfaceAreaBoxPadded(float x, float y, float w, float h, float pt, float pr, float pb, float pl);
      ~UISurfaceAreaBoxPadded();

      void draw_bounding_area();
      bool collides(float x, float y);

      void get_padding(float *pt, float *pr, float *pb, float *pl);
      void set_padding(float pt, float pr, float pb, float pl);
   };
}



