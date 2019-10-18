#pragma once




#include <allegro_flare/surface_area_base.h>




namespace allegro_flare
{
   class UISurfaceAreaAlwaysCollide : public UISurfaceAreaBase
   {
   public:
      UISurfaceAreaAlwaysCollide(float x, float y, float w, float h);
      ~UISurfaceAreaAlwaysCollide();

      void draw_bounding_area();
      bool collides(float x, float y);
   };
}




