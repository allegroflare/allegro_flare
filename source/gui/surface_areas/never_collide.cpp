



#include <iostream>
#include <allegro_flare/gui/surface_areas/never_collide.h>




UISurfaceAreaNeverCollide::UISurfaceAreaNeverCollide(float x, float y, float w, float h)
   : UISurfaceArea(x, y, w, h)
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




