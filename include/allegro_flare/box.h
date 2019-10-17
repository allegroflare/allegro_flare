#pragma once




#include <allegro_flare/surface_area_base.h>




namespace allegro_flare
{
   class UISurfaceAreaBox : public UISurfaceAreaBase
   {
   public:
      UISurfaceAreaBox(float x, float y, float w, float h);
      ~UISurfaceAreaBox();

      void draw_bounding_area();
      bool collides(float x, float y);
   };
}



