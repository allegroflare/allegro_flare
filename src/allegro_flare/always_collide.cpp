



#include <iostream>
#include <allegro_flare/always_collide.h>




namespace allegro_flare
{
   UISurfaceAreaAlwaysCollide::UISurfaceAreaAlwaysCollide(float x, float y, float w, float h)
      : UISurfaceAreaBase(x, y, w, h)
   {}




   UISurfaceAreaAlwaysCollide::~UISurfaceAreaAlwaysCollide()
   {}




   bool UISurfaceAreaAlwaysCollide::collides(float x, float y)
   {
      (void)x;
      (void)y;
      return true;
   }




   void UISurfaceAreaAlwaysCollide::draw_bounding_area()
   {}
}



