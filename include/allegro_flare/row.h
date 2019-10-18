#ifndef __UI_COLLISION_ROW_HEADER
#define __UI_COLLISION_ROW_HEADER




#include <allegro_flare/surface_area_base.h>




namespace allegro_flare
{
   class UISurfaceAreaRow : public UISurfaceAreaBase
   {
   public:
      UISurfaceAreaRow(float y, float h);

      void draw_bounding_area();
      bool collides(float x, float y);
   };
}




#endif
