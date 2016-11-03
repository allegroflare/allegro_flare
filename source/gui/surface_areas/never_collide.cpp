



#include <iostream>
#include <allegro_flare/gui/surface_areas/never_collide.h>




UISurfaceAreaNeverCollide::UISurfaceAreaNeverCollide()
   : UISurfaceArea(0, 0, 1, 1)
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




