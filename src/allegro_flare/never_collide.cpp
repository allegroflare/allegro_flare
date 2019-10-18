



#include <iostream>
#include <allegro_flare/never_collide.h>




namespace allegro_flare
{
   UISurfaceAreaNeverCollide::UISurfaceAreaNeverCollide(float x, float y, float w, float h)
      : UISurfaceAreaBase(x, y, w, h)
   {}




   UISurfaceAreaNeverCollide::~UISurfaceAreaNeverCollide()
   {}




   bool UISurfaceAreaNeverCollide::collides(float x, float y)
   {
      (void)x;
      (void)y;
      return false;
   }




   void UISurfaceAreaNeverCollide::draw_bounding_area()
   {}
}



