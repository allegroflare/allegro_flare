#ifndef __UI_COLLISION_COLUMN_HEADER
#define __UI_COLLISION_COLUMN_HEADER




#include <allegro_flare/surface_area_base.h>




namespace allegro_flare
{
   class UISurfaceAreaColumn : public UISurfaceAreaBase
   {
   public:
      UISurfaceAreaColumn(float x, float w);

      void draw_bounding_area();
      bool collides(float x, float y);
   };
}




#endif
