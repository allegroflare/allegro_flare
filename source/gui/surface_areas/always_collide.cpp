



#include <iostream>
#include <allegro_flare/gui/surface_areas/always_collide.h>




UISurfaceAreaAlwaysCollide::UISurfaceAreaAlwaysCollide(float x, float y, float w, float h)
   : UISurfaceArea(x, y, w, h)
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




